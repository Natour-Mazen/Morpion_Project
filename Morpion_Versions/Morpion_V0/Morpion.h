#ifndef JEUMORPION
#define JEUMORPION
#include <stdbool.h>


#include "Types.h"

//tableau a deux dimensions de 10*10 cases.

//typedef Symboles** TabMorpion;

// Alloue un tableau de jeu.
//TabMorpion allouePlateau(int taille);

// Initialise le plateau avec que des 0 .
void initPlateau(TabMorpion jeu, int taille);

// Affiche le plateau dans la console.
void printJeu(TabMorpion jeu, int taille);

//verifie si une case est vide
bool estvidecase(TabMorpion jeu,int posX , int posY);

// ajoute un symbole dans la case demander si cette case est vide
void ajoutesymbole(TabMorpion jeu ,Symboles symb , int posX , int posY);

//
//void scan



#endif
