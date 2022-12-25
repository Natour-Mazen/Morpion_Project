#ifndef AFFICHAGE_H
#define AFFICHAGE_H
#include <stdbool.h>

#include "AffichageConsole.h"
#include "Types.h"
#include "Morpion.h"

//======================= Print =========================//
void printMenu();
void printWinner(int joueur);
void printPlateauDeJeu(Symboles jeu[TAILLEJEU][TAILLEJEU]);
void printLastPlay(TPlayer p, int X, int Y, bool change);
//======================= Read ==========================//
Position readPositionToPlay(TPlayer p, int* X, int* Y, Position* TabPosition, Symboles jeu[TAILLEJEU][TAILLEJEU]);
char readOtherOptions();

//======================= SDL ==========================//
void messageSDL(char *myTitle, char *myMessage);
void MySDLMenu(TPlayer *playerX, TPlayer *playerO);

#endif
