#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "QList.h"

//=== Définition de la structure ===//
struct T_cell
{
    QList suiv;
    QList prec;
    Q Qdata; //pointeur vers un quintuplet
};

//===============================================================================//
//============================ Opération de Création ============================//
//===============================================================================//

// Donne une liste vide.
QList empty_QL()
{
    return NULL;
}

//===============================================================================//
//========================== Opération de Vérification ==========================//
//===============================================================================//

// Regarde si la liste est vide.
bool isEmpty_QL(QListConst l)
{
    return (l == NULL);
}

// Regarde si le prochain element existe.
bool isNextEmpty_QL(QListConst l)
{
    if(isEmpty_QL(l))
    {
        return true;
    }
    return (l->suiv == NULL);
}

// Regarde si le element précédent existe.
bool isPrevEmpty_QL(QListConst l)
{
    if(isEmpty_QL(l))
    {
        return true;
    }
    return (l->prec == NULL);
}

//===============================================================================//
//============================ Opération de Getteur =============================//
//===============================================================================//

// Retourne le quintuplet de l'élément.
Q getQ_QL(QListConst l)
{
    if(isEmpty_QL(l))
    {
        return NULL;
    }
    return l->Qdata;
}

// Retourne le prochain élément de la liste.
QList getNext_QL(QListConst l)
{
    if(isNextEmpty_QL(l))
    {
        return empty_QL();
    }
    return l->suiv;
}

// Retourne le précédent élément de la liste.
QList getPrev_QL(QListConst l)
{
    if(isPrevEmpty_QL(l))
    {
        return empty_QL();
    }
    return l->prec;
}

// Retourne le premier élément de la liste.
QList getFst_QL(QList l)
{
    QList liste = l;
    while(!isPrevEmpty_QL(liste))
    {
        liste = getPrev_QL(liste);
    }
    return liste;
}

// Retourne le dernier élément de la liste.
QList getLst_QL(QList l)
{
    QList liste = l;
    while(!isNextEmpty_QL(liste))
    {
        liste = getNext_QL(liste);
    }
    return liste;
}

// Retourne la longueur de la liste.
int getLen_QL(QList l)
{
    QList parcours = l;
    if(isEmpty_QL(parcours))
    {
        return 0 ;
    }
    else
    {
        int res = 1;
        parcours = getFst_QL(parcours);
        while(!isNextEmpty_QL(parcours))
        {
            res ++;
            parcours = getNext_QL(parcours);
        }
        return res;
    }
}

//===============================================================================//
//============================== Opération d'ajout ==============================//
//===============================================================================//

// Ajoute un quintuplet après cet élément.
QList addNext_QL(QList l, QConst q)
{
    QList newPiece = (QList) malloc(sizeof(T_cell));

    newPiece->Qdata = q;

    newPiece->suiv = getNext_QL(l);
    newPiece->prec = l;

    if(!isEmpty_QL(l))
    {
        if(!isNextEmpty_QL(l))
        {
            l->suiv->prec = newPiece;
        }
        l->suiv = newPiece;
    }

    return newPiece;
}

// Ajoute un quintuplet avant cet élément.
QList addPrev_QL(QList l, QConst q)
{
    QList newPiece = (QList) malloc(sizeof(T_cell));

    newPiece->Qdata = q;

    newPiece->suiv = l;
    newPiece->prec = getPrev_QL(l);

     if(!isEmpty_QL(l))
     {
        if(!isPrevEmpty_QL(l))
        {
            l->prec->suiv = newPiece;
        }
        l->prec = newPiece;
     }
        
    return newPiece;
}

// Ajoute un quintuplet au début de la liste.
QList addFst_QL(QList l, QConst q)
{
    QList fst = getFst_QL(l);

    return addPrev_QL(fst, q);
}

// Ajoute un quintuplet à la fin de la liste.
QList addLst_QL(QList l, QConst q)
{
    QList lst = getLst_QL(l);
        
    return addNext_QL(lst, q);
}

//===============================================================================//
//========================== Opération de Suppression ===========================//
//===============================================================================//

// Supprime l'élément actuel et on retourne le suivant.
QList rem_QL(QList l)
{
    QList liste;
    if(isEmpty_QL(l))
    {
        return empty_QL();
    }
    else if(isNextEmpty_QL(l) && isPrevEmpty_QL(l))
    {
        free(l);
        return empty_QL();
    }
    else if(!isNextEmpty_QL(l))
    {
        liste = getNext_QL(l);
        liste->prec = getPrev_QL(l);
        if(!isPrevEmpty_QL(l))
        {
            l->prec->suiv = liste;
        }
    }
    else
    {
        liste = getPrev_QL(l);
        liste->suiv = empty_QL();
    }
    free(l);
    return liste;
}

// Supprime l'élément qui est après.
QList remNext_QL(QList l)
{
    rem_QL(getNext_QL(l));
    return l;
}

// Supprime l'élément qui est avant.
QList remPrev_QL(QList l)
{
    rem_QL(getPrev_QL(l));
    return l;
}

// Supprime un élément au début de la liste.
QList remFst_QL(QList l)
{
    QList liste = rem_QL(getFst_QL(l));
    if(isEmpty_QL(liste))
    {
        return empty_QL();
    }
    return l;
}

// Supprime un élément à la fin de la liste.
QList remLst_QL(QList l)
{
    QList liste = rem_QL(getLst_QL(l));
    if(isEmpty_QL(liste))
    {
        return empty_QL();
    }
    return l;
}

// Supprime toute la liste.
QList remAll_QL(QList l)
{
    if(isEmpty_QL(l))
    {
        return empty_QL();
    }
    else
    {
        while(!isEmpty_QL(l))
        {
            l = rem_QL(l);
        }
        return l;
    }
}

// Supprime toute la liste + les elements qu'elle contient.
QList remAllPlusElement_QL(QList l)
{
    if(isEmpty_QL(l))
    {
        return empty_QL();
    }
    else
    {
        while(!isEmpty_QL(l))
        {
            free(getQ_QL(l));
            l = rem_QL(l);
        }
        return l;
    }
}

//===============================================================================//
//============================== Autres Opération ===============================//
//===============================================================================//

// Fusionne deux listes.
QList concat_QL(QList debut, QList* fin)
{
    QList tempDebut = getLst_QL(debut);
    QList tempFin = getFst_QL(*fin);
    if(isEmpty_QL(tempDebut))
    {
        *fin = NULL;
        return tempFin;
    }
    if(!isEmpty_QL(tempFin))
    {
        // On connecte la fin de "debut" au debut de "fin".
        tempDebut->suiv = tempFin;
        tempFin->prec = tempDebut;
        // "fin" est mainteant vide.
        *fin = NULL;
    }
    return debut;
}

// Donne une copie de la liste "l".
QList duplicate_QL(QList l)
{
    QList parcours = getFst_QL(l);
    QList newListe = empty_QL();
    while(!isEmpty_QL(parcours))
    {
        newListe = addLst_QL(newListe, getQ_QL(parcours));
        parcours = getNext_QL(parcours);
    }
    return getFst_QL(newListe);
}

//===============================================================================//