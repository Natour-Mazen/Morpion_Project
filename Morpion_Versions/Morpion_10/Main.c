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

int main()
{
    //==========================================================================//
    //=========================== Initialisation du Jeu ========================//
    //==========================================================================//

	//Menu du Jeu
	printMenu();

	//Initialisation des Joueurs.
	TPlayer playerX = initplayer(1);
	TPlayer playerO = initplayer(2);


	//Creation et affichage du plateau de Jeu.
    Symboles jeu[TAILLEJEU][TAILLEJEU];
    initPlateau(jeu);
    printPlateauDeJeu(jeu);

    //Creation du Tableau de Positions ainsi que la liste principale de Quintuplets.
    Position* tabPosition = getTabPosition(TAILLEJEU);
    QList mainList = makeMainList(tabPosition);

    // On utilisera cette liste pour supprimer tout les quintuplets à la fin.
    QList allQuints = duplicate_QL(mainList);


    //Creation de Variables a utiliser pour chaque tour de Jeu
    bool Xgagne = false;
    bool Ogagne = false;
    char action = ' ';

    //==========================================================================//
    //=============================== Début du Jeu =============================//
    //==========================================================================//

    // Si aucun des deux joueurs ne gagne ou si il y a encore des coup possible à jouer, on continue de jouer.
    while ((!Xgagne && !Ogagne) && !((isEmpty_QL(playerO.listeGagnant) || isEmpty_QL(playerX.listeGagnant)) && isEmpty_QL(mainList)) &&
            !(quitKeysAction(action)))
    {

        // Tour pour les X.
        tourPlayer(&playerX, &playerO, &mainList, jeu, tabPosition, &action);
        miseAzeroXOTableau(TAILLEJEU, tabPosition);
        Xgagne = checkVictory(playerX.listeGagnant);
        //sleep(1);

        // Tour pour les O.
        if(!Xgagne && !((isEmpty_QL(playerO.listeGagnant) || isEmpty_QL(playerX.listeGagnant)) && isEmpty_QL(mainList)) &&
           !(quitKeysAction(action)))
        {
            tourPlayer(&playerO, &playerX, &mainList, jeu, tabPosition, &action);
            miseAzeroXOTableau(TAILLEJEU, tabPosition);
            Ogagne = checkVictory(playerO.listeGagnant);
            //sleep(1);
        }

        // On sauvegarde la partie.
        if(saveKeysAction(action))
        {
            saveGame(playerX, playerO, mainList, allQuints, jeu, tabPosition);
        }
        // On charge la partie.
        if(loadKeysAction(action))
        {
            loadGame(&playerX, &playerO, &mainList, &allQuints, jeu, &tabPosition);
        }
    }

    //========================================================================//
    //=============================== Fin du Jeu =============================//
    //========================================================================//

    if(Xgagne)
    {
        printWinner(playerX.typeSymbole);
    }
    else if(Ogagne)
    {
        printWinner(playerO.typeSymbole);
    }
    else
    {
        printWinner(-1);
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

    //========================================================================//
    //================================== Fin =================================//
    //========================================================================//

	return EXIT_SUCCESS;
}
