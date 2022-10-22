#include <stdio.h>
#include <stdlib.h>

#include "Morpion.h"
#include "Types.h"
#include "Quintuplet.h"
#include "position.h"

/*--------- Main ---------------------*/
int main()
{


    /* ===TESTS DIVERS=== */
    init_tab(TAILLEJEU);

    listequintuplet mainList;
    //TPlayer playerTest;

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

    listequintuplet test;

    test = getAllQuints(&TabPosition[0][0], &mainList);

    afficheQuintus(mainList);
    afficheQuintus(test);

    printf("\n");

    //playerTest = initplayerX();

    mainList = vidertoutLQuint(mainList);

    free(mainList);

    test = vidertoutLQuint(test);

    free(test);

    //playerTest.listeGagnant = vidertoutLQuint(playerTest.listeGagnant);

    //playerTest.listePerdante = vidertoutLQuint(playerTest.listePerdante); */


    /* ===DEROULEMENT DU JEU=== /

    menuaffiche();
    TPlayer playerx = initplayerX();
    TPlayer playero = initplayerO();

    / ===AFFICHAGE DU JEU=== /
    TabMorpion jeu ;
    initPlateau(jeu);
    printJeu(jeu);

    / ===PREPARATION DU ROBOT=== /
    if (playerx.typejoueur == 1 || playero.typejoueur == 1)
    {
        //on appelle ici toutes les fonctions pour que le bot puisse jouer
        listequintuplet mainList;

        init_tab(TAILLEJEU);
        mainList = makeMainList();
        mainList = suppDoublons(mainList);
    }

    / ===BOUCLE PRINCIPALE DU JEU=== /
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

    / ===PAS DECOMMENTER ->=== */
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

