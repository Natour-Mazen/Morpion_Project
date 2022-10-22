#ifndef POSITION_H
#define POSITION_H
#include <stdbool.h>


#include "Types.h"

T_Postion **TabPosition;

void init_tab(int Taille);

T_Postion *getPos(int x , int y);
T_Postion Pos(int x , int y);

int getX(T_Postion pos);
int getXP(T_Postion *pos);

int getY(T_Postion pos);
int getYP(T_Postion *pos);

int getVal(T_Postion pos);
int getValP(T_Postion *pos);

void SetSymbole(Symboles S , T_Postion pos);

Symboles getSymbole(T_Postion pos);
Symboles getSymboleP(T_Postion *pos);

bool idem(T_Postion pos1 , T_Postion pos2);
bool idemP(T_Postion *pos1 , T_Postion *pos2);

int distanceTpos(T_Postion pos1 , T_Postion pos2);
int distanceTposP(T_Postion *pos1 , T_Postion *pos2);


#endif
