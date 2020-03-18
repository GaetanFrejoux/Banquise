#ifndef INITIALISATION_H_INCLUDED
#define INITIALISATION_H_INCLUDED

//INCLUDES

#include "struct.h"

//PROTOTYPES

//Fonction qui initialise le nombre de joueurs
int init_nombre_joueur();//gaetan


 // Demande la taille du plateau de jeu
int init_taille();//gaetan

// Cr�er la matrice de la banquise et la banquise initiale.
T_case **init_banquise(int taille); // gaetan et florian

 // Cr�er la matrice de m�morisation de l'�tat de la banquise au tour pr�c�dent afin d'appliquer la fonde sur ce sh�ma et non le nouveau
int **init_etat_banquise(int taille);//florian

//Creer des positions de depart et d'arriver
void init_depart_arriver(T_case **map, int taille, T_position *ptr_case_depart, T_position *ptr_case_arrive); //gaetan

//Creer un tableau de joueur avec 4 maximum
T_joueur *init_joueur(int nb_joueur); //gaetan

// Créer les différents objets sur la carte
void initialisationDesObjets(T_case **banquise, int tailleBanquise, int **etatBanquise); //florian et gaetan
void apparitionObjet(T_case **banquise, int tailleBanquise, int **etatBanquise, int numeroObjet, int pourcentage); //florian et gaetan

// On utilise etatBanquise pour indiquer les cases occupées par un objet. A la fin de la création des objets, on devra remettre etatBanquise normalement.
void apparitionMarteau(T_case **banquise, int tailleBanquise, int **etatBanquise); //florian et gaetan

//creer les marteau
void creationMarteau(T_case **banquise, int **etatBanquise, int i, int j);//florian

//initialise la position des joueur
void init_position_joueur(T_case **map,T_joueur *tableau_joueur,int taille_map,int nb_joueur,T_position *position_depart);//gaetan


#endif // INITIALISATION_H_INCLUDED
