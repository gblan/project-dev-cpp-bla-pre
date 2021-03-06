/*
 * Partie.h
 *
 *  Created on: 20 janv. 2015
 *      Author: Guillaume
 */

#ifndef PARTIE_H_
#define PARTIE_H_

#include <string>
#include <vector>

#include "Joueur.h"

class Partie {
private:
	vector<Joueur*> vectJoueur;
	Plateau *plateau = NULL;
public:
	Partie(vector<Joueur*> vectJoueur, Plateau *plateau) :
		vectJoueur(vectJoueur), plateau(plateau){};

	virtual ~Partie(){};

	Joueur* getJoueurI(int i){
		return vectJoueur[i];
	}

	vector<Joueur*> getVectJoueur(){
		return vectJoueur;
	}

	Plateau* getPlateau(){
		return plateau;
	}

	/* Lancer le premier tour en initialisant la position d'ImpalaJones	 */
	int lancerPartie(int x, int y);

	/* le tour du joueur pass� en parametre */
	int deroulementJeu(vector<Joueur*> vectJoueur, int tourJoueur, Affichage *affichage);

	/* le tour du joueur pass� en parametre */
	void finPartie(vector<Joueur*> vectJoueur, Affichage *affichage);

};

#endif /* PARTIE_H_ */
