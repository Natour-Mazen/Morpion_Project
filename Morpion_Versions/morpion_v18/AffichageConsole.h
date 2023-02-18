#ifndef AFFICHAGECONSOLE_H
#define AFFICHAGECONSOLE_H
#include <stdbool.h>

// Color ref : https://askubuntu.com/questions/558280/changing-colour-of-text-and-background-of-terminal

#define BASIC_TEXT "\033[0m"
#define RED_TEXT "\033[0;31m"
#define WHITE_BACKGROUND "\033[0;47m"
#define RED_TEXT_AND_WHITE_BACKGROUND "\033[0;31;47m"
#define BLACK_TEXT_AND_WHITE_BACKGROUND "\033[0;30;47m"

//======== Affichage console ========//
void printCarWithColor(int n, char* color);
void printWhiteLigne();
void printWhiteBorder();
void clearALigne();
void viderBuffer();

//===================================//
#endif