#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Morpion.h"
#include "position.h"

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
    printf("\t\t\t\t\t %c%c             2 : Leo                 %c%c\n",b,b,b,b);
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

T_Postion *scancoordonnee(TPlayer p,int *X , int *Y)
{
    int deco = 175 , deco1 = 254;
    const char* InitialeTypeSymbole[3]={"VIDE", "X" , "O"};

    printf("\n\n\t\t\t\t\t      %c%c Joueur '%s'  : \n\n",deco1,deco1,InitialeTypeSymbole[p.typeSymbole]);
    printf("\t\t\t\t\t %c%c  Entrez le numero de la colonne(x) : ",deco,deco);
    scanf("%d",X);
    printf("\t\t\t\t\t %c%c  Entrez le numero de la ligne(y) : ",deco,deco);
    scanf("%d",Y);

    return &TabPosition[*X][*Y];
}

T_Postion *ajouteSymboleHUMAN(TabMorpion jeu, TPlayer p)
{
    T_Postion *ChoosenPos;
    int X,Y;

    bool temp = false;

    do{
        ChoosenPos = scancoordonnee(p,&X,&Y);
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

    SetSymbole(p.typeSymbole, ChoosenPos);

    printJeu(jeu);

    return ChoosenPos;
}

void ajouteSymboleBOT(TabMorpion jeu, T_Postion *ChoosenPos, TPlayer p)
{
    
    printf("\n\n\n\n\n\n\n\n\n%d\n\n\n\n\n\n\n\n\n",getSymboleP(ChoosenPos));

    jeu[getXP(ChoosenPos)][getYP(ChoosenPos)] = p.typeSymbole;

    SetSymbole(p.typeSymbole, ChoosenPos);

    printf("\n\n\n\n\n\n\n\n\n%d\n\n\n\n\n\n\n\n\n",getSymboleP(ChoosenPos));

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

/**************************************************************************/

                /// FONCTIONS QUI GERENT LES LISTES ///

/**************************************************************************/

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
    bool found;

    if (mainList == NULL || mainList->suiv == NULL) return mainList;
    else
    {
        courant = mainList;
        while (courant != NULL)
        {
            parcours = getptrNextCellLQuint(courant);
            found = false;
            while (parcours != NULL && !found)
            {
                if (equalsP(parcours->Qdata->pos[0], courant->Qdata->pos[NTUPLET-1]) &&
                    equalsP(parcours->Qdata->pos[NTUPLET-1], courant->Qdata->pos[0]))
                {
                    for (int i = 0 ; i < NTUPLET ; i++)
                    {
                        TabPosition[getXP(parcours->Qdata->pos[i])][getYP(parcours->Qdata->pos[i])].valeur --;
                    }
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

listequintuplet getAllQuints(T_Postion *pos, listequintuplet l)
{
    listequintuplet result_list;
    initListeQuint(&result_list); //notre liste retournee

    bool found;

    //On suppose l avec au moins un élément (vérifié avant son appel)
    while (l != NULL) //on parcourt l'integralite de notre liste l
    {
        found = false;
        for (int i = 0 ; i < NTUPLET ; i++) //on compare chaque case du quintuplet avec notre case recherchee
            if (equalsP(pos, l->Qdata->pos[i]) && !found)
                found = true; //si on trouve une case identique, on arrête le parcours du quintuplet, on passe à sa suppression sinon on passe au quintuplet suivant
        if (found == true){
            result_list = ajoutEnTeteLQuint(result_list, l->Qdata); //on transfere deja le quintuplet
            l->suiv->prec = l->prec;
            l->prec->suiv = l->suiv;
        }

        l = l->suiv; //et avancer le ptr courant
    }

    return result_list;
}

listequintuplet removeSameQuints(listequintuplet *l1, listequintuplet l2)
{
    listequintuplet courant, parcoursL2;
    bool equals ;

    courant = *l1;

    while (courant != NULL)
    {
        parcoursL2 = l2;
        while (parcoursL2 != NULL)
        {
            equals = true;
            for (int i = 0 ; i < NTUPLET ; i++)
                if (equalsP(courant->Qdata->pos[i], parcoursL2->Qdata->pos[i]) && equals)
                    equals = true;
                else equals = false;

            if (equals == true)
            {
                listequintuplet aSuppr = courant;
                courant = courant->suiv; //et avancer le ptr courant

                if(aSuppr->suiv == NULL)
                {
                    aSuppr->prec->suiv = NULL;
                }
                else if(aSuppr->prec == NULL) //si c'est le premier quintuplet de la liste, on pense a faire les
                {
                    aSuppr->suiv->prec = NULL;
                    *l1 = (*l1)->suiv;
                    (*l1)->prec = NULL;
                }
                else //si c'est pas le cas, on fait la même chose différemment
                {
                    aSuppr->suiv->prec = aSuppr->prec;
                    aSuppr->prec->suiv = aSuppr->suiv;
                }
                free(aSuppr);//on supprime notre cellule, notre quintuplet est tjrs en memoire dans notre result_list
                break;
            }
            else parcoursL2 = parcoursL2->suiv;
        }
        if (!equals) courant = courant->suiv;
    }

    return *l1;
}

void removeClosedQuints(listequintuplet *l)
{
    listequintuplet courant;
    bool xExist, oExist;

    courant = *l;

    while (courant != NULL)
    {
        oExist = false;
        xExist = false;
        for (int i = 0 ; i < NTUPLET ; i++)
        {
            if (!oExist && courant->Qdata->pos[i]->Sy == rond)
                oExist = true;
            if (!xExist && courant->Qdata->pos[i]->Sy == croix)
                xExist = true;
        }

        if (oExist && xExist)
        {
            listequintuplet aSuppr = courant;
            courant = courant->suiv; //et avancer le ptr courant

            if(aSuppr->suiv == NULL)
            {
                aSuppr->prec->suiv = NULL;
            }
            else if(aSuppr->prec == NULL) //si c'est le premier quintuplet de la liste, on pense a faire les
            {
                aSuppr->suiv->prec = NULL;
                *l = (*l)->suiv;
                (*l)->prec = NULL;
            }
            else //si c'est pas le cas, on fait la même chose différemment
            {
                aSuppr->suiv->prec = aSuppr->prec;
                aSuppr->prec->suiv = aSuppr->suiv;
            }
            free(aSuppr->Qdata);
            free(aSuppr);
        }
        else courant = courant->suiv;
    }
}

void afficheQuintus(listequintuplet l) //Fonction d'affichage, uniquement utilisé pour le débogage manuel
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
            printf("Quintuplet %3d : [", i);
            for (int j = 0 ; j < NTUPLET ; j++)
            {
                printf(" { %2d ; %2d ; %2d ; %2d } ", getXP(courant->Qdata->pos[j]), getYP(courant->Qdata->pos[j]), getValP(courant->Qdata->pos[j],vide), getSymboleP(courant->Qdata->pos[j]));
            }
            printf("]\n");
            i++;
            courant = getptrNextCellLQuint(courant);
        }
    }
}
/**************************************************************************/

                /// FONCTIONS DE VICTOIRE ///

/**************************************************************************/

bool checkVictory(listequintuplet l)
{
    listequintuplet parcours = l;

    while (parcours != NULL)
    {
        if(getPtrDataLQuint(parcours)->valquintuplet == 99999) //valeur à modifier precisement, valeur maximale possible, cas d'un quintuplet à 5 symboles
            return true;
        else parcours = getptrNextCellLQuint(parcours);
    }

    return false; //on a pas trouvé de quintuplet à 5 symboles
}

int gameState(listequintuplet mainList, TPlayer p)
{
    if (listeVideLQuint(mainList) && listeVideLQuint(p.listeGagnant) && listeVideLQuint(p.listePerdante))
        return 2; //Partie avec plus de possibilité de victoire des deux joueurs, cas le - probable, à mettre en dernier au switch
    else if(checkVictory(p.listeGagnant))
        return 1; //Partie avec la victoire du joueur, quintuplet à 5 symboles de trouvé, second cas le + probable
    else return 0; //Partie avec toujours une possibilité de victoire, cas le + probable d'arriver donc à prioriser au switch après
}

/**************************************************************************/

                /// FONCTIONS LIEES AU BOT ///

/**************************************************************************/

T_Postion *bestPos(listequintuplet l)
{
    Symboles sym = getSymboleP(l);
    
    T_Postion *max_Pos;
    int valmaxPos = 0 ;
    //On suppose l avec au moins un élément (vérifié avant son appel)
    while(!listeVideLQuint(l))
    {
        for (int i = 0 ; i < NTUPLET ; i++)
        {
            if ((getValP(l->Qdata->pos[i] , sym) > valmaxPos) && (l->Qdata->pos[i]->Sy == vide)){ // best pos sans symbole et en fonction de qui fait lappel ajout de getSymbole
                max_Pos = l->Qdata->pos[i];
                valmaxPos = getValP(l->Qdata->pos[i] , sym);
            }
        }
         

        l=l->suiv; 
    }

    return max_Pos;
}


void majValPosQuintuplet(listequintuplet list){

    
    afficheQuintus(list);


    Listpos listP = NULL;
    listequintuplet listTest = list;
    listequintuplet listTest2 = list;
    Symboles sym = getSymbolePlayer(list);
    printf("je suis dans majval\n");

    if(listTest== NULL){
        printf("hi\n");
    }else{
        printf("hello\n");
    }

    while(listTest != NULL){
        for(int i = 0 ; i<NTUPLET ; i++){
            printf("je suis dans le premier for %d   je  ne suis pas dans la liste %d\n",i,isInList(listTest->Qdata->pos[i],listP));
            if(!isInList(listTest->Qdata->pos[i],listP)){
                printf("je suis dans le premier for %d   je  ne suis pas dans la liste %d\n",i,isInList(listTest->Qdata->pos[i],listP));
                addInList(listTest->Qdata->pos[i],&listP);
                
            }
        }

        listTest = listTest->suiv ;
    }

    while(listTest2 != NULL){
        for(int i = 0 ; i<NTUPLET ; i++){
            majValPosition(listTest->Qdata->pos[i],listP,sym);
            }
        listTest2 = listTest2->suiv ;
    }

}



void FINTOUR(){
    finDeTour();
}




listequintuplet concat(listequintuplet *list1 , listequintuplet *list2){

    listequintuplet temp = *list1;

    if(*list1==NULL){
        return *list2;
    }

    while(temp->suiv != NULL){
        temp = temp->suiv;
    }

    temp->suiv = *list2;

    return *list1;
}
