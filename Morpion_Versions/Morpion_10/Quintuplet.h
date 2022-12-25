#ifndef QUINTUPLET_H
#define QUINTUPLET_H

#include "Types.h"

//===== Création de Quintuplets =====//
Quintuplet* initQuintu();
Quintuplet createQuintu(int x_of_origin, int y_of_origin, int x_direction, int y_direction, Position* TabPosition, int id);

//======== Création de liste ========//
QList makeMainList(Position* TabPosition);

//============ Getteurs =============//
QList getAllQuints(Position pos, QList* l);
Quintuplet* getQuintWithId(int id, QList l);

//=========== Suppréssion ===========//
QList removeClosedQuints(QList l);

//===================================//
#endif

