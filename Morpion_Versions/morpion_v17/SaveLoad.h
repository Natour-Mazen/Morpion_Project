#ifndef SAVELOAD_H
#define SAVELOAD_H
#include <stdbool.h>

#include "Types.h"
#include "SaveLoadInText.h"
#include "SaveLoadInBinary.h"

//======================= Fichier =======================//
FILE* getFilewithMethode(char * file,const char *Methode);
void closeFile(FILE* f);

//================================= Sauvegarde Texte ============================//
void txt_saveGame(TPlayer PlayPlayer, TPlayer WaitPlayer, QList mainList, QList allQuints, Symboles jeu[TAILLEJEU][TAILLEJEU], Position* tabPosition);


//================================= Chargement Texte ============================//
void txt_loadGame(TPlayer* PlayPlayer, TPlayer* WaitPlayer, QList* mainList, QList* allQuints, Symboles jeu[TAILLEJEU][TAILLEJEU], Position** tabPosition);


//============================ Sauvegarde Binaire================================//
void b_saveGame(TPlayer PlayPlayer, TPlayer WaitPlayer, QList mainList, QList allQuints, Symboles jeu[TAILLEJEU][TAILLEJEU], Position* tabPosition);


//================================= Chargement Binaire ==========================//
void b_loadGame(TPlayer* PlayPlayer, TPlayer* WaitPlayer, QList* mainList, QList* allQuints, Symboles jeu[TAILLEJEU][TAILLEJEU], Position** tabPosition);


#endif
