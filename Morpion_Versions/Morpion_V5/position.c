#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#include "position.h"


T_Postion **TabPosition;

void init_tab(int Taille){
	TabPosition = malloc(sizeof(T_Postion * ) * Taille);
	for(int i = 0 ;i < Taille ; i++){
		TabPosition[i] = malloc(sizeof(T_Postion) * Taille);
		for(int j = 0 ; j < Taille ; j++){
            TabPosition[i][j].X = i ;
            TabPosition[i][j].Y = j ;
			TabPosition[i][j].valeur = 0 ;
			TabPosition[i][j].Sy = vide ;
		}
	}
}

T_Postion *PosP(int x , int y){  //renvoie un pointeur

	TabPosition[x][y].valeur ++ ;

	return &(TabPosition[x][y]);
}

T_Postion Pos(int x , int y){     //renvoie une copie donc valeur fixe pour la t_position

	TabPosition[x][y].valeur ++ ;

	return TabPosition[x][y];
}

int getX(T_Postion pos){
    return pos.X;
}

int getXP(T_Postion *pos){
    return pos->X;
}

int getY(T_Postion pos){
    return pos.Y;
}

int getYP(T_Postion *pos){
    return pos->Y;
}

int getVal(T_Postion pos){

	return pos.valeur;
}

int getValP(T_Postion *pos){

	return pos->valeur;
}

void SetSymbole(Symboles S , T_Postion pos){

	pos.Sy = S ;
}

Symboles getSymbole(T_Postion pos){

	return pos.Sy;
}

Symboles getSymboleP(T_Postion *pos){

	return pos->Sy;
}

bool equals(T_Postion pos1 , T_Postion pos2){

	return ((pos1.X == pos2.X) && (pos1.Y == pos2.Y));

}


bool equalsP(T_Postion *pos1 , T_Postion *pos2){

	return ((pos1->X == pos2->X) && (pos1->Y == pos2->Y));

}

int distanceTpos(T_Postion pos1 , T_Postion pos2){
	return sqrt(pow(pos2.X - pos1.X,2) + pow(pos2.Y - pos1.Y,2));
}

int distanceTposP(T_Postion *pos1 , T_Postion *pos2){
	return sqrt(pow(pos2->X - pos1->X,2) + pow(pos2->Y - pos1->Y,2));
}

