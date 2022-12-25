#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
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
    system("cls"); // Pour windows
   // system("clear");
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
                printf(BLUE_TEXT);
                printf("  X ");
                printf(BASIC_TEXT);
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

// Lit un caractère pour faire les opérations de sauvegarde, chargement de partie et que fin de jeu.
char readOtherOptions()
{
    char res = ' ';
    viderBuffer();
    printf("\n\n\n\n");
    bool foundChar = false;
    do
    {
        printf("\n\n\t\t\t\t\t %s Entrez une commande (continuer: 'n', sauvegarde: 's', chargement: 'l' et quitter: 'q') : ", "\u279C");
        scanf("%c", &res);
        viderBuffer();

        if(res == 'n' || res == 'q' || res == 's' || res == 'l' || res == 'N' || res == 'Q' || res == 'S' || res == 'L')
        {
            foundChar = true;
        }
        else
        {
            clearALigne();
            clearALigne();
            clearALigne();

            printf("\t\t\t\t   %s Mauvaise Commande ! Veuillez reessayer.", "\u279C");
        }
    }while(foundChar == false);

    return res;
}

//===============================================================================//
//=================================== SDL =====================================//
//===============================================================================//
//Envoyer un msg à l'ecran
void messageSDL(char *myTitle, char *myMessage){
        const SDL_MessageBoxButtonData buttons[] = {
        { /* .flags, .buttonid, .text */        0, 0, "ok" },
 //       { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
 //       { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 255 }
        }
    };
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL, /* .window */
        myTitle, /* .title */
        myMessage, /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
        //return 1;
    }
   /* if (buttonid == -1) {
        SDL_Log("no selection");
    } else {
        SDL_Log("selection was %s", buttons[buttonid].text);
    }*/

}

//Affichage Menu et initilation Joueurs
void MySDLMenu(TPlayer *playerX, TPlayer *playerO)
{
    const int WINDOW_WIDTH = 550;
    const int WINDOW_HEIGHT = 500;
    const char* WINDOW_TITLE = "Morpion Menu";

    // Initialiser la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Erreur lors de l'initialisation de la SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Creer la fen�tre
    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        fprintf(stderr, "Erreur lors de la creation de la fen�tre : %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // Creer le renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "Erreur lors de la creation du renderer : %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_Surface* backgroundSurface = SDL_LoadBMP("Data/background_Menu.bmp");
    if (backgroundSurface == NULL)
    {
        fprintf(stderr, "Erreur lors du chargement de l'image de fond : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    if (backgroundTexture == NULL)
    {
        fprintf(stderr, "Erreur lors de la creation de la texture de fond : %s\n", SDL_GetError());
        SDL_FreeSurface(backgroundSurface);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    // Dessiner les boutons du menu

    /* SDL RECT DATA :
    int x the x location of the rectangle's upper left corner
    int y the y location of the rectangle's upper left corner
    int w the width of the rectangle
    int h the height of the rectangle
    */

    SDL_Rect ButtonRectIAPlayerX = {360, 240, 40, 40};
    SDL_RenderFillRect(renderer, &ButtonRectIAPlayerX);

    SDL_Rect ButtonRectHumainPlayerX = {450, 240, 65, 40};
    SDL_RenderFillRect(renderer, &ButtonRectHumainPlayerX);

    SDL_Rect ButtonRectIAPlayerO = {360, 330, 40, 40};
    SDL_RenderFillRect(renderer, &ButtonRectIAPlayerX);

    SDL_Rect ButtonRectHumainPlayerO = {450, 330, 65, 40};
    SDL_RenderFillRect(renderer, &ButtonRectHumainPlayerX);

    SDL_Rect ButtonRectFackPlay = {235, 416, 87, 34};
    SDL_RenderFillRect(renderer, &ButtonRectHumainPlayerX);

    SDL_Rect destRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &destRect);

    //MAJ De la fenetre
    SDL_RenderPresent(renderer);

    // Boucle d'evenements
    SDL_Event event;
    bool gameRunning = true;
    while (gameRunning)
    {
        // Attendre un evenements
        SDL_WaitEvent(&event);
        // Traiter l'evenement
        switch (event.type)
        {
            case SDL_QUIT:
                gameRunning = false;
                break;
            case SDL_MOUSEBUTTONUP:
            {
                // Recuperer la position de la souris
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Verifier si l'utilisateur a clique sur un bouton
                if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &ButtonRectIAPlayerX))
                {
                    messageSDL("Choix Joueur avec des Croix",">> Le joueur avec des croix est de type IA");
                    initplayerX(playerX,1);
                }
                else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &ButtonRectHumainPlayerX))
                {
                    messageSDL("Choix Joueur avec des Croix",">> Le joueur avec des croix est de type Humain");
                    initplayerX(playerX,0);
                }
                else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &ButtonRectIAPlayerO))
                {
                    messageSDL("Choix Joueur avec des Ronds",">> Le joueur avec des ronds est de type IA");
                    initplayerO(playerO,1);
                }
                else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &ButtonRectHumainPlayerO))
                {
                    messageSDL("Choix Joueur avec des Ronds",">> Le joueur avec des ronds est de type Humain");
                    initplayerO(playerO,0);
                }
                else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &ButtonRectFackPlay))
                {
                    gameRunning = false;
                }
                break;
            }
        }
    }

    // Nettoyer la memoire avant de quitter
    SDL_FreeSurface(backgroundSurface);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

