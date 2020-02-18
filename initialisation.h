#ifndef INITIALISATION_H_INCLUDED
#define INITIALISATION_H_INCLUDED

//INCLUDES

#include "struct.h"

int init_nombre_joueur();
int init_taille(); // Demande la taille du plateau de jeu
T_case **init_banquise(int taille); // Créer la matrice de la banquise et la banquise initiale.
int **init_etat_banquise(int taille); // Créer la matrice de mémorisation de l'état de la banquise au tour précédent afin d'appliquer la fonde sur ce shéma et non le nouveau
void init_depart_arriver(T_case **map,int taille);
T_joueur *init_joueur(int nb_joueur);


#endif // INITIALISATION_H_INCLUDED
