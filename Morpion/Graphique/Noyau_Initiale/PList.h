#ifndef TYPES_H
	#include "Position.h"
#endif

#ifndef PLIST_H
#define PLIST_H

typedef struct cellule cellule;
typedef cellule* PList;

//=== Liste de Positions ===//
PList empty_PL();
PList add_PL(Position pos, PList l);
bool isInList_PL(Position pos, PList l);
PList remAll_PL(PList l);

//==========================//
#endif