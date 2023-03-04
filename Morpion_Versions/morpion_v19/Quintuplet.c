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
Quintuplet createQuintu(int x_of_origin, int y_of_origin, int x_direction, int y_direction, Position* TabPosition, int id)
{
    Quintuplet q;
    q.valquintuplet = 0;
    q.idQuintuplet = id;
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
    int id = 1;

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
                *q = createQuintu(x_of_origin, y_of_origin, tabXdir[i], tabYdir[i], TabPosition, id);
                id++;
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

// Recupere un Quintuplet dans une liste de Quintuplet avec son "id".
Quintuplet* getQuintWithId(int id, QList l)
{
    QList liste = l;
    while(!(isEmpty_QL(liste)))
    {
        Quintuplet* q = getQ_QL(liste);
        if(q->idQuintuplet == id)
        {
            return q;
        }
        liste = getNext_QL(liste);
    }
    printf("Error getQuintWithId : le quintuplet d'id \"%d\" n\'est pas dans la liste.\n", id);
    exit(EXIT_FAILURE);
}

// Met la valeur "partOfWinQuint" de toutes les positions du quintuplet à true.
void setPosQuintToWin(Quintuplet* q)
{
    for(int i = 0; i < NTUPLET; i++)
    {
        (q->pos[i])->partOfWinQuint = 1;
    }
}

//===============================================================================//
//================================ Vérifications ================================//
//===============================================================================//

// Regarde si le quintuplet est complet.
bool isQuintFull(Quintuplet* q)
{
    return q->valquintuplet >= (NTUPLET * 100);
}

//===============================================================================//
//================================= Suppréssion =================================//
//===============================================================================//

// Supprime les quintuplets qui ces deux positions en commun.
QList removeQuintWithTwoPos(QList l, Position p1, Position p2)
{
    QList parcours = getFst_QL(l);
    QList prevParcours = empty_QL();

    bool p1Exist, p2Exist;

    while (!isEmpty_QL(parcours))
    {
        p1Exist = false;
        p2Exist = false;
        Quintuplet* q = getQ_QL(parcours);
        for (int i = 0; i < NTUPLET; i++)
        {
            if(q->pos[i] == p1)
            {
                p1Exist = true;
            }
            else if(q->pos[i] == p2)
            {
                p2Exist = true;
            }
        }
        prevParcours = parcours;
        parcours = getNext_QL(parcours);

        if (p1Exist && p2Exist && !isEmpty_QL(parcours))
        {
           parcours = remPrev_QL(parcours);
        }
        else if(p1Exist && p2Exist && isEmpty_QL(parcours))
        {
            prevParcours = rem_QL(prevParcours);
        }
    }
    return getFst_QL(prevParcours);
}

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
        // Si le quintuplet est complet on le supprime lui et les quintuplets qui ont plus de une case commune.
        bool quintFull = isQuintFull(q);
        if (((oExist && xExist) || quintFull) && !isEmpty_QL(parcours))
        {
           parcours = remPrev_QL(parcours);
        }
        else if(((oExist && xExist) || quintFull) && isEmpty_QL(parcours))
        {
            prevParcours = rem_QL(prevParcours);
        }
        if(quintFull)
        {
            Position p0 = q->pos[0];
            Position p1 = q->pos[1];
            Position p3 = q->pos[3];
            Position p4 = q->pos[4];
            if(!isEmpty_QL(parcours))
            {
                parcours = removeQuintWithTwoPos(parcours, p0, p1);
                parcours = removeQuintWithTwoPos(parcours, p3, p4);
            }
            else
            {
                prevParcours = removeQuintWithTwoPos(prevParcours, p0, p1);
                prevParcours = removeQuintWithTwoPos(prevParcours, p3, p4);
            }
        }
    }
    return getFst_QL(prevParcours);
}

//===============================================================================//