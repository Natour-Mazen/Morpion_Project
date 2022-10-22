#ifndef QUINTUPLET_H
#define QUINTUPLET_H

#include "Types.h"

Quintuplet *initQuintu ();

bool existeQuintu (int x_of_origin, int y_of_origin, int x_direction, int y_direction);

Quintuplet createQuintu(int x_of_origin, int y_of_origin, int x_direction, int y_direction);

Symboles getSymbolePlayer(listequintuplet l);

void majValPosQuintuplet(listequintuplet list);

void finDeTour();
#endif

