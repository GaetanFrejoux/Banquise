#ifndef TOUR_H_INCLUDED
#define TOUR_H_INCLUDED
//INCLUDES

#include "struct.h"

//PROTOTYPES
// Tue un joueur.
void mortJoueur(T_case **banquise, T_joueur *tableau_joueur, int numeroJoueur); //florian

//Regarde si un gla�on a percut� un joueur. Si c'est le cas, le tue
void glaconKiller(T_case **banquise, T_joueur *tableau_joueur, int i, int j, int nombre_joueur); //florian

 //Effectue le d�placement d'un joueur
void deplacementJoueur(T_case **banquise, T_joueur *tableau_joueur, int *indice_joueur, int nombre_joueur, int tailleBanquise);//florian et gaetan

int qui_est_mort(T_case **banquise,T_joueur *tableau_joueur,int nombre_joueur);//gaetan
void joueur_suivant(T_case **banquise,T_joueur *tableau_joueur,int* indice_joueur, int nombre_joueur);//gaetan

// Indique la position de la t�te du marteau par rapport � l'axe ( 0 : en haut, 1  � gauche, 2 : en bas, 3 : � droite)
int positionTeteMarteau(T_case **banquise, int i, int j); //florian
// On donne pour i et j la position de l'axe du marteau

// Indique si le marteau peut tourner (1) ou non (0)
int marteauPeutBouger(T_case **banquise, int i, int j, int directionX, int directionY, int tailleBanquise, int casMarteau); //florian
// On donne en i et en j la position de la t�te de marteau

// Ici, i et j sont les position de la t�te de marteau
void deplacementMarteau(T_case **banquise, int i, int j, int directionX, int directionY, int tailleBanquise, int nombreDeDeplacementRestant, T_joueur *tableau_joueur, int nombre_joueur);//florian

 //Si un objet emp�che un d�placement, renvoie 1, sinon, si l'emplacement est libre, renvoie 0
int objetEmpecheDeplacement(T_case **banquise, int i, int j);//florian


#endif // TOUR_H_INCLUDED
