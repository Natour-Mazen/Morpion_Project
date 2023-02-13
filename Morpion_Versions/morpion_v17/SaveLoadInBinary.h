#ifndef SAVELOADINBINARY_H
#define SAVELOADINBINARY_H
#include <stdbool.h>

#include "Types.h"


//====================== Game Save ======================//

void b_writeSymbolesTab(FILE* fd, Symboles jeu[TAILLEJEU][TAILLEJEU]);
void b_writePosition(FILE* fd, Position pos);
void b_writeLitePosition(FILE* fd, Position pos);
void b_writeTabPosition(FILE* fd, Position* tabPosition);
void b_writeQunituplet(FILE* fd, Quintuplet* q);
void b_writeLiteQunituplet(FILE* fd, Quintuplet* q);
void b_writeListQuintuplets(FILE* fd, QList l);
void b_writeLiteListQuintuplets(FILE* fd, QList l);
void b_writeTPlayer(FILE* fd, TPlayer player);

//====================== Game Load ======================//

void b_readSymbolesTab(FILE* fd, Symboles jeu[TAILLEJEU][TAILLEJEU]);
struct t_position b_readPosition(FILE* fd);
Position b_readLitePosition(FILE* fd, Position* tabPosition);
void b_readTabPosition(FILE* fd, Position** tabPosition);
Quintuplet* b_readQunituplet(FILE* fd, Position* tabPosition);
Quintuplet* b_readLiteQunituplet(FILE* fd, QList l);
QList b_readListQuintuplets(FILE* fd, Position* tabPosition);
QList b_readLiteListQuintuplets(FILE* fd, QList allQuints);
TPlayer b_readTPlayer(FILE* fd, QList allQuints);

//=======================================================//
#endif
