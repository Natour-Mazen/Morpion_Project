#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Types.h"


/* ---------------------- CREATION --------------------- */

void initListeQuint(listequintuplet *l)
{
    *l=NULL;
}


/* -------------------- VERIFICATION --------------------- */

bool listeVideLQuint(listequintuplet l)
{
    return (l==NULL);
}


/* --------------------- OPERTATION AJOUT --------------------- */

listequintuplet ajoutEnTeteLQuint(listequintuplet l, Quintuplet *mydata)
{
    listequintuplet racine = malloc(sizeof(*racine));

    racine->Qdata=mydata;

    racine->suiv = l;
    racine->prec = NULL;

    if (! listeVideLQuint(l))
        l->prec = racine;

    l = racine;
    return l;
}


listequintuplet ajoutEnFinLQuint(listequintuplet l, Quintuplet* mydata)
{
    listequintuplet racine = malloc(sizeof(*racine));
    listequintuplet ptr = l ;

    racine->Qdata=mydata;

    racine->suiv = NULL;

    if (listeVideLQuint(l))
    {
        racine->prec = NULL;
        l = racine;
    }
    else
    {
        while (ptr->suiv != NULL)
            ptr = ptr->suiv;
        ptr->suiv = racine;
        racine->prec=ptr;
    }

    return l;
}


listequintuplet ajoutEnNLQuint(listequintuplet l, int pos, Quintuplet* mydata)
{
    int numero_cellule = 1;
    listequintuplet courant = l;
    while(numero_cellule != pos)
    {
        courant = courant->suiv;
        numero_cellule ++;
    }

    listequintuplet nouv = malloc(sizeof(*nouv));
    (nouv->Qdata)=mydata;

    nouv->suiv = courant->suiv;
    nouv->prec = courant;
    courant->suiv->prec = nouv;
    courant->suiv = nouv;

    return l;
}



/* --------------------- OPERTATION SUPPRESION --------------------- */

listequintuplet suppEnTeteLQuint(listequintuplet l)
{
    listequintuplet liste = l ;
    if(listeVideLQuint(l))
        return NULL;
    else if(liste->suiv == NULL && liste->prec == NULL )
    {
        free(l->Qdata);
        free(liste);
        return NULL;
    }
    else
    {
        l = l->suiv;
        l->prec = NULL;
        free(liste->Qdata);
        free(liste);
        return l;
    }

}


listequintuplet suppEnFinLQuint(listequintuplet l)
{
    listequintuplet liste = l;
    if(l->suiv == NULL && l->prec == NULL )
    {
        free(l->Qdata);
        free(l);
        return NULL;
    }
    else if (listeVideLQuint(l))
        return NULL;
    else{
        while(liste->suiv != NULL)
        {
            liste=liste->suiv;
        }
        if (liste->prec == NULL){
            // si une seule celule dans la liste
            free(liste->Qdata);
            free(liste);
            return NULL;
        }
        else{
            //sinon cas general
            liste->prec->suiv = NULL;
            free(liste->Qdata);
            free(liste);
            return l;
        }
    }
}


listequintuplet suppEnNLQuint(listequintuplet l, int pos)
{
    if(pos > getNbreCellLQuint(l))
    {
        return l;
    }
    listequintuplet liste = l ;
    if (l->suiv == NULL)
        liste = suppEnFinLQuint(liste);
    else
    {
        for(int i=0; i<pos;i++)
        {
            liste = liste ->suiv;
        }
        liste->prec->suiv = liste->suiv;
        if (liste->suiv != NULL)
            liste->suiv->prec = liste->prec;
        free(liste->Qdata);
        free(liste);

    }

    return l;
}



/* --------------------- OPERTATION CHANGEMENT DE POINTEUR --------------------- */

listequintuplet getptrFirstCellLQuint(listequintuplet l)
{
    if(listeVideLQuint(l))
        return NULL;
    else
        return l;
}


listequintuplet getptrLastCellLQuint(listequintuplet l)
{
    listequintuplet liste = l;
    while(liste->suiv != NULL)
    {
        liste=liste->suiv;
    }
    return liste;
}


listequintuplet getptrNextCellLQuint(listequintuplet l)
{
    listequintuplet liste = l;
    if(liste->suiv == NULL)
        return NULL;
    liste = l->suiv;
    return liste;
}


listequintuplet getptrPrevCellLQuint(listequintuplet l)
{
    listequintuplet liste = l;
    if(liste->prec == NULL)
        return NULL;
    liste = l->prec;
    return liste;
}


listequintuplet rembobiner(listequintuplet l)
{
    if(listeVideLQuint(l))
        return NULL;
    else if (l->prec == NULL && l->suiv == NULL)
        return l;
    else
    {
        while(l->prec != NULL)
        l = l->prec;
        return l;
    }
}



/* --------------------- OPERTATION DIVERSES --------------------- */

Quintuplet* getPtrDataLQuint(listequintuplet l)
{
    if(listeVideLQuint(l))
    {
        return NULL;
    }
    else
    {
        return l->Qdata;
    }
}


int getNbreCellLQuint(listequintuplet l)
{
    int res=1;
    if(listeVideLQuint(l))
        return res=0 ;
    else
    {
        rembobiner(l);
        while(l->suiv !=NULL)
        {
            res ++;
            l = l->suiv;
        }
        return res;
    }
}


listequintuplet vidertoutLQuint(listequintuplet l)
{
    if(listeVideLQuint(l))
        return NULL;
    else
    {
        while(!listeVideLQuint(l))
        {
            l = suppEnFinLQuint(l);
        }
        return l;
    }
}






