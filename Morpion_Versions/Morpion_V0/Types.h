#ifndef TYPES_H
#define TYPES_H

#define NTUPLET 5
#define TAILLEJEU10x10 10

typedef enum{vide, croix, rond } Symboles;
typedef enum{Humain , IA } t_joueur;

typedef Symboles TabMorpion[TAILLEJEU10x10][TAILLEJEU10x10];

typedef struct {
    const int X, Y;
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


#endif
