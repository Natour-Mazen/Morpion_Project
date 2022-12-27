//=== Projet Morpion de L3 ===//

Le jeu est le jeu du morpion ou le but du jeu est d'aligner 5 même symboles.
Le jeu se joue à deux joueurs.
Dans notre version on peut jouer en 1VS1, 1VSbot ou botVSbot.

Sous linux:

//= Makefile =//
-make: 		 fait l'executable du jeu.
-make run: 	 fait l'executable et execute le jeu.
-make val: 	 fait l'extutable du jeu et l'execute avec Valgrind.
-make clean: supprime l'executable du jeu.


//= SDL ==//
Pour que ça marche sous Linux il faut aller dans Affichage.h
et mettre en commentaire :
	#include <SDL.h> // Pour windows  (Ligne 4)
et decommenter : 
	//#include <SDL2/SDL.h> // Pour Linux  (Ligne 5)
puis compiler les warnings du main sont pas problematique mais faut pas les enlever pour le bon fonctionnement de la SDL !