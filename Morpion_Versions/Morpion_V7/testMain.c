#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Morpion.h"
#include "Types.h"
#include "Quintuplet.h"
#include "position.h"

int main()
{

	//Menu Jeu
	menuaffiche();

	//Initialisation des Joueurs
	TPlayer playerX = initplayerX();
	TPlayer playerO = initplayerO();


	//Creation et affichage du plateau de Jeu
	TabMorpion jeu ;
    initPlateau(jeu);
    printJeu(jeu);

    //Creation du Tableau de Positions ainsi que la liste principale de Quintuplet
    init_tab(TAILLEJEU);
    listequintuplet mainList;
    mainList = makeMainList();
    mainList = suppDoublons(mainList);



    //Creation de Variables a utiliser pour chaque tour de Jeu
    T_Postion *ChoosenPos;
    T_Postion *DefPos;
    listequintuplet listTemp ;
    bool Xgagne = false ;
    bool Ogagne = false ;


     //===================Debut Jeu=================//

    //pour le test on fait 20 tour de jeu
    bool firstTurn = true ;
   // int tourJeu = 0 ;

    while ( !Xgagne && !Ogagne)
    {

    	//printf("Tour de Jeu n:%d J1 gagne : %d   J2 gagne : %d \n\n\n",tourJeu,Xgagne,Ogagne);


    	//Joueur X Joue
    	if (playerX.typejoueur == Humain)
        {
            if (firstTurn)
            {

                ChoosenPos = ajouteSymboleHUMAN(jeu, playerX);
                listTemp = getAllQuints(ChoosenPos, mainList);
                playerX.listeGagnant = concat(playerX.listeGagnant , listTemp);
                firstTurn = false ;
            }
            else
            {

                ChoosenPos = ajouteSymboleHUMAN(jeu, playerX);
                listTemp = getAllQuints(ChoosenPos, mainList);
                playerX.listeGagnant = concat(playerX.listeGagnant , listTemp);
            }
        }
        else if (playerX.typejoueur == IA)
        {

        	if (firstTurn)
            {

                ChoosenPos = bestPos(mainList,croix);
                ajouteSymboleBOT(jeu, ChoosenPos, playerX);
                listTemp = getAllQuints(ChoosenPos, mainList);
                playerX.listeGagnant = concat(playerX.listeGagnant , listTemp);
                majValPosQuintuplet(playerX.listeGagnant,croix);
                MiseAjourValQuint(ChoosenPos, playerX.listeGagnant);
                firstTurn = false ;
            }
            else
            {

            	majValPosQuintuplet(playerX.listeGagnant,croix);
                majValPosQuintuplet(playerO.listeGagnant,rond);
                ChoosenPos = bestPos(playerX.listeGagnant , croix);
                DefPos = bestPos(playerO.listeGagnant, rond);

                //Test
                //printf("%d > %d\n", bestPosint(playerX.listeGagnant, croix) , bestPosint(playerO.listeGagnant,rond));
                //fin test

                if(bestPosint(playerX.listeGagnant, croix) >= bestPosint(playerO.listeGagnant,rond))
                    {

                        ajouteSymboleBOT(jeu, ChoosenPos, playerX);
                        listTemp = getAllQuints(ChoosenPos, mainList);
                        playerX.listeGagnant = concat(playerX.listeGagnant , listTemp);
                        MiseAjourValQuint(ChoosenPos, playerX.listeGagnant);
                    }
                    else
                    {
                        ajouteSymboleBOT(jeu, DefPos, playerX);
                        listTemp = getAllQuints(DefPos, mainList);
                        playerX.listeGagnant = concat(playerX.listeGagnant , listTemp);
                        MiseAjourValQuint(DefPos, playerX.listeGagnant);
                    }

            }
        }

        //Joueur O joue

        if (playerO.typejoueur == Humain)
        {

            ChoosenPos = ajouteSymboleHUMAN(jeu, playerO);
            listTemp = getAllQuints(ChoosenPos, mainList);
            playerO.listeGagnant = concat(playerO.listeGagnant , listTemp);
            MiseAjourValQuint(ChoosenPos, playerO.listeGagnant);
        }
        else if (playerO.typejoueur == IA)
        {

        	if(playerO.listeGagnant != NULL)
            {

              majValPosQuintuplet(playerO.listeGagnant,rond);
              majValPosQuintuplet(playerX.listeGagnant,croix);
              ChoosenPos = bestPos(playerO.listeGagnant , rond);
		      DefPos = bestPos(playerX.listeGagnant , croix);

		      //Test
              //printf("%d > %d\n", bestPosint(playerX.listeGagnant, croix) , bestPosint(playerO.listeGagnant,rond));
              //fin test

              if(bestPosint(playerO.listeGagnant,rond) >= bestPosint(playerX.listeGagnant,croix))
              {

                ajouteSymboleBOT(jeu, ChoosenPos, playerO);
    			listTemp = getAllQuints(ChoosenPos, mainList);
    			playerO.listeGagnant = concat(playerO.listeGagnant , listTemp);
    			MiseAjourValQuint(ChoosenPos, playerO.listeGagnant);
		      }
              else
              {
    		    ajouteSymboleBOT(jeu, DefPos, playerO);
                listTemp = getAllQuints(DefPos, mainList);
    			playerO.listeGagnant = concat(playerO.listeGagnant , listTemp);
    			MiseAjourValQuint(DefPos, playerO.listeGagnant);
		      }

		    }
		    else
		    {
		    	ChoosenPos = bestPos(mainList, rond);
        		DefPos = bestPos(playerX.listeGagnant, croix);

        		//Test
                //printf("%d > %d\n", bestPosint(playerX.listeGagnant, croix) , bestPosint(playerO.listeGagnant,rond));
                //fin test

        		if(bestPosint(playerO.listeGagnant,rond) >= bestPosint(playerX.listeGagnant,croix))
              {

                ajouteSymboleBOT(jeu, ChoosenPos, playerO);
    			listTemp = getAllQuints(ChoosenPos, mainList);
    			playerO.listeGagnant = concat(playerO.listeGagnant , listTemp);
    			MiseAjourValQuint(ChoosenPos, playerO.listeGagnant);
		      }
              else
              {
    		    ajouteSymboleBOT(jeu, DefPos, playerO);
                listTemp = getAllQuints(DefPos, mainList);
    			playerO.listeGagnant = concat(playerO.listeGagnant , listTemp);
    			MiseAjourValQuint(DefPos, playerO.listeGagnant);
		      }
		    }


        }

        //Test
        //printf("test quitus main avant remove\n");
        //afficheQuintus(playerX.listeGagnant);
        //fin test


        //playerX.listeGagnant = removeClosedQuints(playerX.listeGagnant);
        //playerO.listeGagnant = removeClosedQuints(playerO.listeGagnant);

        //Test
        //printf("test quitus main apres remove\n");
        //afficheQuintus(playerX.listeGagnant);
        //fin test



        FINTOUR();

        //tourJeu++ ;
        Xgagne = checkVictory(playerX.listeGagnant);
        Ogagne = checkVictory(playerO.listeGagnant);


        Sleep(1500);
    }

     if(checkVictory(playerO.listeGagnant))
        printf("Le joueur O a gagne");
     else if (checkVictory(playerX.listeGagnant))
        printf("Le joueur X a gagne");


    liberationTab();

	return EXIT_SUCCESS;
}
