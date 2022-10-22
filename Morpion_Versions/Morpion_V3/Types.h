#ifndef TYPES_H
#define TYPES_H

#define NTUPLET 5
#define TAILLEJEU 10

 ///------------- DEFINTION DES TYPES STRUCTURE DU JEU -------------------------///

typedef enum{vide, croix, rond } Symboles;
typedef enum{Humain , IA } t_joueur;

typedef Symboles TabMorpion[TAILLEJEU][TAILLEJEU];

typedef struct {
    int X, Y;
    int valeur;
    Symboles Sy;
} T_Postion;


typedef struct {
    T_Postion pos[NTUPLET];
    int valquintuplet;
} Quintuplet;


typedef struct T_cell{
    struct T_cell  *suiv;
    struct T_cell  *prec;
    Quintuplet *Qdata; //pointeur vers un quintuplet
} *listequintuplet;


typedef struct {
    t_joueur typejoueur;
    Symboles typeSymbole;
    listequintuplet listeGagnant , listePerdante;
} TPlayer;





 ///------------- OPERATIONS SUR LES LISTE DE QUINTUPLETS -------------------------///



/************************** CREATION ***************************/
void initListeQuint(listequintuplet *l);

/************************ VERIFICATION **************************/
bool listeVideLQuint(listequintuplet l);

/*************************** OPERTATION AJOUT ***************************/
listequintuplet ajoutEnTeteLQuint(listequintuplet l, Quintuplet *mydata);
listequintuplet ajoutEnFinLQuint(listequintuplet l, Quintuplet* mydata);
listequintuplet ajoutEnNLQuint(listequintuplet l, int pos, Quintuplet* mydata);

/*************************** OPERTATION SUPPRESION ***************************/
listequintuplet suppEnTeteLQuint(listequintuplet l);
listequintuplet suppEnFinLQuint(listequintuplet l);
listequintuplet suppEnNLQuint(listequintuplet l, int pos);

/*************************** OPERTATION CHANGEMENT DE POINTEUR ***************************/
listequintuplet getptrFirstCellLQuint(listequintuplet l);
listequintuplet getptrLastCellLQuint(listequintuplet l);
listequintuplet getptrNextCellLQuint(listequintuplet l);
listequintuplet getptrPrevCellLQuint(listequintuplet l);
listequintuplet rembobiner(listequintuplet l);

/************************** OPERTATION DIVERSES ***************************/
Quintuplet* getPtrDataLQuint(listequintuplet l);
int getNbreCellLQuint(listequintuplet l);
listequintuplet vidertoutLQuint(listequintuplet l);






















#endif
