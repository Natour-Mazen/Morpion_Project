#ifndef JEUMORPION
#define JEUMORPION
#include <stdbool.h>


#include "Types.h"
#include "Quintuplet.h"


/// INITALISATION & AFFICHAGE PLATEAU DE JEU ///
// Initialise le plateau avec que des 0 .
void initPlateau(TabMorpion jeu);
// Affiche le plateau dans la console.
void printJeu(TabMorpion jeu);

///  AFFICHAGE GENERALE ///
void menuaffiche();



/// FONCTIONS D AJOUT SUR LE PLATEAU ///
//verifie si une case est vide
bool estvidecase(TabMorpion jeu,int posX , int posY);
void scancoordonnee(TPlayer p,int *X , int *Y);
void ajoutesymbole(TabMorpion jeu ,TPlayer p);




/// INITALISATION & AFFICHAGE JOUEURS ///
void ParamPlayer(TPlayer *p,int tjoueur);
TPlayer initplayerX();
TPlayer initplayerO();
void printplayer(TPlayer p);




listequintuplet makeMainList();

listequintuplet suppDoublons(listequintuplet mainList);

void afficheMainList(listequintuplet l);
#endif









/*
//tableau a deux dimensions de 10*10 cases.

//typedef Symboles** TabMorpion;

// Alloue un tableau de jeu.
//TabMorpion allouePlateau(int taille);
*/
