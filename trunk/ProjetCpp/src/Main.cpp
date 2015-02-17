//============================================================================
// Name        : ProjetCpp.cpp
// Author      : G
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include <cstdlib>

#include "Affichage/AffichageConsole.h"
#include "Affichage/Affichage.h"
#include "Joueur/JoueurReel.h"
#include "Joueur/Ordinateur.h"
#include "Plateau/Plateau.h"
#include "Joueur.h"
#include "Partie.h"
#include "Regle.h"
#include "Utils/Sauvegarde.h"

using namespace std;

int main(){
	int res;
	do{
		cout << "1- Test de programme" << endl;
		cout << "2- Appel du vrai programme" << endl;
		cin >> res;
	}while(res != 1 && res != 2);

	// Test, permet de debugger nos fonctions qu'on ajoute au fur et a mesure
	if(res == 1){
		JoueurReel j("Zizou");
		cout << j << endl;

		// Affichage de la liste initialis�e
		AffichageConsole affichage;
		affichage.afficheListAnimal(j.getListAnimaux());

		// Ajout d'Impala Jones dans le plateau
		ImpalaJones ij(1, 0);
		Plateau p;
		p.initImpalaJones(&ij);

		j.jouerCase(2, 1, &p, &affichage);
		j.jouerCase(3, 2, &p, &affichage);
		j.jouerCase(3, 1, &p, &affichage);
	}
	// Vrai programme qui sera ici quand tout sera fini
	else{
		srand (time(NULL));
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

			// Initialisation du plateau et de la partie
			Plateau *plateau = new Plateau();
			Partie partie = Partie(vectJoueur,plateau);

			// Affichage du plateau
			affichage->affichePlateau(*plateau);

			// Tirage au sort pour savoir qui commence
			int tourJoueur = affichage->pileOuFace(vectJoueur[0], vectJoueur[1]);	// i=0 ou 1

			// D�but de la partie
			affichage->messageDebutPartie(vectJoueur[tourJoueur]);

			// Demande de placement de Impala Jones
			affichage->demandePositionInitialeImpalaJones(plateau->getImpalaJones());

			// Lancement de la partie
			partie.lancerPartie(plateau->getImpalaJones()->getX(), plateau->getImpalaJones()->getY());

			// D�termination du joueur qui doit maintenant jouer
			int nbJoueurs = vectJoueur.size();
			if(tourJoueur == nbJoueurs-1){
				tourJoueur = 0;
			}
			else{
				tourJoueur++;
			}
			int nbCases, jeu;
			// D�roulement du jeu jusqu'� que la partie prenne fin
			while (!Regle::finPartie(*plateau)) {
				// Affiche du plateau
				affichage->affichePlateau(*plateau);

				// Message indiquant c'est a qui de jouer
				affichage->afficheTour(partie.getJoueurI(tourJoueur));

				// Affichage du menu du joueur
				do{
					jeu = affichage->menuJoueur(partie.getJoueurI(tourJoueur));
					// Si jeu = 2 ==> le joueur joue
					if(jeu == 2){
						bool joue = false;
						do{
							joue = partie.getJoueurI(tourJoueur)->jouer(partie.getPlateau(),affichage);
						}while(!joue);
						break;
					}
					// Le joueur ne joue pas mais fait une autre action
					else{
						switch(jeu){
							// Le joueur souhaite afficher sa liste de pions
							case(1) : affichage->afficheListAnimal(partie.getJoueurI(tourJoueur)->getListAnimaux());	break;

							// Le joueur souhaite sauvegarder la partie
							case(3) : Sauvegarde::sauvegarderPartie(partie,"save.txt");	break;	// a modifier le save.txt, et proposer au joueur d'entrer un nom de sauvegarde

							// Le joueur souhaite quitter la partie
							case(4) : return 0;
						}
					}
				}while(jeu!=2);

				// Affiche du plateau apres que le joueur ait jou�
				affichage->affichePlateau(*partie.getPlateau());

				// Le joueur doit d�placer Impala Jones avant de passer son tour
				nbCases = affichage->demandeDeplacerImpalaJones(*partie.getPlateau(),*partie.getPlateau()->getImpalaJones());
				partie.getPlateau()->getImpalaJones()->deplacer(nbCases, partie.getPlateau());

				// D�termination du prochain joueur
				if(tourJoueur == nbJoueurs-1){
					tourJoueur = 0;
				}
				else{
					tourJoueur++;
				}
			}
		}

		// Afficher les r�gles
		else if (menu_demarrage == 3) {
			affichage->afficheRegle();
		}

		// Charger une partie
		else if (menu_demarrage == 4) {

		}

		// Quitter
		else if (menu_demarrage == 5) {
			return 0;
		}
	}

	return 0;
}
