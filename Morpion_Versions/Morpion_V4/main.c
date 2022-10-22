#include <stdio.h>
#include <stdlib.h>

#include "Morpion.h"
#include "Types.h"
#include "Quintuplet.h"
#include "position.h"

/*--------- Main ---------------------*/
int main()
{

    /* ===TESTS AVEC LISTES SANS JEU=== */
    init_tab(TAILLEJEU);
    //printf("%d %d", getX(TabPosition[3][7]), getY(TabPosition[3][7]));
    listequintuplet mainList;
    TPlayer playerTestA;
    TPlayer playerTestB;

    mainList = makeMainList();
    afficheMainList(mainList);

    printf("\n\n\n\n\n\n\n");
    mainList = suppDoublons(mainList);

    afficheMainList(mainList);


    for (int i = 0 ; i < TAILLEJEU ; i++)
    {
        for (int j = 0 ; j < TAILLEJEU ; j++)
            printf("%2d/", getVal(TabPosition[i][j]));
        printf("\n");
    }

    //playerTest = initplayerX();

    /*Quintuplet *q;

    q = initQuintu();

    *q = createQuintu(5,5,1,0);

    playerTest.listeGagnant = ajoutEnTeteLQuint(playerTest.listeGagnant, q);

    afficheMainList(playerTest.listeGagnant);

    x = gameState(mainList, playerTest);

    printf("%d", x);

    playerTest.listeGagnant->Qdata->valquintuplet = 99999;

    x = gameState(mainList, playerTest);

    printf("%d", x);

    mainList = vidertoutLQuint(mainList); */

    /*playerTest.listeGagnant = vidertoutLQuint(playerTest.listeGagnant);

    playerTest.listePerdante = vidertoutLQuint(playerTest.listePerdante);

    x = gameState(mainList, playerTest);

    printf("%d", x);

    afficheMainList(mainList);*/


    /* ===TESTS SANS LISTES AVEC JEU=== */

    /*menuaffiche();
    TPlayer playerx = initplayerX();
    TPlayer playero = initplayerO();

    TabMorpion jeu ;
    initPlateau(jeu);
    printJeu(jeu);

    // boucle principale du jeu
    int cont = 30;
    int probaquijoue=(rand()%2);
    while ( cont != 0 )
    {
        if(probaquijoue == 0 )
        {
            //joueurX puis joueurO
            ajoutesymbole(jeu,playerx);
            ajoutesymbole(jeu,playero);

        }
        else if (probaquijoue == 1 )
        {
            //joueurO puis joueurX
            ajoutesymbole(jeu,playero);
            ajoutesymbole(jeu,playerx);

        }

        cont--;
    }






        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    */
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

