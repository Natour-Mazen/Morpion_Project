#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Quintuplet.h"

Quintuplet *initQuintu ()
{
    Quintuplet *q;
    q = (Quintuplet*)malloc(sizeof(Quintuplet));

    return q;
}

bool existeQuintu (int x_of_origin, int y_of_origin, int x_direction, int y_direction)
{
    bool result = true;

    if (x_direction == 0 && y_direction == 0) return false;

    if (x_direction != 0)
    {
        if (x_direction > 0)
        {
            if ((x_of_origin + NTUPLET - 1) < TAILLEJEU10x10) result = true; //pas besoin d'aller chercher si result a ete modifie car c'est le premier if
            else result = false;
        }
        else if ((x_of_origin - NTUPLET + 1) >= 0 && result != false) result = true;
        else result = false;
    }

    if (y_direction != 0)
    {
        if (y_direction > 0)
        {
            if ((y_of_origin + NTUPLET - 1) < TAILLEJEU10x10 && result != false) result = true;
            else result = false;
        }
        else if ((y_of_origin - NTUPLET + 1) >= 0 && result != false) result = true;
        else result = false;
    }

    return result;
}

Quintuplet createQuintu(int x_of_origin, int y_of_origin, int x_direction, int y_direction)
{
    Quintuplet q;
    q.valquintuplet = 0;
    for (int i = 0 ; i < NTUPLET ; i++)
    {
        q.pos[i].X = x_of_origin;
        q.pos[i].Y = y_of_origin;
        //printf("(%d,%d)", q.pos[i].X, q.pos[i].Y);
        q.pos[i].valeur = 1;
        q.pos[i].Sy = vide;

        x_of_origin += x_direction;
        y_of_origin += y_direction;
        q.valquintuplet += q.pos[i].valeur;
        //printf("-");
    }
    //printf("\n");
    return q;
}
