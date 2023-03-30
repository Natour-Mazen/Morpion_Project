#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Affichage.h"


#define TAILLECASE TAILLEECRANJEU/TAILLEJEU

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
   // system("clear"); // Pour Linux
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
Position readPositionToPlay(TPlayer p, int* X, int* Y, Position* TabPosition, Symboles jeu[TAILLEJEU][TAILLEJEU],SDL_Renderer* renderer, bool *stopGame)
{
    bool foundCase = false;
    do{
        SDL_Event event;
        while (true) {
            if (SDL_WaitEvent(&event) == 0)
            {
                break;
            }
            if (event.type == SDL_QUIT)
            {
                *stopGame = true;
                break;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                *X = event.button.x / TAILLECASE;
                *Y = event.button.y / TAILLECASE;
                //  printf("X = %d, Y = %d",*X, *Y);
                if(isEmptyCase(jeu, *X, *Y) && *X < TAILLEJEU && *Y < TAILLEJEU && *X >= 0 && *Y >= 0)
                {
                    if(p.typeSymbole == croix){
                        dessiner_croix_bleue(renderer,*X,*Y);
                    }
                    else{
                        dessiner_rond_rouge(renderer,*X,*Y);
                    }
                    // Afficher le rendu a l'ecran
                    SDL_RenderPresent(renderer);
                    foundCase = true;
                }
                else
                {
                    messageSDL("Case non vide",">> Cette case n'est pas vide vous pouvez pas jouer ici !",SDL_MESSAGEBOX_WARNING);
                    break;
                }
            }
            break;
        }
    }while(foundCase == false);
    return &TabPosition[*X][*Y];
}

//===============================================================================//
//=================================== SDL =====================================//
//===============================================================================//
//Envoyer un msg à l'ecran
//Flag est soit
//- SDL_MESSAGEBOX_INFORMATION --> pour un pop up info
//- SDL_MESSAGEBOX_WARNING --> pour un pop up warning
void messageSDL(const char *myTitle,const char *myMessage, const int Flag)
{
        const SDL_MessageBoxButtonData buttons[] = {
        { /* .flags, .buttonid, .text */        0, 0, "ok" },
 //       { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
 //       { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,  255, 255 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            {   0, 0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            { 255,  255, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 0 }
        }
    };
    const SDL_MessageBoxData messageboxdata = {
        Flag, /* .flags */
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
void MySDL_Menu(TPlayer *playerX, TPlayer *playerO, bool *continuJeu)
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

    // Creer la fenetre
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

    //Charger la texture du menu
    SDL_Surface* backgroundSurface = SDL_LoadBMP("Data/background_Menu.bmp");
    if (backgroundSurface == NULL)
    {
        fprintf(stderr, "Erreur lors du chargement de l'image de fond : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    //Creer la texture du menu sur le renderer
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

    //On met la texture qu'on a creer sur le renderer
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
            case SDL_QUIT:{
                *continuJeu = false;
                gameRunning = false;
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                // Recuperer la position de la souris
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Verifier si l'utilisateur a clique sur un bouton
                if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &ButtonRectIAPlayerX))
                {
                    messageSDL("Choix Joueur avec des Croix",">> Le joueur avec des croix est de type IA",SDL_MESSAGEBOX_INFORMATION);
                    initplayerX(playerX,1);
                }
                else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &ButtonRectHumainPlayerX))
                {
                    messageSDL("Choix Joueur avec des Croix",">> Le joueur avec des croix est de type Humain",SDL_MESSAGEBOX_INFORMATION);
                    initplayerX(playerX,0);
                }
                else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &ButtonRectIAPlayerO))
                {
                    messageSDL("Choix Joueur avec des Ronds",">> Le joueur avec des ronds est de type IA",SDL_MESSAGEBOX_INFORMATION);
                    initplayerO(playerO,1);
                }
                else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &ButtonRectHumainPlayerO))
                {
                    messageSDL("Choix Joueur avec des Ronds",">> Le joueur avec des ronds est de type Humain",SDL_MESSAGEBOX_INFORMATION);
                    initplayerO(playerO,0);
                }
                else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &ButtonRectFackPlay))
                {
                    Display_Info();
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

//Dessiner la grille
void dessiner_grille_morpion(SDL_Renderer* renderer)
{
  //  la taille et la couleur des lignes de la grille
  SDL_SetRenderDrawColor(renderer, 128,128, 128, SDL_ALPHA_OPAQUE);

  // on dessine les lignes horizontales de la grille
  for (int i = 0; i <= TAILLEJEU; i++) {
    SDL_RenderDrawLine(renderer, 0, i * TAILLECASE, TAILLECASE * TAILLECASE, i * TAILLECASE);
  }

  // on dessine les lignes verticales de la grille
  for (int i = 0; i <= TAILLEJEU; i++) {
    SDL_RenderDrawLine(renderer, i * TAILLECASE, 0, i * TAILLECASE, TAILLECASE * TAILLECASE);
  }
}

//Dessiner les croix
void dessiner_croix_bleue(SDL_Renderer* renderer, int x, int y)
{
  // la couleur de la croix bleue
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);

  // le centre de la croix
  int centre_x = x * TAILLECASE + TAILLECASE/2;
  int centre_y = y * TAILLECASE + TAILLECASE/2;

    int longeur = 0;
    if(TAILLEJEU >= 20){
        longeur = 15;
    }
    else{
        longeur = 20;
    }

  // les deux lignes de la croix
  SDL_RenderDrawLine(renderer, centre_x - longeur, centre_y - longeur, centre_x + longeur, centre_y + longeur);
  SDL_RenderDrawLine(renderer, centre_x - longeur, centre_y + longeur, centre_x + longeur, centre_y - longeur);
}

