#ifndef SAVELOAD_H
#define SAVELOAD_H
#include <stdbool.h>

#include "Types.h"
#include "SaveLoadInBinary.h"
#include "SaveLoadInText.h"

#define SAVEFILEB "MorpionSave"
#define SAVEFILET "MorpionSave.txt"

//======================= Fichier =======================//
FILE* getFileInWrite();
FILE* getFileInRead();
void closeFile(FILE* f);

//===================== Sauvegarde ======================//
void saveGameBinary(TPlayer PlayPlayer, TPlayer WaitPlayer, QList mainList, QList allQuints, Symboles jeu[TAILLEJEU][TAILLEJEU], Position* tabPosition);
void saveGameText(TPlayer PlayPlayer, TPlayer WaitPlayer, QList mainList, QList allQuints, Symboles jeu[TAILLEJEU][TAILLEJEU], Position* tabPosition);

//===================== Chargement ======================//
void loadGameBinary(TPlayer* PlayPlayer, TPlayer* WaitPlayer, QList* mainList, QList* allQuints, Symboles jeu[TAILLEJEU][TAILLEJEU], Position** tabPosition);
void loadGameText(TPlayer* PlayPlayer, TPlayer* WaitPlayer, QList* mainList, QList* allQuints, Symboles jeu[TAILLEJEU][TAILLEJEU], Position** tabPosition);

//=======================================================//
#endif