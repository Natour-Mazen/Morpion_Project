#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SaveLoadInText.h"
#include "Position.h"
#include "Quintuplet.h"

//===============================================================================//
//================================== Fichier ====================================//
//===============================================================================//

// Ouvre le fichier "MorpionSave.txt" en écriture.
FILE* getFileInWrite()
{
	char* file = "Sauvegarde/MorpionSave.txt";

    FILE* fd = fopen(file, "w");
    if(fd == NULL)
    {
        printf("Error getFileInWrite : on ne peut pas ouvrir le fichier \"%s\"\n", file);
        exit(EXIT_FAILURE);
    }
    return fd;
}

// Ouvre le fichier "MorpionSave.txt" en lecture.
FILE* getFileInRead()
{
	char* file = "Sauvegarde/MorpionSave.txt";

    FILE* fd = fopen(file, "r");
    if(fd == NULL)
    {
        printf("Error getFileInRead : on ne peut pas ouvrir le fichier \"%s\"\n", file);
        exit(EXIT_FAILURE);
    }
    return fd;
}

// Ferme le fichier f.
void closeFile(FILE* f)
{
	fclose(f);
}

//===============================================================================//
//================================= Game Save ===================================//
//===============================================================================//

// Ecrit un tableau de Symboles dans un fichier.
void writeSymbolesTab(FILE* fd, Symboles jeu[TAILLEJEU][TAILLEJEU])
{
    fprintf(fd, "SymbolesTab %d\n", TAILLEJEU);
    for(int j = 0; j < TAILLEJEU; j++)
    {
        for(int i = 0; i < TAILLEJEU; i++)
        {
            fprintf(fd, "%d ", jeu[i][j]);
        }
        fprintf(fd, "\n");
    }
}

// Ecrit une Position dans un fichier.
void writePosition(FILE* fd, Position pos)
{
    fprintf(fd, "Pos %d %d %d %d %d %d\n", pos->X, pos->Y, pos->valeur, pos->valX, pos->valO, pos->Sy);
}

// Ecrit les coordonnées d'une Position dans un fichier.
void writeLitePosition(FILE* fd, Position pos)
{
    fprintf(fd, "P %d %d\n", pos->X, pos->Y);
}

//Ecrit un tableau de position dans un fichier.
void writeTabPosition(FILE* fd, Position* tabPosition)
{
    fprintf(fd, "TabPos %d\n", TAILLEJEU);
    for(int i = 0; i < TAILLEJEU; i++)
    {
        for(int j = 0; j < TAILLEJEU; j++)
        {
            writePosition(fd, &(tabPosition[i][j]));
        }
    }
}

// Ecrit un Quintuplet dans un fichier.
void writeQunituplet(FILE* fd, Quintuplet* q)
{
    fprintf(fd, "Quint %d %d %d\n", NTUPLET, q->valquintuplet, q->idQuintuplet);
    for(int i = 0; i < NTUPLET; i++)
    {
        writeLitePosition(fd, q->pos[i]);
    }
}

// Ecrit l'id d'un quintuplet.
void writeLiteQunituplet(FILE* fd, Quintuplet* q)
{
    fprintf(fd, "QuintLite %d\n", q->idQuintuplet);
}

// Ecrit une liste de Quintuplets dans un fichier.
void writeListQuintuplets(FILE* fd, QList l)
{
    int lenList = getLen_QL(l);
    QList liste = l;
    fprintf(fd, "ListQuint %d\n", lenList);
    for(int i = 0; i < lenList; i++)
    {
        writeQunituplet(fd, getQ_QL(liste));
        liste = getNext_QL(liste);
    }
}

// Ecrit une liste de Quintuplet Lite(juste l'id).
void writeLiteListQuintuplets(FILE* fd, QList l)
{
    int lenList = getLen_QL(l);
    QList liste = l;
    fprintf(fd, "ListLiteQuint %d\n", lenList);
    for(int i = 0; i < lenList; i++)
    {
        writeLiteQunituplet(fd, getQ_QL(liste));
        liste = getNext_QL(liste);
    }
}

// Ecrit un joueur dans un fichier.
void writeTPlayer(FILE* fd, TPlayer player)
{
    fprintf(fd, "Player %d %d\n", player.typejoueur, player.typeSymbole);
    writeLiteListQuintuplets(fd, player.listeGagnant);
    writeLiteListQuintuplets(fd, player.listePerdante);
}

