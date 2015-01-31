/*
 * Joueur.h
 *
 *  Created on: 20 janv. 2015
 *      Author: Guillaume
 */

#ifndef JOUEUR_H_
#define JOUEUR_H_

#include <iostream>
#include <string>
#include <vector>

#include "Pion/Animal/Effrayant/Crocodile.h"
#include "Pion/Animal/Effrayant/Lion.h"
#include "Pion/Animal/Neutre/Elephant.h"
#include "Pion/Animal/Peureux/Gazelle.h"
#include "Pion/Animal/Peureux/Zebre.h"
#include "Pion/Animal.h"

using namespace std;

/**
 * Classe abstraite, car contient une m�thode virtuelle pure (=0;) pour ne pas l'instancier.
 */

class Animal;
class Gazelle;

class Joueur {
private:
	int nbPoints;
	string nom;
	vector<Animal> listAnimaux;

	/**
	 * Permet d'initialiser tous les pions d'un joueur
	 * 6 gazelles
	 * 5 zebres
	 * 1 elephant
	 * 1 lion
	 * 2 crocos
	 */
	void initListPions(int nbGazelles = 0, int nbZebres = 0, int nbElephants = 0, int nbLions = 0, int nbCrocos = 0) {

		/**
		 * Utiliser les pointeurs ???
		 */

		int i;

		// 6 gazelles
		for(i=0; i< nbGazelles; i++){
			listAnimaux.push_back(*(new Gazelle()));
		}
		// 5 zebres
		for(i=0; i< nbZebres; i++){
			listAnimaux.push_back(*(new Zebre()));
		}
		// 1 elephant
		for(i=0; i< nbElephants; i++){
			listAnimaux.push_back(*(new Elephant()));
		}
		// 1 lion
		for(i=0; i< nbLions; i++){
			listAnimaux.push_back(*(new Lion()));
		}
		// 2 crocodiles
		for(i=0; i< nbCrocos; i++){
			listAnimaux.push_back(*(new Crocodile()));
		}
	}

public:
	Joueur(int nbPoints = 0, string nom = "", int nbGazelles = 0, int nbZebres = 0, int nbElephants = 0, int nbLions = 0, int nbCrocos = 0) :
			nbPoints(nbPoints), nom(nom), listAnimaux(0) {
		initListPions(nbGazelles, nbZebres, nbElephants, nbLions, nbCrocos);
	}

	virtual ~Joueur() {

	}

	const vector<Animal>& getListAnimaux() const {
		return listAnimaux;
	}

	Animal* getAnimal(const int i){
		Animal a = listAnimaux[i];
		Animal * result = &a;
		return result;
	}

	int getNbPoints() const {
		return nbPoints;
	}

	const string& getNom() const {
		return nom;
	}

	void setNbPoints(int nbPoints) {
		this->nbPoints = nbPoints;
	}

	friend ostream& operator<<(ostream &strm, const Joueur &a) {
		strm << "Joueur(" << a.nom << ") : "<< a.nbPoints << "."<< endl;
		return strm;
	}

	int jouer();

	int placementAnimal(Animal a, int x, int y);
};

#endif /* JOUEUR_H_ */
