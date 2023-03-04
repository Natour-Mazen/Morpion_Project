#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

#define NTUPLET 5 // Uniquement 5 avec les multiples allignements.
#define TAILLEJEU 20
#define TAILLEECRANJEU 40*TAILLEJEU
// pour Taillejeu = 10
// alors TAILLEECRANJEU = 60*TAILLEJEU
// pour Taillejeu = 20
// alors TAILLEECRANJEU = 40*TAILLEJEU


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
    int partOfWinQuint; // int et non bool car la fwrite de struct pose problème.
    bool alreadyVisited; // Seulement pour la SDL pour eviter de recolorier une case qui a deja ete colorier
} *Position;

/*=== Un Quintuplet. ===*/
typedef struct Quintuplet
{
    Position pos[NTUPLET];
    int valquintuplet;
    int idQuintuplet; // utile pour la sauvegarde.
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
        int winQuints;
    } TPlayer;

    #endif
#endif

#endif

