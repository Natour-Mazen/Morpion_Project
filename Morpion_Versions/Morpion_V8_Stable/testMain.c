#include <stdio.h>
#include <stdlib.h>

#include "Morpion.h"
#include "Types.h"
#include "Quintuplet.h"
#include "position.h"
#include "windows.h"

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


    bool firstTurn = true ;

    while (!Xgagne && !Ogagne)
    {



    	//Joueur X Joue
    	if (playerX.typejoueur == Humain)
        {
            if (firstTurn)
            {
                ChoosenPos = ajouteSymboleHUMAN(jeu, playerX);
                listTemp = getAllQuints(ChoosenPos, mainList);
                playerX.listeGagnant = concat(playerX.listeGagnant , listTemp);
                MiseAjourValQuint(ChoosenPos, playerX.listeGagnant);
                firstTurn = false ;
            }
            else
            {
                playerX.listeGagnant = removeClosedQuints(playerX.listeGagnant);
                ChoosenPos = ajouteSymboleHUMAN(jeu, playerX);
                listTemp = getAllQuints(ChoosenPos, mainList);
                playerX.listeGagnant = concat(playerX.listeGagnant , listTemp);
                MiseAjourValQuint(ChoosenPos, playerX.listeGagnant);
            }
        }
        else
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
                playerX.listeGagnant = removeClosedQuints(playerX.listeGagnant);
            	majValPosQuintuplet(playerX.listeGagnant,croix);
                majValPosQuintuplet(playerO.listeGagnant,rond);
                ChoosenPos = bestPos(playerX.listeGagnant , croix);
                DefPos = bestPos(playerO.listeGagnant, rond);



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

        Xgagne = checkVictory(playerX.listeGagnant);

        if (!Xgagne)
        {
            //Joueur O joue
            if (playerO.typejoueur == Humain)
            {
                playerO.listeGagnant = removeClosedQuints(playerO.listeGagnant);
                ChoosenPos = ajouteSymboleHUMAN(jeu, playerO);
                listTemp = getAllQuints(ChoosenPos, mainList);
                playerO.listeGagnant = concat(playerO.listeGagnant , listTemp);
                MiseAjourValQuint(ChoosenPos, playerO.listeGagnant);
            }
            else
            {

                if(playerO.listeGagnant != NULL)
                {
                  playerO.listeGagnant = removeClosedQuints(playerO.listeGagnant);
                  majValPosQuintuplet(playerO.listeGagnant,rond);
                  majValPosQuintuplet(playerX.listeGagnant,croix);
                  ChoosenPos = bestPos(playerO.listeGagnant , rond);
                  DefPos = bestPos(playerX.listeGagnant , croix);


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
        }

        FINTOUR();
        Ogagne = checkVictory(playerO.listeGagnant);
        Sleep(1000);
    }

    if (Xgagne)
        printgagnant(playerX);
    if (Ogagne)
        printgagnant(playerO);

    liberationTab();

    mainList = vidertoutLQuint(mainList);
    playerO.listeGagnant = vidertoutLQuint(playerO.listeGagnant);
    playerO.listePerdante = vidertoutLQuint(playerO.listePerdante);
    playerX.listeGagnant = vidertoutLQuint(playerX.listeGagnant);
    playerX.listePerdante = vidertoutLQuint(playerX.listePerdante);

    Sleep(6000);
	return EXIT_SUCCESS;
}
