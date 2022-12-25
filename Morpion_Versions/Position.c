#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "Position.h"

//==================================================================//
//=================== Tableau de T_position init ===================//
//==================================================================//

// Initialise le tableau de positions.
static Position* init_tabPosition(int taille)
{
	Position* TabPosition = (Position*) malloc(sizeof(Position) * taille);

	for(int i = 0; i < taille; i++)
	{
		TabPosition[i] = (Position) malloc(sizeof(struct t_position) * taille);
		for(int j = 0; j < taille; j++)
		{
            TabPosition[i][j].X = i;
            TabPosition[i][j].Y = j;
			TabPosition[i][j].valeur = 0;
			TabPosition[i][j].valX = 0;
			TabPosition[i][j].valO = 0;
			TabPosition[i][j].Sy = vide;
		}
	}
	return TabPosition;
}

// Donne le tableau de positions initialisé.
Position* getTabPosition(int taille)
{
	static Position* tabPosition = NULL;
	if(tabPosition == NULL)
	{
		tabPosition = init_tabPosition(taille);
	}
	return tabPosition;
}

// Fait un free de tout le tableau.
void freeTabPosition(int taille, Position* TabPosition)
{
	for(int i = 0; i < taille; i++)
	{
		free(TabPosition[i]);
	}
	free(TabPosition);
}

// Met les valeurs de X et O du tableau de position à 0 et les ajoute à la valeur de la position.
void miseAzeroXOTableau(int taille, Position* TabPosition)
{
	for(int i = 0; i < taille; i++)
	{
		for(int j = 0; j < taille; j++)
		{
			TabPosition[i][j].valeur = TabPosition[i][j].valeur + TabPosition[i][j].valX + TabPosition[i][j].valO;
			TabPosition[i][j].valX = 0;
			TabPosition[i][j].valO = 0;
		}
	}
}

//==================================================================//
//===================== Getteurs de T_position =====================//
//==================================================================//

// Retourne la position en X.
int getX(Position pos)
{
    return pos->X;
}

// Retourne la position en Y.
int getY(Position pos)
{
    return pos->Y;
}

Position getPosition(int x, int y, Position* TabPosition)
{
	(TabPosition[x][y].valeur)++;

	return &(TabPosition[x][y]);
}

// Retourne le symbole d'une position.
Symboles getSymbole(Position pos)
{
	return pos->Sy;
}

// Retourne la valeur de la position + la valeur X.
static int getVal_plus_valX(Position pos)
{
	return pos->valeur + pos->valX;
}

// Retourne la valeur de la position + la valeur O.
static int getVal_plus_valO(Position pos)
{
	return pos->valeur + pos->valO;
}

// Retourne la valeur en fonction du symbole qu'il y a sur la position.
int getVal(Position pos, Symboles sym)
{
	if(sym == croix)
	{
		return getVal_plus_valX(pos);
	}
	if(sym == rond)
	{
		return getVal_plus_valO(pos);
	}
	return pos->valeur;
}

// Met un symbole à une position.
void setSymbole(Symboles s, Position pos)
{
	pos->Sy = s ;
}

//==================================================================//
//====================  Mise à jour des valeurs ====================//
//==================================================================//

// Augmente la valeur de X et diminue la valeur de la position.
static void majValX(Position pos)
{
    (pos->valeur)--;
	(pos->valX)++;
}

// Augmente la valeur de O et diminue la valeur de la position.
static void majValO(Position pos)
{
    (pos->valeur)--;
	(pos->valO)++;
}

//// Augmente la valeur de X ou O et diminue la valeur de la position.
void majValPosition(Position pos, Symboles S)
{
	if(S == croix)
	{
		majValX(pos);
	}
	else
	{
		majValO(pos);
	}
}

//==================================================================//
//======================== Test de validité ========================//
//==================================================================//

//Regarde si deux positions sont au même endroit.
bool equals(Position pos1, Position pos2)
{
	return ((pos1->X == pos2->X) && (pos1->Y == pos2->Y));
}

//==================================================================//