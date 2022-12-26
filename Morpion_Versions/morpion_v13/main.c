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
    initplayerX(&playerX,54); // On initilaise des types de joueurs n'importe pour être sûr que si l'utilisateur choisi pas de type on passe dans le CheckTypePlayer
    initplayerO(&playerO,695); // car sinon le typejoueur X est mis à 0 par defaut or si on a rien choisi c'est problemeatique

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
        SDL_Window* window = SDL_CreateWindow("Morpion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);

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

        //Creation de Variables a utiliser pour chaque tour de Jeu
        bool Xgagne = false;
        bool Ogagne = false;
        bool stopgame = false;

        //==========================================================================//
        //=============================== Début du Jeu =============================//
        //==========================================================================//

        // Si aucun des deux joueurs ne gagne ou si il y a encore des coup possible à jouer, ou si l'utilisateur n'as pas demandé l'arret du jeu, on continue de jouer.
        while (((!Xgagne && !Ogagne) && !((isEmpty_QL(playerO.listeGagnant) || isEmpty_QL(playerX.listeGagnant)) && isEmpty_QL(mainList)) )&&
              !stopgame)
        {
            SDL_PumpEvents(); //do events
            const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
            // On sauvegarde la partie.
            if(pKeyStates[SDL_SCANCODE_S])
            {
                 messageSDL("SAUVEGARDE",">> La Sauvegarde de votre partie a ete effectue !");
                saveGame(playerX, playerO, mainList, allQuints, jeu, tabPosition);
            }
            // On charge une partie.
            if( pKeyStates[SDL_SCANCODE_L])
            {
                messageSDL("CHARGEMENT",">> Le Chargement de votre ancienne partie a ete effectue !");
                loadGame(&playerX, &playerO, &mainList, &allQuints, jeu, &tabPosition);
                MAJPlateauJeu(renderer,jeu);
            }
            //On quitte la partie
            if( pKeyStates[SDL_SCANCODE_ESCAPE])
            {
                messageSDL("EXIT",">> Vous avez Demander a arreter La partie !");
                stopgame = true;
            }

            // Tour pour les X.
            tourPlayer(&playerX, &playerO, &mainList, jeu, tabPosition, renderer,&stopgame);
            miseAzeroXOTableau(TAILLEJEU, tabPosition);
            Xgagne = checkVictory(playerX.listeGagnant);
            //sleep(1);

            // Tour pour les O.
            if(!Xgagne && !((isEmpty_QL(playerO.listeGagnant) || isEmpty_QL(playerX.listeGagnant)) && isEmpty_QL(mainList)) &&
                !stopgame)
            {
                tourPlayer(&playerO, &playerX, &mainList, jeu, tabPosition, renderer,&stopgame);
                miseAzeroXOTableau(TAILLEJEU, tabPosition);
                Ogagne = checkVictory(playerO.listeGagnant);
                //sleep(1);
            }
            printPlateauDeJeu(jeu);
        }

        //========================================================================//
        //=============================== Fin du Jeu =============================//
        //========================================================================//

        if(Xgagne)
        {
            print_Winner_SDL(1); // joueur avec des croix
        }
        else if(Ogagne)
        {
            print_Winner_SDL(2); // joueur avec des ronds
        }
        else if(!stopgame)
        {
           print_Winner_SDL(-1); // Egalité
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


        //========================================================================//
        //================================== Fin =================================//
        //========================================================================//

    }

	return EXIT_SUCCESS;
}
