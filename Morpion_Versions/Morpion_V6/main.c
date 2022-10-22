#include <stdio.h>
#include <stdlib.h>

#include "Morpion.h"
#include "Types.h"
#include "Quintuplet.h"
#include "position.h"

/*--------- Main ---------------------*/
int main()
{

    /* ===TESTS DIVERS=== /
    init_tab(TAILLEJEU);

    listequintuplet mainList;
    TPlayer playerTest;
    T_Postion *ChoosenPos;

    mainList = makeMainList();

    mainList = suppDoublons(mainList);

    afficheQuintus(mainList);

    printf("\n\n\n\n");
    for (int i = 0 ; i < TAILLEJEU ; i++)
    {
        for (int j = 0 ; j < TAILLEJEU ; j++)
            printf("%2d|", getVal(TabPosition[i][j]));
        printf("\n______________________________\n");
    }

    playerTest = initplayerX();

    TabMorpion jeu ;
    initPlateau(jeu);
    printJeu(jeu);

    if (playerTest.typejoueur == 0)
        ChoosenPos = ajouteSymboleHUMAN(jeu, playerTest);
    else {
        ChoosenPos = &TabPosition[0][0];//bestPos(mainList);
        ajouteSymboleBOT(jeu, ChoosenPos, playerTest);
    }

    playerTest.listeGagnant = getAllQuints(ChoosenPos, mainList);

    afficheQuintus(mainList);
    printf("\n");
    afficheQuintus(playerTest.listeGagnant);

    mainList = removeSameQuints(&mainList, playerTest.listeGagnant);

    afficheQuintus(mainList);
    printf("\n");
    afficheQuintus(playerTest.listeGagnant);

    printJeu(jeu);

    printf("\n\n\n\n");
    for (int i = 0 ; i < TAILLEJEU ; i++)
    {
        for (int j = 0 ; j < TAILLEJEU ; j++)
            printf("%2d|", getSymbole(TabPosition[i][j]));
        printf("\n______________________________\n");
    }

    TabPosition[4][4].Sy = 2;
    removeClosedQuints(&playerTest.listeGagnant);
    afficheQuintus(playerTest.listeGagnant);

    mainList = vidertoutLQuint(mainList);

    free(mainList);

    //test = vidertoutLQuint(test);

    //free(test);

    playerTest.listeGagnant = vidertoutLQuint(playerTest.listeGagnant);

    playerTest.listePerdante = vidertoutLQuint(playerTest.listePerdante);

    */
    /* ===DEROULEMENT DU JEU=== */

    menuaffiche();
    TPlayer playerx = initplayerX();
    TPlayer playero = initplayerO();

    /* ===AFFICHAGE DU JEU=== */
    TabMorpion jeu ;
    initPlateau(jeu);
    printJeu(jeu);

    listequintuplet mainList;
    listequintuplet listTemp;

    /* ===PREPARATION DU ROBOT=== */
    if (playerx.typejoueur == 1 || playero.typejoueur == 1)
    {
        

        init_tab(TAILLEJEU);
        mainList = makeMainList();
        mainList = suppDoublons(mainList);
    }

    /* ===BOUCLE PRINCIPALE DU JEU=== */
    int gameState = 0;
    bool firstTurn = true;
    T_Postion *ChoosenPos;
    //int probaquijoue=(rand()%2);
    int i = 1;
    while ( gameState == 0 && i<5)
    {
        
        printf("tour de boucle num %d\n", i);
        i++;

         //Joueur X joue
        if (playerx.typejoueur == Humain)
        {
            if (firstTurn)
            {
                ChoosenPos = ajouteSymboleHUMAN(jeu, playerx);
                listTemp = getAllQuints(ChoosenPos, mainList);
                playerx.listeGagnant = concat(&playerx.listeGagnant , &listTemp);
                firstTurn = false ;
            }
            else
            {
                ChoosenPos = ajouteSymboleHUMAN(jeu, playerx);
                listTemp = getAllQuints(ChoosenPos, mainList);
                playerx.listeGagnant = concat(&playerx.listeGagnant , &listTemp);
            }
        }
        else
            {
                if (firstTurn)
                {
                    ChoosenPos = bestPos(mainList);
                    ajouteSymboleBOT(jeu, ChoosenPos, playerx);
                    listTemp = getAllQuints(ChoosenPos, mainList);
                    playerx.listeGagnant = concat(&playerx.listeGagnant , &listTemp);
                    firstTurn = false ;
                }
                else
                {
                    //majValPosQuintuplet(playerx.listeGagnant);
                    ChoosenPos = bestPos(playerx.listeGagnant);
                    ajouteSymboleBOT(jeu, ChoosenPos, playerx);
                    listTemp = getAllQuints(ChoosenPos, mainList);
                    playerx.listeGagnant = concat(&playerx.listeGagnant , &listTemp);
                }
                removeClosedQuints(playerx.listeGagnant);
                FINTOUR();
            }
            //Joueur O joue

        if (playero.typejoueur == Humain)
        {
            ChoosenPos = ajouteSymboleHUMAN(jeu, playero);
            listTemp = getAllQuints(ChoosenPos, mainList);
            playero.listeGagnant = concat(&playero.listeGagnant , &listTemp);
        }
        else
        {
            if(playero.listeGagnant != NULL)
            {
                //majValPosQuintuplet(playero.listeGagnant);
                ChoosenPos = bestPos(playero.listeGagnant);
                ajouteSymboleBOT(jeu, ChoosenPos, playero);
                listTemp = getAllQuints(ChoosenPos, mainList);
                playero.listeGagnant = concat(&playero.listeGagnant , &listTemp);
            }
            else
            {
                afficheQuintus(mainList);
                ChoosenPos = bestPos(mainList);
                ajouteSymboleBOT(jeu, ChoosenPos, playero);
                listTemp = getAllQuints(ChoosenPos, mainList);
                playero.listeGagnant = concat(&playero.listeGagnant , &listTemp);
            }
        }

        removeClosedQuints(playero.listeGagnant);
        FINTOUR();
    }    

    /* ===PAS DECOMMENTER ->=== */
    return EXIT_SUCCESS;
}




/*

    //printplayer(playerx);
    //printplayer(playero);

 //free(jeu);//= allouePlateau(TAILLEJEU10x10);
    TabMorpion jeu ;
    initPlateau(jeu,TAILLEJEU10x10);
    printJeu(jeu,TAILLEJEU10x10);

    printf("------------------------------------------------------\n");
    ajoutesymbole(jeu,rond,3,3);
    printJeu(jeu,TAILLEJEU10x10);

    printf("------------------------------------------------------\n");
    ajoutesymbole(jeu,croix,3,4);
    printJeu(jeu,TAILLEJEU10x10);

    printf("------------------------------------------------------\n");
    ajoutesymbole(jeu,rond,9,4);
    printJeu(jeu,TAILLEJEU10x10);

    printf("------------------------------------------------------\n");
    ajoutesymbole(jeu,croix,8,6);
    printJeu(jeu,TAILLEJEU10x10);

*/

