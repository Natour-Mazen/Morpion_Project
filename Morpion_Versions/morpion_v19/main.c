#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Morpion.h"
#include "Types.h"
#include "Quintuplet.h"
#include "Position.h"
#include "Affichage.h"
#include "SaveLoad.h"
// Pour windows
//#include "windows.h"

int main(int argc, char* argv[])
{
    //==========================================================================//
    //=========================== Initialisation du Jeu ========================//
    //==========================================================================//

	//Initialisation des Joueurs && affichage du menu.
    TPlayer playerX  , playerO;
    initplayerX(&playerX,54); // On initilaise des types de joueurs n'importe pour �tre s�r que si l'utilisateur choisi pas de type on passe dans le CheckTypePlayer
    initplayerO(&playerO,695); // car sinon le typejoueur X est mis � 0 par defaut or si on a rien choisi c'est problemeatique

    bool continuJeu = true; //Si l'utilisateur quitte l'ecran du menu faut pas lancer le jeu
    MySDL_Menu(&playerX,&playerO,&continuJeu);

    if(continuJeu){

        //On verifie si L'utilisateur a bien choisi des types de joueurs pour les 2 joueurs
        CheckTypePlayer(&playerX,&playerO);

        //Creation et affichage du plateau de Jeu.
        Symboles jeu[TAILLEJEU][TAILLEJEU];
        initPlateau(jeu);

        // Initialisez SDL
        SDL_Init(SDL_INIT_VIDEO);

        // Creez une fenetre
        SDL_Window* window = SDL_CreateWindow("Morpion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, TAILLEECRANJEU, TAILLEECRANJEU, SDL_WINDOW_SHOWN);

        // Creez un renderer pour dessiner sur la fenetre
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        // la couleur de fond en noir
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

        // on dessine la grille de morpion
        dessiner_grille_morpion(renderer);

        // Afficher le rendu a l'ecran
        SDL_RenderPresent(renderer);

        //Creation du Tableau de Positions ainsi que la liste principale de Quintuplets.
        Position* tabPosition = getTabPosition(TAILLEJEU);
        QList mainList = makeMainList(tabPosition);

        // On utilisera cette liste pour supprimer tout les quintuplets à la fin.
        QList allQuints = duplicate_QL(mainList);

        printPlateauDeJeu(jeu, playerX, playerO, tabPosition);

        //==========================================================================//
        //=============================== Début du Jeu =============================//
        //==========================================================================//
        bool stopgame = false;
        srand(time(NULL));

        // Génération d'un nombre aléatoire entre 0 et RAND_MAX
        int rand_num = rand()%2;
        // Normalisation du nombre aléatoire entre 0 et 1
        //double rand_double = (double) rand_num / RAND_MAX;

        // Si aucun des deux joueurs ne gagne ou si il y a encore des coup possible à jouer, on continue de jouer.
        while (!((isEmpty_QL(playerO.listeGagnant) || isEmpty_QL(playerX.listeGagnant)) && isEmpty_QL(mainList)) &&
              !stopgame)
        {
            Color_Quint_case(jeu,renderer,tabPosition);
            SDL_PumpEvents(); //do events
            const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
            // On sauvegarde la partie.
            if(pKeyStates[SDL_SCANCODE_S])
            {
                saveGameText(playerX, playerO, mainList, allQuints, jeu, tabPosition);
                //saveGameBinary(playerX, playerO, mainList, allQuints, jeu, tabPosition);
                messageSDL("SAUVEGARDE",">> La Sauvegarde de votre partie a ete effectue !",SDL_MESSAGEBOX_INFORMATION);
            }
            // On charge une partie.
            if( pKeyStates[SDL_SCANCODE_L])
            {
                loadGameText(&playerX, &playerO, &mainList, &allQuints, jeu, &tabPosition);
                //loadGameBinary(&playerX, &playerO, &mainList, &allQuints, jeu, &tabPosition);
                messageSDL("CHARGEMENT",">> Le Chargement de votre ancienne partie a ete effectue !",SDL_MESSAGEBOX_INFORMATION);
                redessiner_PlateauJeu(renderer,window,jeu);
                Color_Quint_case(jeu,renderer,tabPosition);
                WhatisTheSymbol(playerX,playerO);
            }
            //on affiche le score
            if( pKeyStates[SDL_SCANCODE_B])
            {
               Display_Score(playerO,playerX);
            }
            //on affiche les infos utiles pour le jeu
            if( pKeyStates[SDL_SCANCODE_I])
            {
               Display_Info();
            }
            //On quitte la partie
            if( pKeyStates[SDL_SCANCODE_ESCAPE])
            {
                messageSDL("EXIT",">> Vous avez Demander a arreter La partie !",SDL_MESSAGEBOX_INFORMATION);
                stopgame = true;
            }

            if(rand_num==1){
                // Tour pour les X.
                tourPlayer(&playerX, &playerO, &mainList, jeu, tabPosition, renderer,&stopgame);
                miseAzeroXOTableau(TAILLEJEU, tabPosition);
                playerX.winQuints += checkWinQuints(playerX.listeGagnant);
                   rand_num = 0;
            }
            else if(rand_num==0){
                // Tour pour les O.
                if(!((isEmpty_QL(playerO.listeGagnant) || isEmpty_QL(playerX.listeGagnant)) && isEmpty_QL(mainList))&&
                  !stopgame )
                {
                    tourPlayer(&playerO, &playerX, &mainList, jeu, tabPosition,  renderer,&stopgame);
                    miseAzeroXOTableau(TAILLEJEU, tabPosition);
                    playerO.winQuints += checkWinQuints(playerO.listeGagnant);
                }
                rand_num = 1;

            }



            printPlateauDeJeu(jeu, playerX, playerO, tabPosition);

        }

        //========================================================================//
        //=============================== Fin du Jeu =============================//
        //========================================================================//
        if(playerX.winQuints > playerO.winQuints && !stopgame)
        {
            Display_Score(playerO,playerX);
            print_Winner_SDL(1); // joueur avec des croix
        }
        else if(playerX.winQuints < playerO.winQuints  && !stopgame)
        {
            Display_Score(playerO,playerX);
            print_Winner_SDL(2); // joueur avec des ronds
        }
        else if(!stopgame)
        {
            print_Winner_SDL(-1); // Egalit�
        }

        //========================================================================//
        //====================== Free de tout les mallocs fait ===================//
        //========================================================================//

        // On free toutes les listes.
        mainList = remAll_QL(mainList);
        playerO.listeGagnant = remAll_QL(playerO.listeGagnant);
        playerO.listePerdante = remAll_QL(playerO.listePerdante);
        playerX.listeGagnant = remAll_QL(playerX.listeGagnant);
        playerX.listePerdante = remAll_QL(playerX.listePerdante);
        // On supprime tout les quintuplets.
        allQuints = remAllPlusElement_QL(allQuints);

        // On supprime le tableau de position.
        freeTabPosition(TAILLEJEU, tabPosition);

        // Nettoyez les ressources utilisees par SDL
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }


    //========================================================================//
    //================================== Fin =================================//
    //========================================================================//

	return EXIT_SUCCESS;
}
