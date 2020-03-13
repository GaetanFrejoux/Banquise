#ifndef INITIALISATION_H_INCLUDED
#define INITIALISATION_H_INCLUDED

//INCLUDES

#include "struct.h"

//PROTOTYPES
int init_nombre_joueur();
int init_taille(); // Demande la taille du plateau de jeu
T_case **init_banquise(int taille); // Cr�er la matrice de la banquise et la banquise initiale.
int **init_etat_banquise(int taille); // Cr�er la matrice de m�morisation de l'�tat de la banquise au tour pr�c�dent afin d'appliquer la fonde sur ce sh�ma et non le nouveau
void init_depart_arriver(T_case **map, int taille, T_position *ptr_case_depart, T_position *ptr_case_arrive); //Creer des positions de depart et d'arriver
T_joueur *init_joueur(int nb_joueur); //Creer un tableau de joueur avec 4 maximum
void apparition_objets(T_case **banquise, int taille); //Place des glacons de manière aléatoire sur la banquise.

void initialisationDesObjets(T_case **banquise, int tailleBanquise, int **etatBanquise); // Créer les différents objets sur la carte
void apparitionObjet(T_case **banquise, int tailleBanquise, int **etatBanquise, int numeroObjet, int pourcentage);
void apparitionMarteau(T_case **banquise, int tailleBanquise, int **etatBanquise); // On utilise etatBanquise pour indiquer les cases occupées par un objet. A la fin de la création des objets, on devra remettre etatBanquise normalement.
void creationMarteau(T_case **banquise, int **etatBanquise, int i, int j);

void init_position_joueur(T_case **map,T_joueur *tableau_joueur,int taille_map,int nb_joueur,T_position *position_depart);


#endif // INITIALISATION_H_INCLUDED
