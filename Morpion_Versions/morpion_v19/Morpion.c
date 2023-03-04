#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Morpion.h"
#include "Position.h"

//===============================================================================//
//=============================== Initialisation ================================//
//===============================================================================//

// Initialise le plateau avec que des 0.
void initPlateau(Symboles jeu[TAILLEJEU][TAILLEJEU])
{
    for (int i = 0; i < TAILLEJEU; i++)
    {
        for (int j = 0; j < TAILLEJEU; j++)
        {
            jeu[i][j] = vide;
        }
    }
}

// Initialise "p" de type TPlayer.
static void ParamPlayer(TPlayer* p, int tjoueur)
{
    if(tjoueur == 0)
    {
        p->typejoueur = Humain;
        p->listeGagnant = NULL;
        p->listePerdante = NULL;
        p->winQuints = 0;
    }
    else if (tjoueur == 1)
    {
        p->typejoueur = IA;
        p->listeGagnant = NULL;
        p->listePerdante = NULL;
        p->winQuints = 0;
    }
    else{
        p->typejoueur = tjoueur;
        p->listeGagnant = NULL;
        p->listePerdante = NULL;
        p->winQuints = 0;
    }
}


void initplayerX(TPlayer *p,int TypeJoueur)
{
    p->typeSymbole = croix;
    ParamPlayer(p, TypeJoueur);
    printf("\n");

 }

void initplayerO(TPlayer *p,int TypeJoueur)
{
    p->typeSymbole = rond;
    ParamPlayer(p, TypeJoueur);
    printf("\n");

 }

//===============================================================================//
//=============================== Vérifications =================================//
//===============================================================================//

// Vérifie si une case du plateau est vide.
bool isEmptyCase(Symboles jeu[TAILLEJEU][TAILLEJEU], int posX, int posY)
{
    return (jeu[posX][posY] == vide);
}

// Regarde si dans la liste il y a un quintuplet à 5 symboles.
bool checkVictory(QList l)
{
    QList parcours = l;

    while (!isEmpty_QL(parcours))
    {
        //valeur à modifier precisement, valeur maximale possible, cas d'un quintuplet à 5 symboles.
        if(isQuintFull(getQ_QL(parcours)))
        {
            return true;
        }
        parcours = getNext_QL(parcours);
    }
    return false; //on a pas trouvé de quintuplet à 5 symboles.
}

// Regarde le nombre de quintuplets qui gagne et retourne ce nombre.
int checkWinQuints(QList l)
{
    QList parcours = l;
    int nbWinQuints = 0;

    while (!isEmpty_QL(parcours))
    {
        Quintuplet* q = getQ_QL(parcours);
        if(isQuintFull(q))
        {
            setPosQuintToWin(q);
            nbWinQuints++;
        }
        parcours = getNext_QL(parcours);
    }
    return nbWinQuints;
}

//On verifie si L'utilisateur a bien choisi des types de joueurs
void  CheckTypePlayer(TPlayer *playerX, TPlayer *playerO)
{
    //si ce n'est pas le cas alors le jeu sera IA vs IA
    if((playerX->typejoueur != Humain && playerX->typejoueur != IA)
       ||
       (playerO->typejoueur != Humain && playerO->typejoueur != IA))
    {
        messageSDL("Types De Joueurs Non Saissi !",">> Vous n'avez pas entrez de Type pour les joueurs ainsi le jeu sera IA vs IA",SDL_MESSAGEBOX_WARNING);
        initplayerO(playerO,1);
        initplayerX(playerX,1);
    }
}



//===============================================================================//
//===================== Ajout d'une position sur le plateau =====================//
//===============================================================================//

