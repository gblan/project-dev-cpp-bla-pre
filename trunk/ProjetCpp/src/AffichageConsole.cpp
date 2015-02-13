/*
 * AffichageConsole.cpp
 *
 *  Created on: 6 f�vr. 2015
 *      Author: Julien
 */

#include "AffichageConsole.h"

#include <iostream>
#include <string>

#include "Joueur.h"
#include "Plateau/Case.h"
#include "Plateau/Plateau.h"

int AffichageConsole::menuDemarrage() {
	cout << "======================================" << endl;
	cout << "Bienvenue dans le jeu Drole de Zebres!" << endl;
	cout << "   1 - Jouer (Joueur vs Ordi)" << endl;
	cout << "   2 - Jouer (Joueur vs Joueur)" << endl;
	cout << "   3 - Regles" << endl;
	cout << "   4 - Charger une partie" << endl;
	cout << "   5 - Quitter" << endl;
	cout << "======================================" << endl;
	int res;
	cin >> res;
	while (!(res >= 1 && res <= 5)) {
		cout << "Erreur ! Veuillez entrer un chiffre compris entre 1 et 5"
				<< endl;
		cout << "======================================" << endl;
		cout << "Bienvenue dans le jeu Drole de Zebres!" << endl;
		cout << "   1 - Jouer (Joueur vs Ordi)" << endl;
		cout << "   2 - Jouer (Joueur vs Joueur)" << endl;
		cout << "   3 - Regles" << endl;
		cout << "   4 - Charger une partie" << endl;
		cout << "   5 - Quitter" << endl;
		cout << "======================================" << endl;
		cin >> res;
	}
	return res;
}

int AffichageConsole::afficheRegle() {

	/** Faire un affichage des regles qui sont dans un texte **/

	int res;
	cout << "======================================" << endl;
	cout << "Entrez 1 pour retourner au menu" << endl;
	cin >> res;
	while (res != 1) {
		cout << "======================================" << endl;
		cout << "Erreur ! Veuillez entrer 1 pour retourner au menu" << endl;
		cin >> res;
	}
	return res;
}

void AffichageConsole::demandeNomJoueur(Joueur *j, int numJoueur) {
	cout << "======================================" << endl;
	cout << "Veuillez entrer le nom du joueur n�" << numJoueur << " : " << endl;
	cout << "======================================" << endl;
	string nom;
	cin >> nom;
	/** Verifier si le nom est correct? Comment? **/
	j->setNom(nom);
}

void AffichageConsole::affichePlateau(Plateau p) {
	/*string s = ""; */
	for (int i = 0; i < p.getTaillePlateauY(); i++) {
		for (int j = 0; j < p.getTaillePlateauX(); j++) {

			/* Affichage des cases d'IMPALA JONES*/
			if (i == 0 || i == 6 || j == 0 || j == 7) {
				//CASES NON ACCESSIBLES
				if ((i == 0 && j == 0) || (i == 6 && j == 0)) {
					//en haut � gauche ou en bas a gauche
					cout << "  X  |";
				} else if ((i == 0 && j == 7) || (i == 6 && j == 7)) {
					//en haut � droite ou en bas � droite
					cout << "  X  ";
				} else {
					// CASES ACCESSIBLES
					if (p.getCase(j, i).getPion() != NULL) {
						if (j == 7) {
							cout << "  I ";
						} else {
							cout << "  I  |";
						}
					} else {
						if (j == 7) {
							cout << "     ";
						} else {
							cout << "     |";
						}
					}
				}
			} else {
				/* Affichage des zones du jeu et des PIONS */
				if (p.getCase(j, i).getPion() != NULL) {
					cout << " " <<p.getCase(j, i).getPion() << " ";
				} else {
					cout << "   ";
				}

				if (p.getCase(j, i).getSecteur() != p.getCase(j+1, i).getSecteur()) {
					cout << "  |";
				} else {
					cout << "   ";
				}
			}
		}
		cout << "\n";
		if (i < p.getTaillePlateauY() - 1) {
			for (int k = 0; k < p.getTaillePlateauX(); k++) {
				if (k == 0 || k == p.getTaillePlateauX() - 1
						|| p.getCase(k, i).getSecteur()
								!= p.getCase(k, i+1).getSecteur()) {
					cout << " ___  ";
				} else {
					cout << "      ";
				}
			}
		}
		cout << "\n";

	}
	/*cout << s << endl;*/
}

int AffichageConsole::demandeDeplacerImpalaJones(){
	cout << "D�placement d'Impala Jones : veuillez choisir un nombre compris entre 1 et 3" << endl;
	int res;
	cin >> res;
	while(!(res>=1 && res<=3)){
		cout << "Erreur! Veuillez choisir un nombre compris entre 1 et 3" << endl;
		cin >> res;
	}
	return res;
}

void AffichageConsole::afficheListAnimal(vector<Animal*> listAnimaux){
	int nbPion = listAnimaux.size();
	int i;
	cout << "(";
	for(i=0; i<nbPion; i++){
		cout << listAnimaux[i]->print() << "[n�" << i << "]";
		if(i == nbPion-1){
			cout << ")" << endl;
		}
		else{
			cout << " - ";
		}
	}
}


