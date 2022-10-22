#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Morpion.h"



/**************************************************************************/

            /// INITALISATION & AFFICHAGE PLATEAU DE JEU ///

/**************************************************************************/
void initPlateau(TabMorpion jeu, int taille)
{
    for (int i=0;i<taille;i++){
        for (int j=0;j<taille;j++){
            jeu[i][j] = vide;
        }
    }
}

void printJeu(TabMorpion jeu, int taille)
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("    \t  \t\t\t\t    ");
    for(int x = 0; x < taille; x++){
		printf("%3d ", x);
	}
    printf("\n");
    for (int j=0;j<taille;j++){
            printf("\t\t\t\t\t%3d ", j);
        for (int i=0;i<taille;i++){
                if(jeu[i][j] == vide)
                    printf("  . ");
                else if(jeu[i][j] == rond)
                    printf("  O ");
                else if(jeu[i][j] == croix)
                    printf("  X ");
        }
        printf("\n");
    }
}



/**************************************************************************/

                 /// FONCTIONS D AJOUT SUR LE PLATEAU ///

/**************************************************************************/
bool estvidecase(TabMorpion jeu,int posX , int posY)
{
    return (jeu[posX][posY] == vide);
}

void scancoordonnee(TPlayer p,int *X , int *Y)
{
    int deco = 175 , deco1 = 254;
    const char* InitialeTypeSymbole[3]={"VIDE", "X" , "O"};

    printf("\n\n\t\t\t\t\t      %c%c Joueur '%s'  : \n\n",deco1,deco1,InitialeTypeSymbole[p.typeSymbole]);
    printf("\t\t\t\t\t %c%c  Entrez le numero de la colonne(x) : ",deco,deco);
    scanf("%d",X);
    printf("\t\t\t\t\t %c%c  Entrez le numero de la ligne(y) : ",deco,deco);
    scanf("%d",Y);

}

void ajoutesymbole(TabMorpion jeu ,TPlayer p)
{
    int X,Y;
    bool temp = false;
    if (p.typejoueur == Humain)
    {
        do{
            scancoordonnee(p,&X,&Y);
            if(estvidecase(jeu,X,Y) && X < TAILLEJEU10x10 && Y < TAILLEJEU10x10)
                temp = true;
            else
            {
                printf("\n\n\t\t\t\t   %c                                                      %c",201,187);
                printf("\n\t\t\t\t   %c C EST PAS POSSIBLE A CES COORDONNEES ! REESSAYEZ SVP %c",186,186);
                printf("\n\t\t\t\t   %c                                                      %c",200,188);
            }
        }while(temp == false);
        jeu[X][Y] = p.typeSymbole;
    }
    else if (p.typejoueur == IA);
        // fct pour faire fonction le robot

    printJeu(jeu,TAILLEJEU10x10);
}



/**************************************************************************/

                /// INITALISATION & AFFICHAGE JOUEURS ///

/**************************************************************************/
void ParamPlayer(TPlayer *p,int tjoueur)
{
    if(tjoueur == 1)
    {
        p->typejoueur = Humain;
        p->listeGagnant = NULL;
        p->listePerdante= NULL;
    }
    else if (tjoueur == 2)
    {
        p->typejoueur = IA;
        p->listeGagnant = NULL;
        p->listePerdante= NULL;
    }
}

TPlayer initplayerX()
{
     TPlayer p;
     int playerX , deco = 175;
      do{
        playerX = 0;
        printf("\t\t\t\t\t %c%c  le joueur avec des croix ('X') est : ",deco,deco);
        scanf("%d",&playerX);
    }while(playerX != 1 && playerX != 2);

    p.typeSymbole = croix;
    ParamPlayer(&p,playerX);
    printf("\n");

    return p;
 }

TPlayer initplayerO()
{
    TPlayer p;
    int playerO , deco = 175;
    do{
        playerO=0;
        printf("\t\t\t\t\t %c%c  le joueur avec des ronds ('O') est : ",deco,deco);
        scanf("%d",&playerO);
    }while(playerO != 1 && playerO != 2);

    p.typeSymbole = rond;
    ParamPlayer(&p,playerO);
    printf("\n");

     return p;
 }












/*

void ajoutesymbole(TabMorpion jeu ,Symboles symb , int posX , int posY)
{
    if(estvidecase(jeu,posX,posY))
        jeu[posX][posY] = symb;

}
TabMorpion allouePlateau(int taille){
    TabMorpion jeu;
    jeu = (Symboles**)malloc(sizeof(Symboles*)*taille);
    for (int i=0;i<taille;i++){
        jeu[i] = (Symboles*)malloc(sizeof(Symboles)*taille);
    }
    return jeu;
}*/

   /* int playerX;
    do{
        playerX = 0;
        printf("le joueur avec des croix ('X') est : ");
        scanf("%d",&playerX);
        printf("\n");
    }while(playerX != 1 && playerX != 2);

    int playerO;
    do{
        playerO=0;
        printf("le joueur avec des ronds ('O') est : ");
        scanf("%d",&playerO);
        printf("\n");
    }while(playerO != 1 && playerO != 2);
t_joueur getplayer()
{
    int player = 0;
    int symb = 0;
    printf("Le type du joueur 1 : ")


    t_joueur joueur;


     do{
        scanf("%d",&player)
    }while(player != 1 || player !=2)

    switch(player1){
        case 1 :
            joueur = Humain;
            break;
        case 2 :
            joueur = IA;
            break;
    }

    return joueur;

}


    scancoordonnee(p,&X,&Y);
        if(estvidecase(jeu,X,Y) && X < TAILLEJEU10x10 && Y < TAILLEJEU10x10)

*/