// Demande la postion d'un symbole au joueur et l'ajoute sur le plateau de jeu.
Position askPostionHumain(Symboles jeu[TAILLEJEU][TAILLEJEU], TPlayer p, Position* TabPosition,SDL_Renderer* renderer,bool *stopGame)
{
    Position ChoosenPos = NULL;
    int X = 0;
    int Y = 0;

    //printPlateauDeJeu(jeu);
    printLastPlay(p, X, Y, false);

    ChoosenPos = readPositionToPlay(p, &X, &Y, TabPosition, jeu,renderer,stopGame);
    jeu[X][Y] = p.typeSymbole;
    setSymbole(p.typeSymbole, ChoosenPos);

    return ChoosenPos;
}

// Ajoute un du Bot symbole sur le plateau de jeu.
void askPositionBot(Symboles jeu[TAILLEJEU][TAILLEJEU], Position ChoosenPos, TPlayer p,SDL_Renderer* renderer)
{
    int X = 0;
    int Y = 0;

    //printPlateauDeJeu(jeu);
    printLastPlay(p, X, Y, false);

    X = getX(ChoosenPos);
    Y = getY(ChoosenPos);
    if(p.typeSymbole == croix){
            dessiner_croix_bleue(renderer,X,Y);
    }
    else{
            dessiner_rond_rouge(renderer,X,Y);
    }
    // Affichez le rendu a l'ecran
    SDL_RenderPresent(renderer);

    jeu[X][Y] = p.typeSymbole;
    setSymbole(p.typeSymbole, ChoosenPos);

    //printPlateauDeJeu(jeu);
    printLastPlay(p, X, Y, true);
}


//===============================================================================//
//============================= Meilleur Position ===============================//
//===============================================================================//

// Choisie la meilleur position pour jouer.
Position bestPositionToPlay(QList list, Symboles symbole, int* recupValMax)
{
    Symboles sym = symbole;
    QList parcours = list;
    Position max_Pos = NULL;
    int valmaxPos = 0 ;
    //On suppose "parcours" avec au moins un élément (vérifié avant son appel)
    while(!isEmpty_QL(parcours))
    {
        Quintuplet* q = getQ_QL(parcours);
        for (int i = 0; i < NTUPLET; i++)
        {
            int valQ = getVal(q->pos[i], sym) + q->valquintuplet;
            // meilleur position sans symbole et en fonction de qui fait l'appel ajout de getSymbole
            if((valQ >= valmaxPos) && (q->pos[i]->Sy == vide))
            {
                max_Pos = q->pos[i];
                valmaxPos = valQ;
            }
        }
        parcours = getNext_QL(parcours);
    }
    *recupValMax = valmaxPos;
    return max_Pos;
}

//===============================================================================//
//============================ Mise à jour valeurs ==============================//
//===============================================================================//

// On ajoute 100 à la valeur du quintuplet si il y a la position dans sa liste.
void majValQunits(Position pos, QList l)
{
    QList parcours = getFst_QL(l);

    //On suppose "parcours" avec au moins un �l�ment (v�rifi� avant son appel)
    //on parcourt l'integralite de notre liste "parcours"
    while (!isEmpty_QL(parcours))
    {
        //on compare chaque case du quintuplet avec notre case recherchee
        for(int i = 0; i < NTUPLET; i++)
        {
            if(equals(pos, (getQ_QL(parcours))->pos[i]))
            {
                (getQ_QL(parcours))->valquintuplet += 100;
            }
        }
	    parcours = getNext_QL(parcours);
    }
}

// Pour chaque Position qui se trouve dans la liste, on augmente leur valeur.
void majValPositions(QList list, Symboles symbole){

    PList listP = empty_PL();
    QList parcours = getFst_QL(list);

    Symboles sym = symbole;

    while(!isEmpty_QL(parcours))
    {
        for(int i = 0; i < NTUPLET; i++)
        {
            if(!(isInList_PL(getQ_QL(parcours)->pos[i], listP)))
            {
                listP = add_PL(getQ_QL(parcours)->pos[i], listP);
                majValPosition(getQ_QL(parcours)->pos[i], sym);
            }
        }
        parcours = getNext_QL(parcours);
    }
    listP = remAll_PL(listP);
}

//===============================================================================//
//================================ Tour de Jeu ==================================//
//===============================================================================//

