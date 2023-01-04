#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SaveLoadInBinary.h"
#include "Types.h"
#include "Position.h"
#include "Quintuplet.h"

//===============================================================================//
//================================= Game Save ===================================//
//===============================================================================//

// Ecrit un tableau de Symboles dans un fichier.
void b_writeSymbolesTab(FILE* fd, Symboles jeu[TAILLEJEU][TAILLEJEU])
{
    int taille = TAILLEJEU;
    fwrite(&taille, sizeof(int), 1, fd);
    for(int j = 0; j < TAILLEJEU; j++)
    {
        for(int i = 0; i < TAILLEJEU; i++)
        {
            fwrite(&(jeu[i][j]), sizeof(int), 1, fd);
        }
    }
}

// Ecrit une Position dans un fichier.
void b_writePosition(FILE* fd, Position pos)
{
    fwrite(pos, sizeof(struct t_position), 1, fd);
}

// Ecrit les coordonnées d'une Position dans un fichier.
void b_writeLitePosition(FILE* fd, Position pos)
{
    fwrite(&(pos->X), sizeof(int), 1, fd);
    fwrite(&(pos->Y), sizeof(int), 1, fd);
}

//Ecrit un tableau de position dans un fichier.
void b_writeTabPosition(FILE* fd, Position* tabPosition)
{
    int taille = TAILLEJEU;
    fwrite(&taille, sizeof(int), 1, fd);
    for(int i = 0; i < TAILLEJEU; i++)
    {
        for(int j = 0; j < TAILLEJEU; j++)
        {
            b_writePosition(fd, &(tabPosition[i][j]));
        }
    }
}

// Ecrit un Quintuplet dans un fichier.
void b_writeQunituplet(FILE* fd, Quintuplet* q)
{
    int ntuplet = NTUPLET;
    fwrite(&ntuplet, sizeof(int), 1, fd);
    fwrite(&(q->valquintuplet), sizeof(int), 1, fd);
    fwrite(&(q->idQuintuplet), sizeof(int), 1, fd);
    for(int i = 0; i < NTUPLET; i++)
    {
        b_writeLitePosition(fd, q->pos[i]);
    }
}

// Ecrit l'id d'un quintuplet.
void b_writeLiteQunituplet(FILE* fd, Quintuplet* q)
{
    fwrite(&(q->idQuintuplet), sizeof(int), 1, fd);
}

// Ecrit une liste de Quintuplets dans un fichier.
void b_writeListQuintuplets(FILE* fd, QList l)
{
    int lenList = getLen_QL(l);
    QList liste = l;
    fwrite(&lenList, sizeof(int), 1, fd);
    for(int i = 0; i < lenList; i++)
    {
        b_writeQunituplet(fd, getQ_QL(liste));
        liste = getNext_QL(liste);
    }
}

// Ecrit une liste de Quintuplet Lite(juste l'id).
void b_writeLiteListQuintuplets(FILE* fd, QList l)
{
    int lenList = getLen_QL(l);
    QList liste = l;
    fwrite(&lenList, sizeof(int), 1, fd);
    for(int i = 0; i < lenList; i++)
    {
        b_writeLiteQunituplet(fd, getQ_QL(liste));
        liste = getNext_QL(liste);
    }
}

// Ecrit un joueur dans un fichier.
void b_writeTPlayer(FILE* fd, TPlayer player)
{
    fwrite(&(player.typejoueur), sizeof(int), 1, fd);
    fwrite(&(player.typeSymbole), sizeof(int), 1, fd);
    b_writeLiteListQuintuplets(fd, player.listeGagnant);
    b_writeLiteListQuintuplets(fd, player.listePerdante);
}

//===============================================================================//
//================================= Game Load ===================================//
//===============================================================================//

