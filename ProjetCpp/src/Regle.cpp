/*
 * Regle.cpp
 *
 *  Created on: 6 f�vr. 2015
 *      Author: Julien
 */

#include "Regle.h"

#include "Joueur.h"
#include "Pion/Animal/Peureux.h"
#include "Pion/Animal.h"
#include "Pion.h"
#include "Plateau/Case.h"
#include "Plateau/Plateau.h"

/**
 * Renvoie vrai si la case (colonne, ligne) dans le plateau poss�de un pion
 */
bool Regle::caseRempli(Plateau p, int colonne, int ligne){
	return (p.getCase(colonne, ligne)->getPion() != NULL);
}

/**
 * Renvoie vrai si la colonne pass�e en param�tre poss�de aucune case vide (toutes les cases de la colonne contiennent des pions)
 */
bool Regle::colonneRempli(Plateau p, int colonne){
	unsigned int i;
	for (i = 1; i < p.getTaillePlateauY() - 1; i++) {
		if (p.getCase(colonne, i)->getPion() == NULL) {
			return false;
		}
	}
	return true;
}

/**
 * Renvoie vrai si la ligne pass�e en param�tre poss�de aucune case vide (toutes les cases de la ligne contiennent des pions)
 */
bool Regle::ligneRempli(Plateau p, int ligne){
	unsigned int i;
	for (i = 1; i < p.getTaillePlateauX() - 1; i++) {
		if (p.getCase(i, ligne)->getPion() == NULL) {
			return false;
		}
	}
	return true;
}

/**
 * Renvoie vrai si la partie est termin�e (toutes les cases du plateau ont un pion)
 */
bool Regle::finPartie(Plateau p){
	unsigned int i;
	for (i = 1; i < p.getTaillePlateauX() - 1; i++) {
		if (!colonneRempli(p, i)) {
			return false;
		}
	}
	return true;
}

/**
 * Renvoie vrai si Impala Jones peut �tre pos� nbCases plus loin dans le plateau p selon sa position initiale (x, y)
 */
bool Regle::testDeplacementImpalaJones(Plateau p, int x, int y, int nbCases){
	int new_x;
	int new_y;
	// Cas ou ImpalaJones est sur la ligne horizontale du haut
	if (y == 0) {
		// Cas ou il passe sur la ligne verticale de droite
		if (x + nbCases >= TAILLE_PLATEAU_X - 1) {
			nbCases -= (TAILLE_PLATEAU_X - 1 - x);
			new_x = TAILLE_PLATEAU_X - 1;
			//new_y = 1 + nbCases;
			new_y = 1;
			//return !ligneRempli(p, new_y);
			return testDeplacementImpalaJones(p, new_x, new_y, nbCases);
		}
		// Cas ou il reste sur ligne horizontale du haut
		else {
			new_x = x + nbCases;
			return !colonneRempli(p, new_x);
		}
	}
	// Cas ou ImpalaJones est sur la ligne horizontale du bas
	else if (y == TAILLE_PLATEAU_Y - 1) {
		// Cas ou il passe sur la ligne verticale de gauche
		if (x - nbCases <= 0) {
			nbCases -= x;
			new_x = 0;
			//new_y = TAILLE_PLATEAU_Y - 2 - nbCases;
			new_y = TAILLE_PLATEAU_Y - 2;
			//return !ligneRempli(p, new_y);
			return testDeplacementImpalaJones(p, new_x, new_y, nbCases);
		}
		// Cas ou il reste sur la ligne horizontale du bas
		else {
			new_x = x - nbCases;
			return !colonneRempli(p, new_x);
		}
	}
	// Cas ou ImpalaJones est sur la ligne verticale de gauche
	else if (x == 0) {
		// Cas ou il passe sur la ligne horizontale du haut
		if (y - nbCases <= 0) {
			nbCases -= y;
			new_y = 0;
			//new_x = 1 + nbCases;
			new_x = 1;
			//return !colonneRempli(p, new_x);
			return testDeplacementImpalaJones(p, new_x, new_y, nbCases);
		}
		// Cas ou il reste sur la ligne verticale de gauche
		else {
			new_y = y - nbCases;
			return !ligneRempli(p, new_y);
		}
	}
	// Cas ou ImpalaJones est sur la ligne verticale de droite
	else if (x == TAILLE_PLATEAU_X - 1) {
		// Cas ou il passe sur la ligne horizontale du bas
		if (y + nbCases >= TAILLE_PLATEAU_Y - 1) {
			nbCases -= (TAILLE_PLATEAU_Y - 1 - y);
			new_y = TAILLE_PLATEAU_Y - 1;
			//new_x = TAILLE_PLATEAU_X - 2 - nbCases;
			new_x = TAILLE_PLATEAU_X - 2;
			//return !colonneRempli(p, new_x);
			return testDeplacementImpalaJones(p, new_x, new_y, nbCases);
		}
		// Cas ou il reste sur la ligne verticale de droite
		else {
			new_y = y + nbCases;
			return !ligneRempli(p, new_y);
		}
	}
	return true;
}

/**
 * Permet de savoir quelles sont les possibilit�s pour le joueur de d�placer Impala Jones :
 * 		-> Si le joueur peut le d�placer sur 1 des 3 prochaines cases (les 3 prochaines cases sont dispo) : renvoie -1
 * 		-> Si le joueur peut le d�placer sur la case suivante (+1) et celle d'apr�s (+2) mais pas la +3 : renvoie -2
 * 		-> Si le joueur peut le d�placer sur la case suivante (+1) et 2 cases plus loin (+3) mais pas la +2 : renvoie -3
 * 		-> Si le joueur peut le d�placer sur la 2�me case plus loin (+2) et celle encore d'apres (+3) mais pas la +1 : renvoie -4
 * 		-> Si le joueur peut le d�placer uniquement sur la prochaine case (+1) : renvoie -5
 * 		-> Si le joueur peut le d�placer uniquement sur la 2�me case (+2) : renvoie -6
 * 		-> Si le joueur peut le d�placer uniquement sur la 3�me case (+3) : renvoie -7
 * 		-> Sinon, renvoie le nombre de case plus loin o� il doit jouer (entier >=1)
 */
