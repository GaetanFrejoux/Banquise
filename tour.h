#ifndef TOUR_H_INCLUDED
#define TOUR_H_INCLUDED
//INCLUDES

#include "struct.h"

//PROTOTYPES
T_case case_adjacente(T_case **banquise,T_joueur *tableau_joueur,int* indice_joueur,int tailleBanquise,int x,int y);
void joueur_vivant(T_case **banquise,T_joueur *tableau_joueur,int* indice_joueur, int nombre_joueur,int* nombre_morts);
void tour_joueur(T_case **banquise,T_joueur *tableau_joueur,int* indice_joueur, int nombre_joueur, int tailleBanquise);
void qui_est_mort(T_case **banquise,T_joueur *tableau_joueur,int nombre_joueur);

#endif // TOUR_H_INCLUDED
