#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "AffichageConsole.h"

//===============================================================================//
//============================= Affichage console ===============================//
//===============================================================================//

// Affiche n fois un caractère dans la console.
void printCarWithColor(int n, char* color)
{
    printf("%s", color);
    for(int i = 0; i < n; i++)
    {
        printf(" ");
    }
    printf(BASIC_TEXT);
}

// Affiche une ligne blanche dans la console.
void printWhiteLigne()
{
    printf("\t\t\t\t\t ");
    printCarWithColor(41, WHITE_BACKGROUND);
    printf("\n");
}

// Affiche une petite ligne de chaque côté dans la console.
void printWhiteBorder()
{
    printf("\t\t\t\t\t ");
    printCarWithColor(2, WHITE_BACKGROUND);
    printf("\t\t\t\t\t");
    printCarWithColor(2, WHITE_BACKGROUND);
    printf("\n");
}

// Supprime la dernière ligne écrite.
void clearALigne()
{
    // Met le curseur au début de la ligne.
    printf("\x1b[1F");
    // Supprime la ligne.
    printf("\x1b[2K");
}

// Vide le buffer de la console.
void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

//===============================================================================//