int AffichageConsole::selectionnerAnimal(vector<Animal*> listAnimaux){
	int nbPion = listAnimaux.size();
	cout << "Voici votre liste de pion : " << endl;
	cout << "---> ";
	afficheListAnimal(listAnimaux);
	cout << "S�lectionner l'animal que vous souhaitez poser sur le plateau selon sa position dans votre liste de pion" << endl;
	int positionAnimal;
	cin >> positionAnimal;
	while(!(positionAnimal>=0 && positionAnimal<=(nbPion-1))){
		cout << "Erreur ! Veuillez entrer un nombre compris entre 0 et " << (nbPion-1) << endl;
		cout << "Voici votre liste de pion : " << endl;
		cout << "---> ";
		afficheListAnimal(listAnimaux);
		cout << "S�lectionner l'animal que vous souhaitez poser sur le plateau selon sa position dans votre liste de pion" << endl;
		cin >> positionAnimal;
	}

	return positionAnimal;
}

int AffichageConsole::selectionnerPosition(int *x, int *y, Plateau p){
	cout << "Selectionnez une case (entrez x et y) " << endl;
	int i, j;
	cin >> i >> j;
	if(!(i>=0 && i<=p.getTaillePlateauX() && j>=0 && j<=p.getTaillePlateauY())){
		cout << "Erreur ! x doit etre compris entre 0 et " << p.getTaillePlateauX() << " et y doit etre compris entre 0 et " << p.getTaillePlateauY() << endl;
		return -1;
	}
	if(p.getCase(i, j).getPion()==NULL){
		cout << "Erreur ! la case (" << i << ", " << j << ") a deja un pion" << endl;
		return -1;
	}

	/* TODO : a v�rifier */
	*x=i;
	*y=j;
	return 0;
}

void AffichageConsole::affichePion(Pion *p, Joueur *j){
	/* appel de print p et de l'id du joueur */
	cout << "(" << p->print() << ", " << j->getId() << ")" << endl;
}

void AffichageConsole::afficheImpalaJones(){
	cout << "(IJ)" << endl;
}

int AffichageConsole::menuJoueur(Joueur *j){
	/* Afficher le nom du joueur qui doit jouer + lui proposer de poser un pion, de regarder sa liste de pion, de sauvegarder
	 * 	ou de d�clarer forfait
	 */
	cout << "======================================" << endl;
	cout << "Joueur : " << j->getNom() << "(J" << j->getId() << ") :" << endl;
	cout << "Que voulez-vous faire?" << endl;
	cout << "   1 - D�placer Impala Jones" << endl;
	cout << "   2 - Afficher votre liste de pions" << endl;
	cout << "   3 - Sauvegarder la partie" << endl;
	cout << "   4 - Quitter la partie" << endl;
	int res;
	cin >> res;
	while(!(res>=1 && res<=4)){
		cout << "Erreur ! Veuillez entrer un nombre entre 1 et 4" << endl;
		cout << "Que voulez-vous faire?" << endl;
		cout << "   1 - D�placer Impala Jones" << endl;
		cout << "   2 - Afficher votre liste de pions" << endl;
		cout << "   3 - Sauvegarder la partie" << endl;
		cout << "   4 - Quitter la partie" << endl;
		cin >> res;
	}
	cout << "======================================" << endl;
	return res;
}

int AffichageConsole::demandeLigne(Plateau p, int colonne){
	cout << "Veuillez entrer la ligne ou vous souhaitez poser votre pion" << endl;
	int res;
	cin >> res;
	while(!(res>=0 && res<p.getTaillePlateauY())){
		cout << "Erreur ! Veuillez entrer un chiffre entre 0 et " << p.getTaillePlateauY() << endl;
		cin >> res;
	}
	while(p.getCase(colonne, res).getPion() != NULL){
		cout << "Erreur ! La case est occup�e" << endl;
		cin >> res;
		while(!(res>=0 && res<p.getTaillePlateauY())){
			cout << "Erreur ! Veuillez entrer un chiffre entre 0 et " << p.getTaillePlateauY() << endl;
			cin >> res;
		}
	}
	return res;
}

int AffichageConsole::demandeColonne(Plateau p, int ligne){
	cout << "Veuillez entrer la colonne ou vous souhaitez poser votre pion" << endl;
	int res;
	cin >> res;
	while(!(res>=0 && res<p.getTaillePlateauX())){
		cout << "Erreur ! Veuillez entrer un chiffre entre 0 et " << p.getTaillePlateauX() << endl;
		cin >> res;
	}
	while(p.getCase(res, ligne).getPion() != NULL){
		cout << "Erreur ! La case est occup�e" << endl;
		cin >> res;
		while(!(res>=0 && res<p.getTaillePlateauX())){
			cout << "Erreur ! Veuillez entrer un chiffre entre 0 et " << p.getTaillePlateauX() << endl;
			cin >> res;
		}
	}
	return res;
}
