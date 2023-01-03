#ifndef SAVELOADINTEXT_H
#define SAVELOADINTEXT_H
#include <stdbool.h>

#include "Types.h"

//======================= Fichier =======================//
FILE* getFileInWrite();
FILE* getFileInRead();
void closeFile(FILE* f);

//====================== Game Save ======================//

void writeSymbolesTab(FILE* fd, Symboles jeu[TAILLEJEU][TAILLEJEU]);
void writePosition(FILE* fd, Position pos);
void writeLitePosition(FILE* fd, Position pos);
void writeTabPosition(FILE* fd, Position* tabPosition);
void writeQunituplet(FILE* fd, Quintuplet* q);
void writeLiteQunituplet(FILE* fd, Quintuplet* q);
void writeListQuintuplets(FILE* fd, QList l);
void writeLiteListQuintuplets(FILE* fd, QList l);
void writeTPlayer(FILE* fd, TPlayer player);

//====================== Game Load ======================//

void readSymbolesTab(FILE* fd, Symboles jeu[TAILLEJEU][TAILLEJEU]);
struct t_position readPosition(FILE* fd);
Position readLitePosition(FILE* fd, Position* tabPosition);
void readTabPosition(FILE* fd, Position** tabPosition);
Quintuplet* readQunituplet(FILE* fd, Position* tabPosition);
Quintuplet* readLiteQunituplet(FILE* fd, QList l);
QList readListQuintuplets(FILE* fd, Position* tabPosition);
QList readLiteListQuintuplets(FILE* fd, QList allQuints);
TPlayer readTPlayer(FILE* fd, QList allQuints);

//=======================================================//
#endif