#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Affichage.h"
#include <SDL.h>
//===============================================================================//
//=================================== Print =====================================//
//===============================================================================//




void MySDLMenu(TPlayer *playerX,TPlayer *playerO)
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

    // Créer la fenêtre
    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        fprintf(stderr, "Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // Créer le renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_Surface* backgroundSurface = SDL_LoadBMP("Data/Menu/background_Menu.bmp");
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
        fprintf(stderr, "Erreur lors de la création de la texture de fond : %s\n", SDL_GetError());
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

    SDL_Rect destRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &destRect);


    SDL_RenderPresent(renderer);

    // Boucle d'événements
    SDL_Event event;
    bool gameRunning = true;
    while (gameRunning)
    {
        // Attendre un événement
        SDL_WaitEvent(&event);
        // Traiter l'événement
        switch (event.type)
        {
            case SDL_QUIT:
                gameRunning = false;
                break;
            case SDL_MOUSEMOTION:
                   printf("%d / %d \n",event.motion.x,event.motion.y);
                   break;
            case SDL_MOUSEBUTTONUP:
            {
                // Récupérer la position de la souris
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Vérifier si l'utilisateur a cliqué sur un bouton
                if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &ButtonRectIAPlayerX))
                {
                    // Lancer le jeu de Morpion
                    printf("Je suis sur le PLayer X le button IA\n");
                    playerX->typejoueur = IA;
                }
                else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &ButtonRectHumainPlayerX))
                {
                    // Lancer le jeu de Morpion
                    printf("Je suis sur le PLayer X le button Humain\n");
                     playerX->typejoueur = Humain;
                }
                 if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &ButtonRectIAPlayerO))
                {
                    // Lancer le jeu de Morpion
                    printf("Je suis sur le PLayer O le button IA\n");
                       playerO->typejoueur = IA;
                }
                else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &ButtonRectHumainPlayerO))
                {
                    // Lancer le jeu de Morpion
                    printf("Je suis sur le PLayer O le button Humain\n");
                    playerO->typejoueur = Humain;
                }
                else
                {
                    gameRunning = false;
                }
                break;
            }
        }
    }

    // Nettoyer la mémoire avant de quitter
    SDL_FreeSurface(backgroundSurface);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}



// Affiche le menu.
void printMenu()
{
    system("color F"); // Couleur Windows
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
        printf("\t\t\t\t\t <> Dernier coup jouer par le joueur '%s' :\n", InitialeTypeSymbole[joueur]);
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
           printf("\t\t\t\t\t >> Le joueur avec les croix ( X ) est : ");
        }
        else
        {
            printf("\t\t\t\t\t >> Le joueur avec les ronds ( O ) est : ");
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
        printf("\t\t\t\t\t -->  Entrez le numero de la colonne(x) : ");
        scanf("%d", X);
        printf("\t\t\t\t\t -->  Entrez le numero de la ligne(y) : ");
        scanf("%d", Y);

        if(isEmptyCase(jeu, *X, *Y) && *X < TAILLEJEU && *Y < TAILLEJEU && *X >= 0 && *Y >= 0)
        {
            foundCase = true;
        }
        else
        {
            printPlateauDeJeu(jeu);
            printLastPlay(p, *X, *Y, false);

            printf("\n\t\t\t\t   --> Mauvaise coordonnees ! Veuillez reessayer.");
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
        printf("\n\n\t\t >> Entrez une commande (continuer: 'n', sauvegarde: 's', chargement: 'l' et quitter: 'q') : ");
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
