#ifndef TOUR_H_INCLUDED
#define TOUR_H_INCLUDED
//INCLUDES

#include "struct.h"

//PROTOTYPES

void glaconKiller(T_case **banquise, T_joueur *tableau_joueur, int i, int j, int nombre_joueur); //Regarde si un glaçon a percuté un joueur. Si c'est le cas, le tue
void deplacementJoueur(T_case **banquise, T_joueur *tableau_joueur, int *indice_joueur, int nombre_joueur, int tailleBanquise, int *ptr_nombre_morts); //Effectue le déplacement d'un joueur
int qui_est_mort(T_case **banquise,T_joueur *tableau_joueur,int nombre_joueur, int *ptr_nombre_morts);
T_case case_adjacente(T_case **banquise,T_joueur *tableau_joueur,int* indice_joueur,int tailleBanquise,int x,int y);
void joueur_vivant(T_case **banquise,T_joueur *tableau_joueur,int* indice_joueur, int nombre_joueur);

#endif // TOUR_H_INCLUDED