//===============================================================================//
//================================= Game Load ===================================//
//===============================================================================//

// Lit un tableau de symboles dans un fichier.
void readSymbolesTab(FILE* fd, Symboles jeu[TAILLEJEU][TAILLEJEU])
{
    int taille = 0;
    fscanf(fd, "SymbolesTab %d\n", &taille);
    for(int j = 0; j < taille; j++)
    {
        for(int i = 0; i < taille; i++)
        {
            int symbole = 0;
            fscanf(fd, "%d ", &symbole);
            jeu[i][j] = symbole;
        }
        fscanf(fd, "\n");
    }
}

// Lit une position dans un fichier.
struct t_position readPosition(FILE* fd)
{
    int X, Y, valeur, valX, valO, Sy;
    fscanf(fd, "Pos %d %d %d %d %d %d\n", &X, &Y, &valeur, &valX, &valO, &Sy);
    struct t_position pos = {X, Y, valeur, valX, valO, Sy};
    return pos;
}

// Lit une position simple dans un fichier.
Position readLitePosition(FILE* fd, Position* tabPosition)
{
    int X, Y;
    fscanf(fd, "P %d %d\n", &X, &Y);
    return &(tabPosition[X][Y]);
}

// Lit un tableau de position dans un fichier.
void readTabPosition(FILE* fd, Position** tabPosition)
{
    int taille = 0;
    fscanf(fd, "TabPos %d\n", &taille);
    Position* newTabPosition = (Position*) malloc(sizeof(Position) * taille);

    for(int i = 0; i < taille; i++)
    {
        newTabPosition[i] = (Position) malloc(sizeof(struct t_position) * taille);
        for(int j = 0; j < taille; j++)
        {
            newTabPosition[i][j] = readPosition(fd);
        }
    }
    *tabPosition = newTabPosition;
}

// Lit un Quintuplet dans un fichier.
Quintuplet* readQunituplet(FILE* fd, Position* tabPosition)
{
    int nTuplet, val, id;
    fscanf(fd, "Quint %d %d %d\n", &nTuplet, &val, &id);
    Quintuplet* q = initQuintu();
    for(int i = 0; i < nTuplet; i++)
    {
        // ATTENTION: ici la taille du quintuplet et donc du nombre de position depend de la partie en cours.
        q->pos[i] = readLitePosition(fd, tabPosition);
    }
    q->valquintuplet = val;
    q->idQuintuplet = id;
    return q;
}

// Lit un Quintuplet lite.
Quintuplet* readLiteQunituplet(FILE* fd, QList l)
{
    int idQuintuplet;
    fscanf(fd, "QuintLite %d\n", &idQuintuplet);
    return getQuintWithId(idQuintuplet, l);
}

// Lit une liste de Quintuplet dans un fichier.
QList readListQuintuplets(FILE* fd, Position* tabPosition)
{
    int lenList;
    QList l = empty_QL();
    fscanf(fd, "ListQuint %d\n", &lenList);
    for(int i = 0; i < lenList; i++)
    {
        l = addLst_QL(l, readQunituplet(fd, tabPosition));
    }
    return getFst_QL(l);
}

// Lit une liste de Quintuplet Lite(juste l'id).
QList readLiteListQuintuplets(FILE* fd, QList allQuints)
{
    int lenList;
    QList l = empty_QL();
    fscanf(fd, "ListLiteQuint %d\n", &lenList);
    for(int i = 0; i < lenList; i++)
    {
        l = addLst_QL(l, readLiteQunituplet(fd, allQuints));
    }
    return getFst_QL(l);
}

// Lit un joueur dans un fichier.
TPlayer readTPlayer(FILE* fd, QList allQuints)
{
    int typejoueur, typeSymbole;
    fscanf(fd, "Player %d %d\n", &typejoueur, &typeSymbole);
    QList listeGagnant = readLiteListQuintuplets(fd, allQuints);
    QList listePerdante = readLiteListQuintuplets(fd, allQuints);
    TPlayer p;
    p.typejoueur = typejoueur;
    p.typeSymbole = typeSymbole;
    p.listeGagnant = listeGagnant;
    p.listePerdante = listePerdante;
    return p;
}

//===============================================================================//
