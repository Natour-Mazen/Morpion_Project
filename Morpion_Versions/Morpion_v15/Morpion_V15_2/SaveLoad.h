#ifndef SAVELOAD_H
#define SAVELOAD_H
#include <stdbool.h>

#include "Types.h"
#include "SaveLoadInBinary.h"

//===================== Sauvegarde ======================//
void saveGame(TPlayer PlayPlayer, TPlayer WaitPlayer, QList mainList, QList allQuints, Symboles jeu[TAILLEJEU][TAILLEJEU], Position* tabPosition);

//===================== Chargement ======================//
void loadGame(TPlayer* PlayPlayer, TPlayer* WaitPlayer, QList* mainList, QList* allQuints, Symboles jeu[TAILLEJEU][TAILLEJEU], Position** tabPosition);

//=======================================================//
#endif