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

    //Creation du Tableau de Positions ainsi que la liste principale de Quintuplets.
    Position* tabPosition = getTabPosition(TAILLEJEU);
    QList mainList = makeMainList(tabPosition);

    // On utilisera cette liste pour supprimer tout les quintuplets à la fin.
    QList allQuints = duplicate_QL(mainList);


    //Creation de Variables a utiliser pour chaque tour de Jeu
    char action = ' ';

    printPlateauDeJeu(jeu, playerX, playerO, tabPosition);

    //==========================================================================//
    //=============================== Début du Jeu =============================//
    //==========================================================================//

    // Si aucun des deux joueurs ne gagne ou si il y a encore des coup possible à jouer, on continue de jouer.
    while (!((isEmpty_QL(playerO.listeGagnant) || isEmpty_QL(playerX.listeGagnant)) && isEmpty_QL(mainList)) && !(quitKeysAction(action)))
    {

        // Tour pour les X.
        tourPlayer(&playerX, &playerO, &mainList, jeu, tabPosition, &action);
        miseAzeroXOTableau(TAILLEJEU, tabPosition);
        playerX.winQuints += checkWinQuints(playerX.listeGagnant);
        //sleep(1);

        // Tour pour les O.
        if(!((isEmpty_QL(playerO.listeGagnant) || isEmpty_QL(playerX.listeGagnant)) && isEmpty_QL(mainList)) && !(quitKeysAction(action)))
        {
            tourPlayer(&playerO, &playerX, &mainList, jeu, tabPosition, &action);
            miseAzeroXOTableau(TAILLEJEU, tabPosition);
            playerO.winQuints += checkWinQuints(playerO.listeGagnant);
            //sleep(1);
        }

        // On sauvegarde la partie en binaire.
        if(saveBinaryKeysAction(action))
        {
            saveGameBinary(playerX, playerO, mainList, allQuints, jeu, tabPosition);
        }
        // On charge la partie en binaire.
        if(loadBinaryKeysAction(action))
        {
            loadGameBinary(&playerX, &playerO, &mainList, &allQuints, jeu, &tabPosition);
        }
        // On sauvegarde la partie sous forme de texte.
        if(saveTextKeysAction(action))
        {
            saveGameText(playerX, playerO, mainList, allQuints, jeu, tabPosition);
        }
        // On charge la partie sous forme de texte.
        if(loadTextKeysAction(action))
        {
            loadGameText(&playerX, &playerO, &mainList, &allQuints, jeu, &tabPosition);
        }
    }

    //========================================================================//
    //=============================== Fin du Jeu =============================//
    //========================================================================//


    if(playerX.winQuints > playerO.winQuints)
    {
        printWinner(playerX.typeSymbole);
    }
    else if(playerX.winQuints < playerO.winQuints)
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