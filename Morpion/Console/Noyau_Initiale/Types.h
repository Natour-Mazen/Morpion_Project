#ifndef TYPES_H
#define TYPES_H

#define NTUPLET 5
#define TAILLEJEU 10

 ///===== DEFINTION DES TYPES STRUCTURE DU JEU =====///

typedef enum{vide, croix, rond} Symboles;
typedef enum{Humain, IA} t_joueur;


/*=== Une position sur la grille. ===*/
typedef struct t_position
{
    int X, Y;
    int valeur;
    int valX;
    int valO;
    Symboles Sy;
} *Position;

/*=== Un Quintuplet. ===*/
typedef struct Quintuplet
{
    Position pos[NTUPLET];
    int valquintuplet;
} Quintuplet;

#ifndef QLIST_H
    // On include les listes de Quintuplets.
    #include "QList.h"

    #ifndef TYPES2_H
    #define TYPES2_H

    /*=== Un joueur ===*/
    typedef struct TPlayer
    {
        t_joueur typejoueur;
        Symboles typeSymbole;
        QList listeGagnant;
        QList listePerdante;
    } TPlayer;

    #endif
#endif

#endif