// Tour de jeu pour un Humain.
static Position tourHumain(TPlayer* PlayPlayer, Symboles jeu[TAILLEJEU][TAILLEJEU], Position* tabPosition, SDL_Renderer* renderer,bool *stopGame)
{
    return askPostionHumain(jeu, *PlayPlayer, tabPosition, renderer,stopGame);
}

// Tour de jeu pour un Bot.
static Position tourBot(TPlayer* PlayPlayer, TPlayer* WaitPlayer, QList* mainList, Symboles jeu[TAILLEJEU][TAILLEJEU],SDL_Renderer* renderer)
{
    Position ChoosenPos = NULL;
    Position DefPos = NULL;
    Position posToPlay = NULL;
    int bestPositionToPlayAtt = 0;
    int bestPositionToPlayDef = 0;

    // Si la liste gagante n'est pas vide alors on joue avec ces quintuplets.
    if(!isEmpty_QL(PlayPlayer->listeGagnant))
    {
        // Pour chaque position qui se trouve dans les listes gagnantes, on augmente leur valeur.
        majValPositions(PlayPlayer->listeGagnant, PlayPlayer->typeSymbole);
        majValPositions(WaitPlayer->listeGagnant, WaitPlayer->typeSymbole);
        // Retourne la meilleur position pour jouer et la meilleur position de l'adversaire.
        ChoosenPos = bestPositionToPlay(PlayPlayer->listeGagnant, PlayPlayer->typeSymbole, &bestPositionToPlayAtt);
        DefPos = bestPositionToPlay(WaitPlayer->listeGagnant, WaitPlayer->typeSymbole, &bestPositionToPlayDef);
    }
    // Sinon on recupére des quintuplets de la liste principale.
    else
    {
        // Retourne la meilleur position pour jouer et la meilleur position de l'adversaire.
        ChoosenPos = bestPositionToPlay(*mainList, PlayPlayer->typeSymbole, &bestPositionToPlayAtt);
        DefPos = bestPositionToPlay(WaitPlayer->listeGagnant, WaitPlayer->typeSymbole, &bestPositionToPlayDef);
    }

    if(bestPositionToPlayAtt >= bestPositionToPlayDef)
    {
        posToPlay = ChoosenPos;
    }
    else
    {
        posToPlay = DefPos;
    }
    askPositionBot(jeu, posToPlay, *PlayPlayer,renderer);
    return posToPlay;
}

// Tour de jeu pour un joueur.
void tourPlayer(TPlayer* PlayPlayer, TPlayer* WaitPlayer, QList* mainList, Symboles jeu[TAILLEJEU][TAILLEJEU], Position* tabPosition, SDL_Renderer* renderer,bool *stopGame)
{
    QList recupAllQuints = empty_QL();
    Position posToPlay = NULL;

    // On supprime tout les quintuplets qui ne peuvent plus gagner.
    PlayPlayer->listeGagnant = removeClosedQuints(PlayPlayer->listeGagnant);

    //Joueur PlayPlayer joue.

    // Si PlayPlayer est un humain.
    if (PlayPlayer->typejoueur == Humain)
    {
        // Le joueur ajoute un symbole sur le plateau.
        posToPlay = tourHumain(PlayPlayer, jeu, tabPosition, renderer,stopGame);

    }
    // Si PlayPlayer est un bot.
    else
    {
        posToPlay = tourBot(PlayPlayer, WaitPlayer, mainList, jeu,renderer);
    }
    // On recupere tout les quintuplets qui passse par "posToPlay".
    recupAllQuints = getAllQuints(posToPlay, mainList);
    // On ajoute ces quintuplets à la liste gagnante du joueur.
    PlayPlayer->listeGagnant = concat_QL(PlayPlayer->listeGagnant, &recupAllQuints);
    // On ajoute 100 au quintuplet qui on "posToPlay" en commun.
    majValQunits(posToPlay, PlayPlayer->listeGagnant);
}
