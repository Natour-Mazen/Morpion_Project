#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SaveLoad.h"
#include "Types.h"
#include "Position.h"

//===============================================================================//
//================================== Fichier ====================================//
//===============================================================================//

// Ouvre le fichier "MorpionSave.txt" en écriture.
FILE* getFileInWrite(char* file)
{
    FILE* fd = fopen(file, "w");
    if(fd == NULL)
    {
        printf("Error getFileInWrite : on ne peut pas ouvrir le fichier \"%s\"\n", file);
        exit(EXIT_FAILURE);
    }
    return fd;
}

// Ouvre le fichier "MorpionSave.txt" en lecture.
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
//================================= Sauvegarde ==================================//
//===============================================================================//

// Sauvegarde une partie de Morpion dans un fichier sous forme de binaire.
void saveGameBinary(TPlayer PlayPlayer, TPlayer WaitPlayer, QList mainList, QList allQuints, Symboles jeu[TAILLEJEU][TAILLEJEU], Position* tabPosition)
{
	FILE* fd = getFileInWrite(SAVEFILEB);

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

// Sauvegarde une partie de Morpion dans un fichier sous forme de texte.
void saveGameText(TPlayer PlayPlayer, TPlayer WaitPlayer, QList mainList, QList allQuints, Symboles jeu[TAILLEJEU][TAILLEJEU], Position* tabPosition)
{
	FILE* fd = getFileInWrite(SAVEFILET);

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
//================================= Chargement ==================================//
//===============================================================================//

// Charge une partie de Morpion depuis un fichier sous forme de binaire.
void loadGameBinary(TPlayer* PlayPlayer, TPlayer* WaitPlayer, QList* mainList, QList* allQuints, Symboles jeu[TAILLEJEU][TAILLEJEU], Position** tabPosition)
{
	FILE* fd = getFileInRead(SAVEFILEB);

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

// Charge une partie de Morpion depuis un fichier sous forme de texte.
void loadGameText(TPlayer* PlayPlayer, TPlayer* WaitPlayer, QList* mainList, QList* allQuints, Symboles jeu[TAILLEJEU][TAILLEJEU], Position** tabPosition)
{
	FILE* fd = getFileInRead(SAVEFILET);

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