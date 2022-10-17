#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Morpion.h"

/**************************************************************************/

            /// INITALISATION & AFFICHAGE PLATEAU DE JEU ///

/**************************************************************************/
void initPlateau(TabMorpion jeu)
{
    for (int i=0;i<TAILLEJEU;i++){
        for (int j=0;j<TAILLEJEU;j++){
            jeu[i][j] = vide;
        }
    }
}

void printJeu(TabMorpion jeu)
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("    \t  \t\t\t\t    ");
    for(int x = 0; x < TAILLEJEU; x++){
		printf("%3d ", x);
	}
    printf("\n");
    for (int j=0;j<TAILLEJEU;j++){
            printf("\t\t\t\t\t%3d ", j);
        for (int i=0;i<TAILLEJEU;i++){
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

                        ///  AFFICHAGE GENERALE ///

/**************************************************************************/
void menuaffiche()
{
    system("color F");
    int  a = 177,b = 219;
    printf("\n\n\n\n\n\n");
    printf("\t\t\t\t\t %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b);
    printf("\t\t\t\t\t %c%c                                     %c%c\n",b,b,b,b);
    printf("\t\t\t\t\t %c%c Bienvenue Dans le tic tac toe 10*10 %c%c\n",b,b,b,b);
    printf("\t\t\t\t\t %c%c                                     %c%c\n",b,b,b,b);
    printf("\t\t\t\t\t %c%c%c%c%c%c%c%c%c%c%c%c%c%c Menu Joueur %c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",b,b,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,b,b);
    printf("\t\t\t\t\t %c%c                                     %c%c\n",b,b,b,b);
    printf("\t\t\t\t\t %c%c             1 : Humain              %c%c\n",b,b,b,b);
    printf("\t\t\t\t\t %c%c             2 : Robot               %c%c\n",b,b,b,b);
    printf("\t\t\t\t\t %c%c                                     %c%c\n",b,b,b,b);
    printf("\t\t\t\t\t %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b);
    printf("\n\n\n\n\n\n");
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
            if(estvidecase(jeu,X,Y) && X < TAILLEJEU && Y < TAILLEJEU)
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

    printJeu(jeu);
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

void printplayer(TPlayer p)
{
    const char* InitialeTypeJoueur[2]={"Humain", "Robot"};
    const char* InitialeTypeSymbole[3]={"VIDE", "X" , "O"};

    int b = 205;
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b);
    printf("le type du joueur est : %s\n", InitialeTypeJoueur[p.typejoueur]);
    printf("le type du Symbole est : %s\n", InitialeTypeSymbole[p.typeSymbole]);
    printf("le liste gagnante est : %p\n", p.listeGagnant);
    printf("le type Perdante est : %p\n", p.listePerdante);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b);
    printf("\n\n\n\n\n");
}


listequintuplet makeMainList() //Appelé qu'une fois en début de jeu pour faire la liste principale de quintuplets vides
{
    listequintuplet mainList;
    Quintuplet *q;
    initListeQuint(&mainList);

    for (int x_of_origin = 0 ; x_of_origin < TAILLEJEU ; x_of_origin++)
    {
        for (int y_of_origin = 0 ; y_of_origin < TAILLEJEU ; y_of_origin++)                                            //Parcourera les cases du plateau une par une
        {
            for (int x_direction = -1 ; x_direction <= 1 ; x_direction++)
            {
                for (int y_direction = -1 ; y_direction <= 1 ; y_direction++)                                               //Regardera dans toutes les directions possibles
                {
                    if(existeQuintu(x_of_origin, y_of_origin, x_direction, y_direction))                                    //on omet les doublons pour l'instant
                    {
                        q = initQuintu();
                        *q = createQuintu(x_of_origin, y_of_origin, x_direction, y_direction);
                        mainList = ajoutEnFinLQuint(mainList, q); //pas réellement d'intérêt, par rapport à Tête ou Fin vu que les premiers quintuplets seront generalement pris au milieu,
                    }                                             //à part pour la lisibilité : on aura les coordonnées (0,0) en premier
                }
            }
        }
    }

    return mainList;
}


listequintuplet suppDoublons(listequintuplet mainList) //Idem, appelé qu'une fois, juste après makeMainList pour supprimer les doublons crées
{                                                      //Tri complexe et peu opti, je songeais au tri par hachage mais dur de l'adapter sur des structures
    listequintuplet courant, parcours;                 //Corrigé par Mr.MENEVEAUX Daniel
    int X_start, Y_start, X_end, Y_end;
    bool found;

    if (mainList == NULL || mainList->suiv == NULL) return mainList;
    else
    {
        courant = mainList;
        while (courant != NULL)
        {
            X_start = courant->Qdata->pos[0].X;
            Y_start = courant->Qdata->pos[0].Y;
            X_end = courant->Qdata->pos[NTUPLET-1].X;
            Y_end = courant->Qdata->pos[NTUPLET-1].Y;
            parcours = getptrNextCellLQuint(courant);
            found = false;
            while (parcours != NULL && !found)
            {
                if (parcours->Qdata->pos[0].X == X_end &&
                    parcours->Qdata->pos[0].Y == Y_end &&
                    parcours->Qdata->pos[NTUPLET-1].X == X_start &&
                    parcours->Qdata->pos[NTUPLET-1].Y == Y_start)
                {
                    parcours->prec->suiv = parcours->suiv;
                    if (parcours->suiv != NULL)
                        parcours->suiv->prec = parcours->prec;
                    free(parcours->Qdata);
                    free(parcours);
                    found = true;
                }
                else
                {
                    parcours = getptrNextCellLQuint(parcours);
                }

            }
            courant = getptrNextCellLQuint(courant);
        }
    }

    return mainList;
}



void afficheMainList(listequintuplet l) //Fonction d'affichage, uniquement utilisé pour le débogage manuel
{
    int i = 1;
    listequintuplet courant = l;
    if (listeVideLQuint(l))
    {
        printf("rien a afficher\n");
        return;
    }
    else
    {
        while (!listeVideLQuint(courant))
        {
            printf("Quintuplet %d : [", i);
            for (int j = 0 ; j < NTUPLET ; j++)
            {
                printf(" { %d ; %d ; %d ; %d } ", courant->Qdata->pos[j].X, courant->Qdata->pos[j].Y, courant->Qdata->pos[j].valeur, courant->Qdata->pos[j].Sy);
            }
            printf("]\n");
            i++;
            courant = getptrNextCellLQuint(courant);
        }
    }
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


