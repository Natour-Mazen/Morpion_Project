#ifndef POSITION_H
#define POSITION_H

#include <stdbool.h>

#include "Types.h"
#include "PList.h"

//========= Tableau de T_position ==========//
Position* getTabPosition(int taille);
void freeTabPosition(int taille, Position* TabPosition);
void miseAzeroXOTableau(int taille, Position* TabPosition);

//=== Getteurs et Setteurs de T_position ===//
int getX(Position pos);
int getY(Position pos);
Position getPosition(int x, int y, Position* TabPosition);
Symboles getSymbole(Position pos);
int getVal(Position pos, Symboles sym);

void setSymbole(Symboles s, Position pos);

//======== Mise à jour des valeurs =========//
void majValPosition(Position pos, Symboles S);

//============ Test de validité ============//
bool equals(Position pos1, Position pos2);

//==========================================//
#endif