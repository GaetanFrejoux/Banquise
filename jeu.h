#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

//INCLUDES

#include "banquise.h"
#include "initialisation.h"
#include "recurrence.h"
#include "tour.h"

//PROTOTYPES
// Permet de d�placer les gla�ons ou les marteaux en mouvement � la fin d'un tour
void deplacementAutomatique(T_case **banquise, int tailleBanquise, T_joueur *tableau_joueur, int nombre_joueur); //florian

// Lance le jeu
void jeu(); //florian et gaetan

#endif // JEU_H_INCLUDED
