#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SaveLoad.h"
#include "Types.h"
#include "Position.h"

//===============================================================================//
//================================== Fichier ====================================//
//===============================================================================//

// Ouvre le fichier en écriture.
FILE* getFileInWrite(char * file)
{
    FILE* fd = fopen(file, "w");
    if(fd == NULL)
    {
        printf("Error getFileInWrite : on ne peut pas ouvrir le fichier \"%s\"\n", file);
        exit(EXIT_FAILURE);
    }
    return fd;
}

// Ouvre le fichier en lecture.
FILE* getFileInRead(char* file)
{
    FILE* fd = fopen(file, "r");
    if(fd == NULL)
    {
        printf("Error getFileInRead : on ne peut pas ouvrir le fichier \"%s\"\n", file);
        exit(EXIT_FAILURE);
    }
    return fd;
}

// Ferme le fichier f.
void closeFile(FILE* f)
{
	fclose(f);
}



//===============================================================================//
//================================= Sauvegarde Texte ============================//
//===============================================================================//

// Sauvegarde une partie de Morpion dans un fichier sous forme de texte.
void txt_saveGame(TPlayer PlayPlayer, TPlayer WaitPlayer, QList mainList, QList allQuints, Symboles jeu[TAILLEJEU][TAILLEJEU], Position* tabPosition)
{
	FILE* fd = getFileInWrite("Sauvegarde/MorpionSavetxt.txt");

	// On ecrit le tablea de symboles.
	writeSymbolesTab(fd, jeu);

	// On ecrit le tableau de positions.
	writeTabPosition(fd, tabPosition);

	// On ecrit la liste de tout les Quintuplets.
	writeListQuintuplets(fd, allQuints);

	// On ecrit les Quintuplets de mainList.
	writeLiteListQuintuplets(fd, mainList);

	// On ecrit les deux joueurs.
	writeTPlayer(fd, PlayPlayer);
	writeTPlayer(fd, WaitPlayer);

	closeFile(fd);
}

//===============================================================================//
//================================= Chargement Texte ============================//
//===============================================================================//

void txt_loadGame(TPlayer* PlayPlayer, TPlayer* WaitPlayer, QList* mainList, QList* allQuints, Symboles jeu[TAILLEJEU][TAILLEJEU], Position** tabPosition)
{
	FILE* fd = getFileInRead("Sauvegarde/MorpionSavetxt.txt");

	//=== On vide tout le jeu actuel.
	*mainList = remAll_QL(*mainList);
    PlayPlayer->listeGagnant = remAll_QL(PlayPlayer->listeGagnant);
    PlayPlayer->listePerdante = remAll_QL(PlayPlayer->listePerdante);
    WaitPlayer->listeGagnant = remAll_QL(WaitPlayer->listeGagnant);
    WaitPlayer->listePerdante = remAll_QL(WaitPlayer->listePerdante);
    *allQuints = remAllPlusElement_QL(*allQuints);
    freeTabPosition(TAILLEJEU, *tabPosition);
    //===

    // On lit le tableau de symboles.
	readSymbolesTab(fd, jeu);

	// On lit le tableau de positions.
	readTabPosition(fd, tabPosition);

	// On lit la liste de tout les Quintuplets.
	*allQuints = readListQuintuplets(fd, *tabPosition);

	// On lit la liste "mainList".
	*mainList = readLiteListQuintuplets(fd, *allQuints);

	// On lit les deux joueurs.
	*PlayPlayer = readTPlayer(fd, *allQuints);
	*WaitPlayer = readTPlayer(fd, *allQuints);

	closeFile(fd);
}
//===============================================================================//
//============================ Sauvegarde Binaire================================//
//===============================================================================//

// Sauvegarde une partie de Morpion dans un fichier sous forme de texte.
void b_saveGame(TPlayer PlayPlayer, TPlayer WaitPlayer, QList mainList, QList allQuints, Symboles jeu[TAILLEJEU][TAILLEJEU], Position* tabPosition)
{
	FILE* fd = getFileInWrite("Sauvegarde/MorpionSaveBin");

	// On ecrit le tablea de symboles.
	b_writeSymbolesTab(fd, jeu);

	// On ecrit le tableau de positions.
	b_writeTabPosition(fd, tabPosition);

	// On ecrit la liste de tout les Quintuplets.
	b_writeListQuintuplets(fd, allQuints);

	// On ecrit les Quintuplets de mainList.
	b_writeLiteListQuintuplets(fd, mainList);

	// On ecrit les deux joueurs.
	b_writeTPlayer(fd, PlayPlayer);
	b_writeTPlayer(fd, WaitPlayer);

	closeFile(fd);
}

//===============================================================================//
//================================= Chargement Binaire ==========================//
//===============================================================================//

void b_loadGame(TPlayer* PlayPlayer, TPlayer* WaitPlayer, QList* mainList, QList* allQuints, Symboles jeu[TAILLEJEU][TAILLEJEU], Position** tabPosition)
{
	FILE* fd = getFileInRead("Sauvegarde/MorpionSaveBin");

	//=== On vide tout le jeu actuel.
	*mainList = remAll_QL(*mainList);
    PlayPlayer->listeGagnant = remAll_QL(PlayPlayer->listeGagnant);
    PlayPlayer->listePerdante = remAll_QL(PlayPlayer->listePerdante);
    WaitPlayer->listeGagnant = remAll_QL(WaitPlayer->listeGagnant);
    WaitPlayer->listePerdante = remAll_QL(WaitPlayer->listePerdante);
    *allQuints = remAllPlusElement_QL(*allQuints);
    freeTabPosition(TAILLEJEU, *tabPosition);
    //===

    // On lit le tableau de symboles.
	b_readSymbolesTab(fd, jeu);

	// On lit le tableau de positions.
	b_readTabPosition(fd, tabPosition);

	// On lit la liste de tout les Quintuplets.
	*allQuints = b_readListQuintuplets(fd, *tabPosition);

	// On lit la liste "mainList".
	*mainList = b_readLiteListQuintuplets(fd, *allQuints);

	// On lit les deux joueurs.
	*PlayPlayer = b_readTPlayer(fd, *allQuints);
	*WaitPlayer = b_readTPlayer(fd, *allQuints);

	closeFile(fd);
}

//===============================================================================//
