//============================================================================
// Name        : ProjetCpp.cpp
// Author      : G
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================
 
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "Affichage/AffichageConsole.h"
#include "Joueur/JoueurReel.h"
#include "Joueur/Ordinateur.h"
#include "Joueur.h"
#include "Partie.h"
#include "Pion/ImpalaJones.h"
#include "Plateau/Plateau.h"
#include "Regle.h"
#include "Utils/SaisieSecure.h"
#include "Utils/Sauvegarde.h"

using namespace std;

int main() {
	srand(time(NULL));
	cout << "======================================" << endl;
	cout << "            Dr�le de Z�bres           " << endl;
	cout << "======================================" << endl;

	// Demande le type d'affichage aux joueurs
	int typeAffichage = Affichage::demandeTypeAffichage();
	Affichage * affichage = NULL;
	if (typeAffichage == 1) {
		affichage = new AffichageConsole();
	}
	else {
		cout << "Cette affichage n'a pas �t� impl�ment�e" << endl;
		return 0;
	}
	bool regle = false;
	do {
		// Appel du menu de d�marrage
		int menu_demarrage = affichage->menuDemarrage();

		// Jouer
		if (menu_demarrage == 1 || menu_demarrage == 2) {
			// Initialisation du joueur 1
			Joueur *joueur1 = new JoueurReel();
			affichage->demandeNomJoueur(joueur1);

			// Initialisation du joueur 2
			Joueur *joueur2 = NULL;
			// Cas ou le joueur 2 est un joueur "reel"
			if (menu_demarrage == 2) {
				joueur2 = new JoueurReel();
				affichage->demandeNomJoueur(joueur2);
			}
			// Cas ou le joueur 2 est l'ordinateur
			else {
				joueur2 = new Ordinateur();
			}

			// Les joueurs sont dans une liste pour les manipuler plus facilement par la suite
			vector<Joueur*> vectJoueur;
			vectJoueur.push_back(joueur1);
			vectJoueur.push_back(joueur2);

			// Initialisation de la partie
			int num_plateau = affichage->demandePlateau();
			Partie partie = Partie(vectJoueur, new Plateau(num_plateau, false, new ImpalaJones(0, 0)));

			// Affichage du plateau
			affichage->affichePlateau(*partie.getPlateau());

			// Tirage au sort pour savoir qui commence
			int tourJoueur = affichage->pileOuFace(vectJoueur[0], vectJoueur[1], menu_demarrage);	// i=0 ou 1
			// D�but de la partie
			affichage->messageDebutPartie(vectJoueur[tourJoueur]);

			// Demande de placement de Impala Jones
			vectJoueur[tourJoueur]->joueurInitImpala(partie.getPlateau(), affichage); /* TODO A TESTER */

			// D�termination du joueur qui doit maintenant jouer
			int nbJoueurs = vectJoueur.size();
			if (tourJoueur == nbJoueurs - 1) {
				tourJoueur = 0;
			}
			else {
				tourJoueur++;
			}

			// D�roulement du jeu jusqu'� que la partie prenne fin
			int continuer = 0;
			while (continuer != 1) {
				continuer = partie.deroulementJeu(vectJoueur, tourJoueur, affichage);	// = 0 si tout est ok
				if (continuer == -2) {
					// Le joueur a d�cid� de quitter
					return 0;
				}
				else if (continuer == -1) {
					cerr << "Une erreur est pr�sente dans deroulementJeu (Partie.cpp)" << endl;
				}
				// D�termination du prochain joueur
				if (tourJoueur == nbJoueurs - 1) {
					tourJoueur = 0;
				}
				else {
					tourJoueur++;
				}
			}
			/* Affichage en fin de partie */
			partie.finPartie(vectJoueur, affichage);
		}

		// Afficher les r�gles
		else if (menu_demarrage == 3) {
			affichage->afficheRegle();
			regle = true;
		}

		// Charger une partie
		else if (menu_demarrage == 4) {
			int tourJoueur;
			Partie* partie = Sauvegarde::chargementPartie("save.txt", tourJoueur);

			// D�roulement du jeu jusqu'� que la partie prenne fin
			int continuer = 0;
			while (continuer != 1) {
				continuer = partie->deroulementJeu(partie->getVectJoueur(), tourJoueur, affichage);	// = 0 si tout est ok
				if (continuer == -2) {
					// Le joueur a d�cid� de quitter
					return 0;
				}
				else if (continuer == -1) {
					cerr << "Une erreur est pr�sente dans deroulementJeu (Partie.cpp)" << endl;
				}
				int nbJoueurs = partie->getVectJoueur().size();
				// D�termination du prochain joueur
				if (tourJoueur == nbJoueurs - 1) {
					tourJoueur = 0;
				}
				else {
					tourJoueur++;
				}
			}
			/* Affichage en fin de partie */
			partie->finPartie(partie->getVectJoueur(), affichage);
		}

		// Quitter
		else if (menu_demarrage == 5) {
			return 0;
		}
	} while (regle || affichage->retourMenuPrincipal());
	affichage->finProgramme();
	return 0;
}
