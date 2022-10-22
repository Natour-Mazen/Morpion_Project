#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Morpion.h"


/*TabMorpion allouePlateau(int taille){
    TabMorpion jeu;
    jeu = (Symboles**)malloc(sizeof(Symboles*)*taille);
    for (int i=0;i<taille;i++){
        jeu[i] = (Symboles*)malloc(sizeof(Symboles)*taille);
    }
    return jeu;
}*/

void initPlateau(TabMorpion jeu, int taille){
    for (int i=0;i<taille;i++){
        for (int j=0;j<taille;j++){
            jeu[i][j] = vide;
        }
    }
}

void printJeu(TabMorpion jeu, int taille){
    printf("    ");
    for(int x = 0; x < taille; x++){
		printf("%3d ", x);
	}
    printf("\n");
    for (int j=0;j<taille;j++){
            printf("%3d ", j);
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

bool estvidecase(TabMorpion jeu,int posX , int posY)
{
    return (jeu[posX][posY] == vide);
}

void ajoutesymbole(TabMorpion jeu ,Symboles symb , int posX , int posY)
{
    if(estvidecase(jeu,posX,posY))
        jeu[posX][posY] = symb;

}

void menuaffiche()
{
    printf("Bienvenue Dans le tic tac toe 10*10\n");
    printf("------------------Menu Joueur-------------------\n");
    printf("1 : Humain \n");
    printf("2 : Robot \n");
    printf("------------------------------------------------\n");

    int playerX;
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

}

/*
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

*/


