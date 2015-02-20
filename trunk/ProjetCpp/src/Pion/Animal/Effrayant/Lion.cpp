/*
 * Lion.cpp
 *
 *  Created on: 20 janv. 2015
 *      Author: Julien
 */

#include "Lion.h"

#include "../../../Pion.h"
#include "../../../Plateau/Case.h"
#include "../../../Plateau/Plateau.h"
#include "../Peureux/Gazelle.h"
#include "../Peureux/Zebre.h"

/**
 * Action provoqu� lorsque un lion est pos� sur le plateau :
 *  - si un zebre est pr�sent sur une case voisine, il se cache
 *  - si une gazelle est pr�sente sur une case voisine, elle fuit
 */
void Lion::action(Plateau *p, Affichage *affichage){

	// Gazelle
	if(getX()<p->getTaillePlateauX()-1 && dynamic_cast<Gazelle*>(p->getCase(getX()+1, getY())->getPion())!=NULL){
		Gazelle* g = dynamic_cast<Gazelle*>(p->getCase(getX()+1, getY())->getPion());
		g->fuite(p);
	}
	if(getX()>0 && dynamic_cast<Gazelle*>(p->getCase(getX()-1, getY())->getPion())!=NULL){
		Gazelle* g = dynamic_cast<Gazelle*>(p->getCase(getX()-1, getY())->getPion());
		g->fuite(p);
	}
	if(getY()<p->getTaillePlateauY()-1 && dynamic_cast<Gazelle*>(p->getCase(getX(), getY()+1)->getPion())!=NULL){
		Gazelle* g = dynamic_cast<Gazelle*>(p->getCase(getX(), getY()+1)->getPion());
		g->fuite(p);
	}
	if(getY()>0 && dynamic_cast<Gazelle*>(p->getCase(getX(), getY()-1)->getPion())!=NULL){
		Gazelle* g = dynamic_cast<Gazelle*>(p->getCase(getX(), getY()-1)->getPion());
		g->fuite(p);
	}

	// Zebre
	if(getX()<p->getTaillePlateauX()-1 && dynamic_cast<Zebre*>(p->getCase(getX()+1, getY())->getPion())!=NULL){
		Zebre* z = dynamic_cast<Zebre*>(p->getCase(getX()+1, getY())->getPion());
		z->seCache();
	}
	if(getX()>0 && dynamic_cast<Zebre*>(p->getCase(getX()-1, getY())->getPion())!=NULL){
		Zebre* z = dynamic_cast<Zebre*>(p->getCase(getX()-1, getY())->getPion());
		z->seCache();
	}
	if(getY()<p->getTaillePlateauY()-1 && dynamic_cast<Zebre*>(p->getCase(getX(), getY()+1)->getPion())!=NULL){
		Zebre* z = dynamic_cast<Zebre*>(p->getCase(getX(), getY()+1)->getPion());
		z->seCache();
	}
	if(getY()>0 && dynamic_cast<Zebre*>(p->getCase(getX(), getY()-1)->getPion())!=NULL){
		Zebre* z = dynamic_cast<Zebre*>(p->getCase(getX(), getY()-1)->getPion());
		z->seCache();
	}
}
