/*
 * Partie.cpp
 *
 *  Created on: 20 janv. 2015
 *      Author: Guillaume
 */

#include "Partie.h"

#include <iostream>

#include "Regle.h"
#include "Affichage/Affichage.h"
#include "Pion/ImpalaJones.h"
#include "Pion.h"
#include "Plateau/Plateau.h"
#include "Utils/Sauvegarde.h"

/**
 * Lancer le premier tour
 */
int Partie::lancerPartie(int x, int y){
	ImpalaJones * ij = new ImpalaJones(x,y);
	return getPlateau()->initImpalaJones(ij);
}

int Partie::deroulementJeu(vector<Joueur*> vectJoueur, int tourJoueur, Affichage *affichage){
	int nbCases;

	// Affiche du plateau
	affichage->affichePlateau(*getPlateau());

	// Message indiquant c'est a qui de jouer
	affichage->afficheTour(getJoueurI(tourJoueur));

	// Cas ou le joueur n'a plus de pion
	if(getJoueurI(tourJoueur)->getListAnimaux().size() == 0){
		affichage->messagePlusDePion();
	}
	// Cas ou le joueur peut jouer
	else{
		if(getJoueurI(tourJoueur)->jouerTour(getPlateau(),affichage, *this) == 0){
			return -2;
		}
	}
	if(Regle::finPartie(*getPlateau())){
		return 1;	// fin de partie
	}

	// On recupere le nombre de case qui faut d�caler Impala Jones
	nbCases = getJoueurI(tourJoueur)->deplacementImpalaJones(*getPlateau(), *getPlateau()->getImpalaJones(), affichage);

	// Au cas ou, mais ne devrait pas arriv� car finPartie est appel� avant
	if(nbCases == -1){
		return 1;
	}

	// Deplacement d'Impala Jones
	int ancien_x = getPlateau()->getImpalaJones()->getX();
	int ancien_y = getPlateau()->getImpalaJones()->getY();
	return getPlateau()->getImpalaJones()->deplacer(nbCases, getPlateau(), ancien_x, ancien_y);
}

/**
 * Demander les noms, attribuer les cartes
 */
int Partie::initJoueurs(){

	return 0;
}

void Partie::finPartie(vector<Joueur*> vectJoueur, Affichage *affichage){
	Joueur *vainqueur = NULL;
	for(unsigned int i=0;i<vectJoueur.size();i++){
		int total = vectJoueur[i]->getNbPoints()+Regle::calculPointsJoueur(*getPlateau(),vectJoueur[i]);
		vectJoueur[i]->setNbPoints(total);

		if(vainqueur == NULL){
			vainqueur = vectJoueur[i];
		}else{
			if(vainqueur->getNbPoints()<vectJoueur[i]->getNbPoints()){
				vainqueur = vectJoueur[i];
			}
		}
	}

	/* affichage du vainqueur */
	affichage->afficherVainqueur(vainqueur);
}


int Partie::sauvegarde(string path){
	return 0;
}

int Partie::chargement(string path){
	/*
	string file = path + ".txt";
	// Lecture
	ifstream fichier(file, ios::in);
	if(!fichier){
		cout << "Erreur lors de l'ouverture du fichier " << file << endl;
		return -1;
	}
	// Lecture ligne par ligne
    string ligne;
    while(getline(fichier, ligne)){
            cout << ligne << endl;
    }

	// Fin de la lecture
	fichier.close();
	*/
	return 0;
}
