#ifndef INITIALISATION_H_INCLUDED
#define INITIALISATION_H_INCLUDED

//INCLUDES

#include "struct.h"

int init_nombre_joueur();
int init_taille(); // Demande la taille du plateau de jeu
T_case **init_banquise(int taille); // Cr�er la matrice de la banquise et la banquise initiale.
int **init_etat_banquise(int taille); // Cr�er la matrice de m�morisation de l'�tat de la banquise au tour pr�c�dent afin d'appliquer la fonde sur ce sh�ma et non le nouveau
void init_depart_arriver(T_case **map,int taille,T_position *ptr_case_depart, T_position *ptr_case_arrive); //Creer des positions de depart et d'arriver
T_joueur *init_joueur(int nb_joueur); //Creer un tableau de joueur avec 4 maximum


#endif // INITIALISATION_H_INCLUDED