int Regle::possibiliteDeplacementImpalaJones(Plateau p, ImpalaJones ij){
	int x = ij.getX();
	int y = ij.getY();
	/* Test de la case suivante (+1) */
	bool caseSuivante1 = testDeplacementImpalaJones(p, x, y, 1);

	/* Test de la case +2 */
	bool caseSuivante2 = testDeplacementImpalaJones(p, x, y, 2);

	/* Test de la case +3 */
	bool caseSuivante3 = testDeplacementImpalaJones(p, x, y, 3);

	/* Interpretation */

	/* Impala Jones peut etre plac� sur l'une des 3 cases suivantes (case +1 et +2 et +3) */
	if (caseSuivante1 && caseSuivante2 && caseSuivante3) {
		return -1;
	}
	/* Impala Jones peut etre plac� soit sur la prochaine case, soit sur la suivante (case +1 et +2) */
	else if (caseSuivante1 && caseSuivante2 && !caseSuivante3) {
		return -2;
	}
	/* Impala Jones peut etre plac� soit sur la prochaine case, soit sur la 3�me (case +1 et +3) */
	else if (caseSuivante1 && !caseSuivante2 && caseSuivante3) {
		return -3;
	}
	/* Impala Jones peut etre plac� soit sur la 2�me case, soit sur la 3�me (case +2 et +3) */
	else if (!caseSuivante1 && caseSuivante2 && caseSuivante3) {
		return -4;
	}
	/* Impala Jones peut etre plac� que sur la prochaine case (case +1) */
	else if (caseSuivante1 && !caseSuivante2 && !caseSuivante3) {
		return -5;
	}
	/* Impala Jones peut etre plac� soit sur la 2�me case suivante (case +2) */
	else if (!caseSuivante1 && caseSuivante2 && !caseSuivante3) {
		return -6;
	}
	/* Impala Jones peut etre plac� soit sur la 3�me case (case +3) */
	else if (!caseSuivante1 && !caseSuivante2 && caseSuivante3) {
		return -7;
	}
	/* Impala Jones ne peut pas etre plac� sur l'une des 3 cases suivantes -> recherche de la premi�re prochaine case libre */
	int i;
	for (i = 4; i < 19; i++) {
		if (testDeplacementImpalaJones(p, x, y, i)) {
			return i;
		}
	}
	/* Si on sort de la boucle, cela veut dire qu'aucune case ne peut etre jou�e -> fin de la partie */
	return 0;
}

/* calcule les points d'un joueur,
 * renvoie 0 si un secteur n'est pas rempli
 */
int Regle::calculPointsJoueur(Plateau p, Joueur * j){
	int result = 0;
	for (int i = SECT1; i <= SECT6; i++) {
		if (!p.secteurRempli(i)) {
			return 0;
		}
		if (j->getId() == joueurMajoriteDansSecteur(p, i)) {
			result += valeurSecteur(p,i);

		}
	}
	return result;
}

/**
 * renvoie le joueur qui a la majorit� dans un secteur
 * retourne NULL si une case n'a pas de pion
 */
int Regle::joueurMajoriteDansSecteur(Plateau p, int secteur){
	int idJ1 = 0;
	int idJ2 = 0;
	unsigned int nbAnimalJ1 = 0;
	unsigned int nbAnimalJ2 = 0;

	for (unsigned int i = 1; i < p.getTaillePlateauX() - 1; i++) {
		for (unsigned int j = 1; j < p.getTaillePlateauY() - 1; j++) {
			if(p.getCase(i, j)->getPion() == NULL){
				return 0;
			}
			if (p.getCase(i, j)->getSecteur() == secteur) {
				Animal * animal = (Animal*) p.getCase(i, j)->getPion();

				if(idJ1 == animal->getJoueur()->getId()){
					nbAnimalJ1++;
				}else if(idJ2 == animal->getJoueur()->getId()){
					nbAnimalJ2++;
				}else{
					if (idJ1 == 0 && idJ2 == 0) {
						idJ1 = animal->getJoueur()->getId();
						nbAnimalJ1++;
					}else if(idJ2 == 0){
						idJ2 = animal->getJoueur()->getId();
						nbAnimalJ2++;
					}
				}
			}
		}
	}
	if (nbAnimalJ2 > nbAnimalJ1) {
		return idJ2;
	} else {
		return idJ1;
	}
}

/*
 * Renvoie la valeur de tous les pions pr�sents dans un secteur rempli
 *
 * ATTENTION, n'appeller cette methode que lorsque le plateau est rempli
 * return 0 si une des cases n'est pas remplie
 */
int Regle::valeurSecteur(Plateau p, int secteur){
	int result = 0;
	for (int i = 1; i < TAILLE_PLATEAU_Y - 1; i++) {
		for (int j = 1; j < TAILLE_PLATEAU_X - 1; j++) {
			if (p.getCase(i, j)->getSecteur() == secteur) {
				if (p.getCase(i, j)->getPion() == NULL) {
					return 0;
				} else {
					Peureux *peureux = dynamic_cast<Peureux*>(p.getCase(i, j)->getPion());
					if(peureux != NULL && !peureux->isCache()){
						result += peureux->getValeur();
					}
				}
			}
		}
	}
	return result;
}
