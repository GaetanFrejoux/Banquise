#ifndef RECURRENCE_H_INCLUDED
#define RECURRENCE_H_INCLUDED

//INCLUDES

#include "struct.h"
#include "banquise.h"
#include "initialisation.h"

//PROTOTYPES

//fonction permettant de savoir si nous sommes deja passé par une case pour les fonctions recursive
int **init_passage(int tailleBanquise);//florian

//fonction qui remet a 0 toutes les case.
void remiseAZeroPassage(int **passage, int tailleBanquise);//florian

//fonction qui permet de tester si une fin est possible
void finPossible(T_case **banquise, int tailleBanquise, int i, int j);//florian

//fonction qui permet de savoir s'il est possible de se deplacer dans cette case
int aijeLeDroit(int **passage, T_case **banquise, int i, int j);//florian

//fonction auxiliaire de fin possible
int finPossibleAuxiliaire(int **passage, T_case **banquise, int i, int j, int tailleBanquise);//florian

//fonction auxiliaire de finPossibleEau
int finPossibleEauAuxiliaire(int **passageEau, T_case **banquise, int i, int j, int tailleBanquise);//florian

//fonction qui initialise une matrice pour savoir si il existe un passageEau
int **initPassageEau(T_case **banquise, int tailleBanquise);//florian

//fonction qui creer un nouveau passage
void nouveauPassage(int **passageEau, int **sauvegardePassage, int tailleBanquise);//florian

//fonction qui permet de savoir s'il est possible d'agrandir la surface
void peutOnAgrandir(int **sauvegardePassage, int i, int j, int tailleBanquise);//florian

//fonction qui agrandit la surface
void augmentationSurfaceUtilise(int **passageEau, int **sauvegardePassage, int tailleBanquise);//florian

//fonction qui test si il existe une fin possible avec de l'eau
int finPossibleEau(T_case **banquise, int tailleBanquise, int i, int j);//florian

//fonction general qui effectue le test d'une fin possible ?
void peutOnFinir(T_case **banquise, int tailleBanquise, T_joueur *tableau_joueur, int numeroJoueur);//florian

#endif // RECURRENCE_H_INCLUDED