//Dessiner les ronds
void dessiner_rond_rouge(SDL_Renderer* renderer, int x, int y)
{
  // couleur du rond rouge
  SDL_SetRenderDrawColor(renderer, 255, 0,0, SDL_ALPHA_OPAQUE);

 // le rayon du rond et le centre du rond
  int rayon = 0;
  if(TAILLEJEU >= 20){
    rayon = 15;
  }
  else{
    rayon = 20;
  }
  int centre_x = x * TAILLECASE + TAILLECASE/2;
  int centre_y = y * TAILLECASE + TAILLECASE/2;

  // on dessine un cercle en utilisant l'algorithme de Bresenham (Cf.youtube)
  int f = 1 - rayon;
  int ddF_x = 0;
  int ddF_y = -2 * rayon;
  int x1 = 0;
  int y1 = rayon;


  // les 4 points cardinaux du cercle
  SDL_RenderDrawPoint(renderer, centre_x, centre_y + rayon);
  SDL_RenderDrawPoint(renderer, centre_x, centre_y - rayon);
  SDL_RenderDrawPoint(renderer, centre_x + rayon, centre_y);
  SDL_RenderDrawPoint(renderer, centre_x - rayon, centre_y);
   SDL_RenderPresent(renderer);

  while (x1 < y1)
    {
        if (f >= 0) {
          y1--;
          ddF_y += 2;
          f += ddF_y;
        }
        x1++;
        ddF_x += 2;
        f += ddF_x + 1;
       SDL_RenderDrawPoint(renderer, centre_x + x1, centre_y + y1); // moitie du bas droite
        SDL_RenderDrawPoint(renderer, centre_x - x1, centre_y + y1); // moitie du bas gauche
        SDL_RenderDrawPoint(renderer, centre_x + x1, centre_y - y1); // moitie du haut droite
        SDL_RenderDrawPoint(renderer, centre_x - x1, centre_y - y1); // moitie du haut gauche
        SDL_RenderDrawPoint(renderer, centre_x + y1, centre_y + x1); // le rest moitie du bas droite
        SDL_RenderDrawPoint(renderer, centre_x - y1, centre_y + x1); // le rest moitie du bas gauche
        SDL_RenderDrawPoint(renderer, centre_x + y1, centre_y - x1); // le rest moitie du haut droite
        SDL_RenderDrawPoint(renderer, centre_x - y1, centre_y - x1); // le rest moitie du haut droite
    }
}

//Afficher le gagnant
void print_Winner_SDL(int joueur)
{
    if(joueur == 1){ // le joueur avec des croix
        messageSDL("Un gagnant",">> Le gagnant est le joueur avec des croix, bravo à lui !",SDL_MESSAGEBOX_INFORMATION);
    }
    else if (joueur == 2){ // le joueur avec des ronds
        messageSDL("Un gagnant",">> Le gagnant est le joueur avec des ronds, bravo à lui !",SDL_MESSAGEBOX_INFORMATION);
    }
    else{
         messageSDL("Egalite",">> Il n'y a pas de gagnant dans cette partie !",SDL_MESSAGEBOX_INFORMATION);
    }
}

//Affiche les infos sur les touches du jeu
void Display_Info()
{
    messageSDL("Infos sur le Jeu","\n >> Vous pouvez rafficher ses infos en appuyant sur la touche I."
                                  "\n >> Vous pouvez quitter la partie en appuyant sur la touche ECHAP.\n"
                                  "\n  \t\t [ Amusez-Vous Bien ] ",SDL_MESSAGEBOX_INFORMATION);
}

//Fonction permettant de savoir qui commence à jouer apres le tirage aléatoire en debut de partie
void WhoStart(int rand_num)
{
    if(rand_num == 1){
        messageSDL("Qui commence ? ","\n >> C'est au joueur avec des croix de commencer.",SDL_MESSAGEBOX_INFORMATION);
    }
    else if (rand_num == 0){
        messageSDL("Qui commence ? ","\n >> C'est au joueur avec des ronds de commencer.",SDL_MESSAGEBOX_INFORMATION);
    }
}



