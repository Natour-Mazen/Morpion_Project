#include <stdio.h>
#include <stdlib.h>

#include "Morpion.h"
#include "Types.h"

/*--------- Main ---------------------*/
int main()
{

    menuaffiche();
    TPlayer playerx = initplayerX();
    TPlayer playero = initplayerO();

    TabMorpion jeu ;
    initPlateau(jeu,TAILLEJEU10x10);
    printJeu(jeu,TAILLEJEU10x10);

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

