#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "PList.h"

// Initialisation de la structure.
struct cellule
{
    struct cellule* suiv;
    Position pos;
};

//==================================================================//
//======================= Liste de Positions =======================//
//==================================================================//

// Crée une liste vide.
PList empty_PL()
{
    return NULL;
}

// Ajoute "pos" à la liste.
PList add_PL(Position pos, PList l)
{
    PList cell = (PList) malloc(sizeof(cellule));
    cell->pos = pos;
    cell->suiv = l;
    return cell;
}

// Regarde si "pos" est dans la liste.
bool isInList_PL(Position pos, PList l)
{
	PList tmp = l ;

	if(tmp == NULL)
	{
		return false;
	}

	bool found = false;
	while(tmp != NULL)
	{
		if(equals(pos, tmp->pos))
		{
			found = true;
			break;
		}
		tmp = tmp->suiv;
	}
	return found;
}

// Supprime toute la liste
PList remAll_PL(PList l)
{
	PList tmp = l;
	while(tmp != NULL)
	{
		tmp = l->suiv;
		free(l);
		l = tmp;
	}
	return NULL;
}

//==================================================================//