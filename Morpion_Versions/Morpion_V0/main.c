#include <stdio.h>
#include <stdlib.h>

#include "Morpion.h"
#include "Types.h"

/*--------- Main ---------------------*/
int main()
{
    int PlayerX , PlayerO;
    menuaffiche(&PlayerX,&PlayerO);

    TabMorpion jeu ;//= allouePlateau(TAILLEJEU10x10);
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







    //free(jeu);
    return EXIT_SUCCESS;
}
