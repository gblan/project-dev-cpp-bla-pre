/*
 * Animal.h
 *
 *  Created on: 20 janv. 2015
 *      Author: Julien
 */

#ifndef ANIMAL_H_
#define ANIMAL_H_

#include <sstream>
#include <string>

#include "../Joueur.h"
#include "../Pion.h"

class Affichage;
class Plateau;
class Joueur;

using namespace std;


class Animal: public Pion {
// attributs
private:
	int valeur;
	Joueur* joueur;

// m�thodes
public:
	Animal(int v = 0, Joueur* joueur = NULL) : valeur(v), joueur(joueur) {
	}
	virtual ~Animal() {
	}

	// getters
	int getValeur() {
		return valeur;
	}


	Joueur* getJoueur() const{
		return joueur;
	}

	void setJoueur(Joueur* j){
		joueur = j;
	}
	/**
	 * action appel� lorsque l'animal est pos� et est en fonction des autres animaux environnants
	 * Renvoie 1 si il n'y a plus d'action a effectu� apr�s l'appel de cette fonction, et 0 sinon
	 */
	virtual void action(Plateau *p, Affichage *affichage) = 0;


	virtual string print() const{
		return "Animal";
	}
};

#endif /* ANIMAL_H_ */
