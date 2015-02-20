/*
 * Personnage.cpp
 *
 *  Created on: 20 janv. 2015
 *      Author: Julien
 */

#include "ImpalaJones.h"

#include <iostream>

#include "../Plateau/Plateau.h"

/**
 * Cette m�thode prend en param�tre le nombre de case o� Impala Jones sera plus loin, et sa position avant le d�placement
 *  car cette m�thode peut �tre appel� recursivement
 */
int ImpalaJones::deplacer(int nbCases, Plateau *plateau, int ancien_x, int ancien_y){
	if(nbCases<0){
		cout << "Erreur ! nbCases doit etre sup�rieur � 0" << endl;
		return -1;
	}

	// Cas ou ImpalaJones est sur la ligne horizontale du haut
	if(getY()==0){
		if(getX()+nbCases>=TAILLE_PLATEAU_X-1){
			nbCases-=(TAILLE_PLATEAU_X-1-getX());
			setX(TAILLE_PLATEAU_X-1);
			//setY(1 + nbCases);
			setY(1);
			return deplacer(nbCases, plateau, ancien_x, ancien_y);
		}
		else{
			setX(getX()+nbCases);
		}
	}
	// Cas ou ImpalaJones est sur la ligne horizontale du bas
	else if(getY()==TAILLE_PLATEAU_Y-1){
		int x = getX();
		if(x-nbCases<=0){
			nbCases-=getX();
			setX(0);
			//setY(TAILLE_PLATEAU_Y-2 - nbCases);
			setY(TAILLE_PLATEAU_Y-2);
			return deplacer(nbCases, plateau, ancien_x, ancien_y);
		}
		else{
			setX(getX()-nbCases);
		}
	}
	// Cas ou ImpalaJones est sur la ligne verticale du haut
	else if(getX() == 0){
		int y = getY();
		if(y-nbCases<=0){
			nbCases-=getY();
			setY(0);
			//setX(1 + nbCases);
			setX(1);
			return deplacer(nbCases, plateau, ancien_x, ancien_y);
		}
		else{
			setY(getY()-nbCases);
		}
	}
	// Cas ou ImpalaJones est sur la ligne verticale du bas
	else if (getX() == TAILLE_PLATEAU_X-1){
		if(getY()+nbCases>=TAILLE_PLATEAU_Y-1){
			nbCases-=(TAILLE_PLATEAU_Y-1-getY());
			setY(TAILLE_PLATEAU_Y-1);
			//setX(TAILLE_PLATEAU_X-2-nbCases);
			setX(TAILLE_PLATEAU_X-2);
			return deplacer(nbCases, plateau, ancien_x, ancien_y);
		}
		else{
			setY(getY()+nbCases);
		}
	}
	else{
		cout << "Erreur! Impala Jones n'�tait pas bien positionn�" << endl;
		return -1;
	}

	/* suppression d'Impalajones de son ancienne position */
	plateau->getCase(ancien_x, ancien_y)->supprimerPion();

	/* ajout d'impalaJones a sa nouvelle position */
	plateau->getCase(getX(), getY())->ajouterPion(this);
	return 0;
}