// Lit un tableau de symboles dans un fichier.
void b_readSymbolesTab(FILE* fd, Symboles jeu[TAILLEJEU][TAILLEJEU])
{
    int taille = 0;
    fread(&taille, sizeof(int), 1, fd);
    for(int j = 0; j < taille; j++)
    {
        for(int i = 0; i < taille; i++)
        {
            int symbole = 0;
            fread(&symbole, sizeof(int), 1, fd);
            jeu[i][j] = symbole;
        }
    }
}

// Lit une position dans un fichier.
struct t_position b_readPosition(FILE* fd)
{
    struct t_position pos;
    fread(&pos, sizeof(struct t_position), 1, fd);
    return pos;
}

// Lit une position simple dans un fichier.
Position b_readLitePosition(FILE* fd, Position* tabPosition)
{
    int X, Y;
    fread(&X, sizeof(int), 1, fd);
    fread(&Y, sizeof(int), 1, fd);
    return &(tabPosition[X][Y]);
}

// Lit un tableau de position dans un fichier.
void b_readTabPosition(FILE* fd, Position** tabPosition)
{
    int taille = 0;
    fread(&taille, sizeof(int), 1, fd);
    Position* newTabPosition = (Position*) malloc(sizeof(Position) * taille);

    for(int i = 0; i < taille; i++)
    {
        newTabPosition[i] = (Position) malloc(sizeof(struct t_position) * taille);
        for(int j = 0; j < taille; j++)
        {
            newTabPosition[i][j] = b_readPosition(fd);
        }
    }
    *tabPosition = newTabPosition;
}

// Lit un Quintuplet dans un fichier.
Quintuplet* b_readQunituplet(FILE* fd, Position* tabPosition)
{
    int nTuplet, val, id;
    fread(&nTuplet, sizeof(int), 1, fd);
    fread(&val, sizeof(int), 1, fd);
    fread(&id, sizeof(int), 1, fd);
    Quintuplet* q = initQuintu();
    for(int i = 0; i < nTuplet; i++)
    {
        // ATTENTION: ici la taille du quintuplet et donc du nombre de position depend de la partie en cours.
        q->pos[i] = b_readLitePosition(fd, tabPosition);
    }
    q->valquintuplet = val;
    q->idQuintuplet = id;
    return q;
}

// Lit un Quintuplet lite.
Quintuplet* b_readLiteQunituplet(FILE* fd, QList l)
{
    int idQuintuplet;
    fread(&idQuintuplet, sizeof(int), 1, fd);
    return getQuintWithId(idQuintuplet, l);
}

// Lit une liste de Quintuplet dans un fichier.
QList b_readListQuintuplets(FILE* fd, Position* tabPosition)
{
    int lenList;
    QList l = empty_QL();
    fread(&lenList, sizeof(int), 1, fd);
    for(int i = 0; i < lenList; i++)
    {
        l = addLst_QL(l, b_readQunituplet(fd, tabPosition));
    }
    return getFst_QL(l);
}

// Lit une liste de Quintuplet Lite(juste l'id).
QList b_readLiteListQuintuplets(FILE* fd, QList allQuints)
{
    int lenList;
    QList l = empty_QL();
    fread(&lenList, sizeof(int), 1, fd);
    for(int i = 0; i < lenList; i++)
    {
        l = addLst_QL(l, b_readLiteQunituplet(fd, allQuints));
    }
    return getFst_QL(l);
}

// Lit un joueur dans un fichier.
TPlayer b_readTPlayer(FILE* fd, QList allQuints)
{
    int typejoueur, typeSymbole;
    fread(&typejoueur, sizeof(int), 1, fd);
    fread(&typeSymbole, sizeof(int), 1, fd);
    QList listeGagnant = b_readLiteListQuintuplets(fd, allQuints);
    QList listePerdante = b_readLiteListQuintuplets(fd, allQuints);
    TPlayer p;
    p.typejoueur = typejoueur;
    p.typeSymbole = typeSymbole;
    p.listeGagnant = listeGagnant;
    p.listePerdante = listePerdante;
    return p;
}

//===============================================================================//
