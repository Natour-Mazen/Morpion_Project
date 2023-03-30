#ifndef AFFICHAGE_H
#define AFFICHAGE_H
#include <stdbool.h>
#include <SDL.h> // Pour windows
//#include <SDL2/SDL.h> // Pour Linux
#include "AffichageConsole.h"
#include "Types.h"
#include "Morpion.h"

//======================= Print =========================//
void printMenu();
void printWinner(int joueur);
void printPlateauDeJeu(Symboles jeu[TAILLEJEU][TAILLEJEU]);
void printLastPlay(TPlayer p, int X, int Y, bool change);
//======================= Read ==========================//
Position readPositionToPlay(TPlayer p, int* X, int* Y, Position* TabPosition, Symboles jeu[TAILLEJEU][TAILLEJEU],SDL_Renderer* renderer,bool *stopGame);

//======================= SDL ==========================//
void messageSDL(const char *myTitle,const char *myMessage, const int Flag);
void MySDL_Menu(TPlayer *playerX, TPlayer *playerO,bool *continuJeu);
void dessiner_grille_morpion(SDL_Renderer* renderer);
void dessiner_croix_bleue(SDL_Renderer* renderer, int x, int y);
void dessiner_rond_rouge(SDL_Renderer* renderer, int x, int y);
void print_Winner_SDL(int joueur);
void Display_Info();
void WhoStart(int rand_num);


#endif
