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
T_Postion *scancoordonnee(TPlayer p,int *X , int *Y);
T_Postion *ajouteSymboleHUMAN(TabMorpion jeu, TPlayer p);
void ajouteSymboleBOT(TabMorpion jeu, T_Postion *ChoosenPos, TPlayer p);




/// INITALISATION & AFFICHAGE JOUEURS ///
void ParamPlayer(TPlayer *p,int tjoueur);
TPlayer initplayerX();
TPlayer initplayerO();
void printplayer(TPlayer p);


/// FONCTIONS QUI GERENT LES LISTES ///

listequintuplet makeMainList();

listequintuplet concat(listequintuplet *list1 , listequintuplet *list2);

listequintuplet suppDoublons(listequintuplet mainList);

listequintuplet getAllQuints(T_Postion *pos, listequintuplet l);

listequintuplet removeSameQuints(listequintuplet *l1, listequintuplet l2);

void removeClosedQuints(listequintuplet *l);

void afficheQuintus(listequintuplet l);

/// FONCTIONS DE JEU ///

bool checkVictory(listequintuplet l);

int gameState(listequintuplet mainList, TPlayer p);

/// FONCTIONS LIEES AU BOT ///

T_Postion *bestPos(listequintuplet l);

void majValPosQuintuplet(listequintuplet list);

void FINTOUR();


#endif
