#ifndef POSITION_H
#define POSITION_H
#include <stdbool.h>


#include "Types.h"


typedef struct cellule{
    struct cellule  *suiv;
    T_Postion *pos;
} *Listpos;


extern T_Postion **TabPosition;

void init_tab(int Taille);

T_Postion *PosP(int x , int y);
T_Postion Pos(int x , int y);

int getX(T_Postion pos);
int getXP(T_Postion *pos);

void majValX(T_Postion *pos);
void majValO(T_Postion *pos);

int valPosX(T_Postion pos);
int valPosO(T_Postion pos);

int getY(T_Postion pos);
int getYP(T_Postion *pos);

int getVal(T_Postion pos , Symboles sym);
int getValP(T_Postion *pos , Symboles sym);

void SetSymbole(Symboles S , T_Postion *pos);

Symboles getSymbole(T_Postion pos);
Symboles getSymboleP(T_Postion *pos);

bool equals(T_Postion pos1 , T_Postion pos2);
bool equalsP(T_Postion *pos1 , T_Postion *pos2);

int distanceTpos(T_Postion pos1 , T_Postion pos2);
int distanceTposP(T_Postion *pos1 , T_Postion *pos2);

Listpos init();
void addInList(T_Postion *pos , Listpos l);
bool isInList(T_Postion *pos , Listpos list);
void majValPosition(T_Postion *pos , Listpos list, Symboles S);
void miseAzeroXO();
void decroitValcase(T_Postion *pos);

void liberationTab();
void liberationListPos(Listpos l);


#endif
