#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#include "position.h"

static int taille;

T_Postion **TabPosition;

void init_tab(int Taille){
	TabPosition = malloc(sizeof(T_Postion * ) * Taille);
	for(int i = 0 ;i < Taille ; i++){
		TabPosition[i] = malloc(sizeof(T_Postion) * Taille);
		for(int j = 0 ; j < Taille ; j++){
            TabPosition[i][j].X = i ;
            TabPosition[i][j].Y = j ;
			TabPosition[i][j].valeur = 0 ;
			TabPosition[i][j].valX = 0 ;
			TabPosition[i][j].valO = 0 ;
			TabPosition[i][j].Sy = vide ;
		}
	}
	taille = Taille;
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

void majValX(T_Postion *pos){
    pos->valeur --;
	pos->valX ++ ;
}

void majValO(T_Postion *pos){
    pos->valeur --;
	pos->valO ++ ;
}

int valPosX(T_Postion pos){
	return pos.valeur + pos.valX;
}

int valPosO(T_Postion pos){
	return pos.valeur + pos.valO;
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

int getVal(T_Postion pos , Symboles sym){
	
	if(sym == croix){
		return(valPosX(pos));
	}else{
		if(sym == rond){
			return valPosO(pos);
		}else{
			return pos.valeur;
		}
	}
}

int getValP(T_Postion *pos , Symboles sym){

	if(sym == croix){
		return(valPosX(*pos));
	}else{
		if(sym == rond){
			return valPosO(*pos);
		}else{
			return pos->valeur;
		}
	}
}

void SetSymbole(Symboles S , T_Postion *pos){

	pos->Sy = S ;
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

Listpos init(){
    return NULL;
}

void addInList(T_Postion *pos, Listpos l){


    Listpos cell = malloc(sizeof(struct cellule));
    cell->pos = pos;
    cell->suiv = l;
    l=cell;

}

bool isInList(T_Postion *pos , Listpos list){
	
	Listpos tmp = list ;

	if(tmp == NULL){
		return false;
	}else{

		bool found = false;
		while(tmp != NULL && !found){
			if (equalsP(pos,tmp->pos)){
				found = true;
			}
			tmp=tmp->suiv;
		}

		return found ;
	}
}


void majValPosition(T_Postion *pos , Listpos list , Symboles S){
	if (isInList(pos,list)){
		if(S == croix){
			majValX(pos);
		}else{
			majValO(pos);
		}
	}
}

void miseAzeroXO(){
	for(int i = 0 ; i< taille ; i++){
		for(int j = 0 ; j< taille ; j++){
			TabPosition[i][j].valeur = TabPosition[i][j].valeur + TabPosition[i][j].valX + TabPosition[i][j].valO;
			TabPosition[i][j].valX = 0;
			TabPosition[i][j].valO = 0;

		}
	}
}


void decroitValcase(T_Postion *pos){
	pos->valeur --;
}

void liberationTab(){
	for (int i = 0 ; i < taille ; i++)
	{
			free(TabPosition[i]);
	}
	free(TabPosition);
}	

void liberationListPos(Listpos l){

	Listpos tmp = l;
	while(tmp != NULL && l->suiv !=NULL){
		tmp = l->suiv;
		free(l);
		l = tmp;
	}

}