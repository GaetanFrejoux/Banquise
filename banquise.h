#ifndef BANQUISE_H_INCLUDED
#define BANQUISE_H_INCLUDED

//INCLUDES

#include "struct.h"

//PROTOTYPES


void color(int t,int f);
void affichageBanquise(T_case **banquise, int taille);  // Affiche la banquise
void affichageEtatBanquise(int **etatBanquise, int taille); // Affiche la matrice de l'�tat de la banquise FONCTION OK
int estDeLaGlace(int **etatBanquise, int i, int j); //Dis si la case est de la glace (1) ou de l'eau (0)  FONCTION OK
int banquisePeutFondre(int **etatBanquise, int i, int j, int taille); // Dis si la case actuelle a le droit de fondre (1) ou non (0)  FONCTION OK
void majBanquise(T_case **banquise, int **etatBanquise, int taille); // Fonction permettant de copier l'�tat de la banquise et de la sauvegard�e dans la matrice etatBanquise FONCTION OK
void fonteDesGlaces(T_case **banquise, int **etatBanquise, int taille); // Fonction permettant d'appliquer la fonte des glaces du terrain FONCTION OK
void glaconFond(T_case **banquise, int taille); //Fonction permettant d'appliquer la fonte aux gla�ons
int totalDeGlacon(T_case **banquise, int taille); // Compte le nombre total de glaçons présents sur la banquise

#endif // BANQUISE_H_INCLUDED
