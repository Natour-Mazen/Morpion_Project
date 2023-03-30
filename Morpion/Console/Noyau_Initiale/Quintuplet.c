#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Quintuplet.h"
#include "Position.h"

//===============================================================================//
//========================== Création de Quintuplets ============================//
//===============================================================================//

//Alloue une structure Quintuplet en mémoire
Quintuplet* initQuintu() 
{
    return (Quintuplet*) malloc(sizeof(Quintuplet));
}

//Retourne un quintuplet de NTUPLET cases
Quintuplet createQuintu(int x_of_origin, int y_of_origin, int x_direction, int y_direction, Position* TabPosition)
{
    Quintuplet q;
    q.valquintuplet = 0;
    for (int i = 0; i < NTUPLET; i++)
    {
        q.pos[i] = getPosition(x_of_origin, y_of_origin, TabPosition);
        x_of_origin += x_direction;
        y_of_origin += y_direction;
    }
    return q;
}

//===============================================================================//
//============================= Création de liste ===============================//
//===============================================================================//

//Crée la liste principale de quintuplets vides en début de jeu.
QList makeMainList(Position* TabPosition) 
{
    QList mainList = empty_QL();
    Quintuplet* q;

    int NtupletMoinsUn = NTUPLET - 1;
    // pas de "tabYstart" car toujours la même chose pour les 4 boucles.
    int tabXend[4] = {NtupletMoinsUn, 0, NtupletMoinsUn, NtupletMoinsUn};
    int tabYstart[4] = {0, 0, 0, NtupletMoinsUn};
    int tabYend[4] = {0, NtupletMoinsUn, NtupletMoinsUn, 0};
    int tabXdir[4] = {1, 0, 1, 1};
    int tabYdir[4] = {0, 1, 1, -1};

    for(int i = 0; i < 4; i++)
    {
        for(int x_of_origin = 0; x_of_origin < TAILLEJEU - tabXend[i]; x_of_origin++)
        {
            for(int y_of_origin = tabYstart[i]; y_of_origin < TAILLEJEU - tabYend[i]; y_of_origin++)
            {
                q = initQuintu();
                *q = createQuintu(x_of_origin, y_of_origin, tabXdir[i], tabYdir[i], TabPosition);
                mainList = addLst_QL(mainList, q);
            }
        }
    }
    return getFst_QL(mainList);
}

//===============================================================================//
//================================== Getteurs ===================================//
//===============================================================================//

// Recupere tout les quinuplets qui passe par la postion "pos".
QList getAllQuints(Position pos, QList* l)
{
    QList result_list = empty_QL();
    QList parcours = getFst_QL(*l);
    QList prevParcours = empty_QL();

    bool found;

    //on parcourt l'integralite de notre liste "parcours".
    while(!isEmpty_QL(parcours)) 
    {
        found = false;
        //on compare chaque case du quintuplet avec notre case recherchee
        for(int i = 0; i < NTUPLET; i++)
        {
            if(equals(pos, (getQ_QL(parcours))->pos[i]))
            {
                //si on trouve une case identique, on arréte le parcours du quintuplet, on passe à sa suppression sinon on passe au quintuplet suivant
                found = true;
                break;
            }
        }
        prevParcours = parcours;
        parcours = getNext_QL(parcours);
        if(found)
        {
            result_list = addFst_QL(result_list, getQ_QL(prevParcours));
            if (!isEmpty_QL(parcours))
            {
                parcours = remPrev_QL(parcours);
            }
            else
            {
                prevParcours = rem_QL(prevParcours);
            }
        }
    }
    *l = getFst_QL(prevParcours);
    return result_list;
}


//===============================================================================//
//================================= Suppréssion =================================//
//===============================================================================//

// Enleve tout les quintuplets qui ne peuvent plus gagner.
QList removeClosedQuints(QList l)
{
    QList parcours = getFst_QL(l);
    QList prevParcours = empty_QL();

    bool xExist, oExist;

    while (!isEmpty_QL(parcours))
    {
        oExist = false;
        xExist = false;
        Quintuplet* q = getQ_QL(parcours);
        for (int i = 0; i < NTUPLET; i++)
        {
            if (q->pos[i]->Sy == rond)
            {
                oExist = true;
            }
            if (q->pos[i]->Sy == croix)
            {
                xExist = true;
            }
        }
        prevParcours = parcours;
        parcours = getNext_QL(parcours);
        if (oExist && xExist && !isEmpty_QL(parcours))
        {
           parcours = remPrev_QL(parcours);
        }
        else if(oExist && xExist && isEmpty_QL(parcours))
        {
            prevParcours = rem_QL(prevParcours);
        }
    }
    return getFst_QL(prevParcours);
}

//===============================================================================//
