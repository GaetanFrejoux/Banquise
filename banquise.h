#ifndef BANQUISE_H_INCLUDED
#define BANQUISE_H_INCLUDED

//INCLUDES

#include "struct.h"

//PROTOTYPES


void color(int t,int f);//gaetan

// Affiche la banquise
void affichageBanquise(T_case **banquise, int taille); //gaetan

// Affiche la matrice de l'�tat de la banquise FONCTION OK
void affichageEtatBanquise(int **etatBanquise, int taille); //florian

//Dis si la case est de la glace (1) ou de l'eau (0)  FONCTION OK
int estDeLaGlace(int **etatBanquise, int i, int j); //florian

// Dis si la case actuelle a le droit de fondre (1) ou non (0)  FONCTION OK
int banquisePeutFondre(int **etatBanquise, int i, int j, int taille); //florian

// Fonction permettant de copier l'�tat de la banquise et de la sauvegard�e dans la matrice etatBanquise FONCTION OK
void majBanquise(T_case **banquise, int **etatBanquise, int taille); //florian

// Fonction permettant d'appliquer la fonte des glaces du terrain FONCTION OK
void fonteDesGlaces(T_case **banquise,T_joueur *tableau_joueur, int **etatBanquise, int taille); //florian

//Fonction permettant d'appliquer la fonte aux gla�ons
void glaconFond(T_case **banquise, int taille); //florian

// Compte le nombre total de glaçons présents sur la banquise
int totalDeGlacon(T_case **banquise, int taille); //florian

// Test si il y a un gagnant
int winner(T_case** banquise,T_position *ptr_case_arrive); //gaetan
/*void afficheCase( T_objet* unecase);*/

//fonction qui renvoie le cas ou est le glacon
int numeroCasGlacon(T_case **banquise, int i, int j, int directionX, int directionY, int tailleBanquise);//florian

//fonction qui applique le vecteur au glacon
void vecteurGlacon(T_case **banquise, int i, int j, int directionX, int directionY, int tailleBanquise, int *ptrPiege, T_joueur *tableau_joueur, int nombre_joueur);//florian

//fonction qui deplace le glacon
void deplacementGlacon(T_case **banquise, int i, int j, int directionX, int directionY, int tailleBanquise, T_joueur *tableau_joueur, int nombre_joueur);//florian

//fonction qui transforme le glacon
void transformationGlacon(T_case **banquise, int i, int j); //Fonction qui fait que si les glaçons sont sur de l'eau, ils deviennent de la banquise

#endif // BANQUISE_H_INCLUDED
