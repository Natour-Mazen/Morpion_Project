#ifndef AFFICHAGECONSOLE_H
#define AFFICHAGECONSOLE_H
#include <stdbool.h>

#define BASIC_TEXT "\033[0m"
#define RED_TEXT "\033[0;31m"
#define WHITE_BACKGROUND "\033[0;47m"

//======== Affichage console ========//
void printCarWithColor(int n, char* color);
void printWhiteLigne();
void printWhiteBorder();
void clearALigne();
void viderBuffer();

//===================================//
#endif