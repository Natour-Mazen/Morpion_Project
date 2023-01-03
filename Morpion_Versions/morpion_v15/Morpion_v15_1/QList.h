#ifndef TYPES_H
	#include "Types.h"
#endif

#ifndef QLIST_H
#define QLIST_H

#define TYPE Quintuplet

typedef TYPE* Q;
typedef TYPE* const QConst;

// Liste de quintuplet.
typedef struct T_cell T_cell;
typedef T_cell* QList;
typedef const T_cell* QListConst;

//===== Opération de Création =====//
QList empty_QL();

//=== Opération de Vérification ===//
bool isEmpty_QL(QListConst l);
bool isNextEmpty_QL(QListConst l);
bool isPrevEmpty_QL(QListConst l);

//====== Opération de Getteur =====//
Q getQ_QL(QListConst l);
QList getNext_QL(QListConst l);
QList getPrev_QL(QListConst l);
QList getFst_QL(QList l);
QList getLst_QL(QList l);
int getLen_QL(QList l);

//======= Opération d'ajout =======//
QList addNext_QL(QList l, QConst q);
QList addPrev_QL(QList l, QConst q);
QList addFst_QL(QList l, QConst q);
QList addLst_QL(QList l, QConst q);

//==== Opération de Suppression ===//
QList rem_QL(QList l);
QList remNext_QL(QList l);
QList remPrev_QL(QList l);
QList remFst_QL(QList l);
QList remLst_QL(QList l);
QList remAll_QL(QList l);
QList remAllPlusElement_QL(QList l);

//======= Autres Opération ========//
QList concat_QL(QList debut, QList* fin);
QList duplicate_QL(QList l);

#endif //QLIST_H