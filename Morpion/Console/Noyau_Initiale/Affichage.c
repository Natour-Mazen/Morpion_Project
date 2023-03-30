#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Affichage.h"

//===============================================================================//
//=================================== Print =====================================//
//===============================================================================//

// Affiche le menu.
void printMenu()
{
    //system("color F"); // Couleur Windows
    //Ligne 1
    printf("\n\n\n\n\n\n");
    printWhiteLigne();
    // Ligne 2
    printWhiteBorder();
    // Ligne 3
    printf("\t\t\t\t\t ");
    printCarWithColor(2, WHITE_BACKGROUND);
    printf(" Bienvenue dans le tic tac toe 10*10 ");
    printCarWithColor(2, WHITE_BACKGROUND);
    printf("\n");
    // Ligne 4
    printWhiteBorder();
    // Ligne 5
    printf("\t\t\t\t\t ");
    printCarWithColor(14, WHITE_BACKGROUND);
    printf(" Menu Joueur ");
    printCarWithColor(14, WHITE_BACKGROUND);
    printf("\n");
    // Ligne 6
    printWhiteBorder();
    // Ligne 7
    printf("\t\t\t\t\t ");
    printCarWithColor(2, WHITE_BACKGROUND);
    printf("\t\t1 : Humain\t\t");
    printCarWithColor(2, WHITE_BACKGROUND);
    printf("\n");
    // Ligne 8
    printf("\t\t\t\t\t ");
    printCarWithColor(2, WHITE_BACKGROUND);
    printf("\t\t2 : IA\t\t\t");
    printCarWithColor(2, WHITE_BACKGROUND);
    printf("\n");
    // Ligne 9
    printWhiteBorder();
    // Ligne 10
    printWhiteLigne();
    printf("\n\n\n");
}

// Affiche le gagnant du jeu.
void printWinner(int joueur)
{
    const char* InitialeTypeSymbole[3] = {"VIDE", "X" , "O"};
    printf("\n\n\n\n");
    // Ligne 1
    printWhiteLigne();
    // Ligne 2
    printWhiteBorder();
    // Ligne 3 
    printWhiteBorder();
    // Ligne 4
    printf("\t\t\t\t\t ");
    printCarWithColor(2, WHITE_BACKGROUND);
    if(joueur == 1 || joueur == 2)
    {
        printf("\t   Le Joueur '%s' a gagne\t", InitialeTypeSymbole[joueur]);
    }
    else
    {
        printf("\t     Personne ne gagne \t\t");
    } 
    printCarWithColor(2, WHITE_BACKGROUND);
    printf("\n");
    // Ligne 5
    printWhiteBorder();
    // Ligne 6
    printWhiteBorder();
    // Ligne 7
    printWhiteLigne();
    printf("\n\n\n\n\n\n");
}

// Affiche le plateau dans la console.
void printPlateauDeJeu(Symboles jeu[TAILLEJEU][TAILLEJEU])
{
    //system("cls"); // Pour windows
    system("clear");
    printf("\n\n\n\n\n\n\n");
    printf("    \t  \t\t\t\t    ");
    for(int x = 0; x < TAILLEJEU; x++)
    {
		printf("%3d ", x);
	}
    printf("\n");
    for (int j = 0; j < TAILLEJEU; j++)
    {
        printf("\t\t\t\t\t%3d ", j);
        for (int i = 0; i < TAILLEJEU; i++)
        {
            if(jeu[i][j] == vide)
            {
                printf("  . ");
            }
            else if(jeu[i][j] == rond)
            {   
                printf(RED_TEXT);
                printf("  O ");
                printf(BASIC_TEXT);
            }
            else if(jeu[i][j] == croix)
            {
                printf("  X ");
            }
        }
        printf("\n");
    }
}

// Affiche le coup joué par le joueur.
void printLastPlay(TPlayer p, int X, int Y, bool change)
{
    static int x = 0;
    static int y = 0;
    static int joueur = 0;
    static bool firstTourOfTheGame = false;
    if(change)
    {
        x = X;
        y = Y;
        joueur = p.typeSymbole;
        firstTourOfTheGame = true;
    }
    if(firstTourOfTheGame)
    {
        const char* InitialeTypeSymbole[3] = {"VIDE", "X" , "O"};
        printf("\n\n");
        printf("\t\t\t\t     <> Dernier coup jouer par le joueur '%s' :\n", InitialeTypeSymbole[joueur]);
        printf("\t\t\t\t\t\t\t --> En X = %d\n", x);
        printf("\t\t\t\t\t\t\t --> En Y = %d\n", y);
    }
}

//===============================================================================//
//===================================== Read ====================================//
//===============================================================================//

// Lit le type du player, soit Humain soit Bot.
void readPlayer(int playerXouO, int* player)
{
    do{
        if(playerXouO == 1)
        {
           printf("\t\t\t\t\t %s Le joueur avec les croix ( X ) est : ", "\u279C"); 
        }
        else
        {
            printf("\t\t\t\t\t %s Le joueur avec les ronds ( O ) est : ", "\u279C");
        }

        scanf("%d", player);
    }while(*player != 1 && *player != 2);

}

// Permet à un Humain d'entrée une case pour jouer.
Position readPositionToPlay(TPlayer p, int* X, int* Y, Position* TabPosition, Symboles jeu[TAILLEJEU][TAILLEJEU])
{
    const char* InitialeTypeSymbole[3] = {"VIDE", "X" , "O"};
    bool foundCase = false;

    do
    {
        printf("\n\n\t\t\t\t\t         Joueur '%s'  : \n\n", InitialeTypeSymbole[p.typeSymbole]);
        printf("\t\t\t\t\t %s  Entrez le numero de la colonne(x) : ", "\u279C");
        scanf("%d", X);
        printf("\t\t\t\t\t %s  Entrez le numero de la ligne(y) : ", "\u279C");
        scanf("%d", Y);

        if(isEmptyCase(jeu, *X, *Y) && *X < TAILLEJEU && *Y < TAILLEJEU && *X >= 0 && *Y >= 0)
        {
            foundCase = true;
        }
        else
        {
            printPlateauDeJeu(jeu);
            printLastPlay(p, *X, *Y, false);

            printf("\n\t\t\t\t   %s Mauvaise coordonnees ! Veuillez reessayer.", "\u279C");
        }
    }while(foundCase == false);

    return &TabPosition[*X][*Y];
}

//===============================================================================//