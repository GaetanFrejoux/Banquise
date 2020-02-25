//INCLUDES

#include "banquise.h"
#include "initialisation.h"
#include "recurrence.h"

//VARIABLES
T_position case_depart, case_arrive;
T_position *ptr_case_depart = &case_depart , *ptr_case_arrive = &case_arrive;
int tour=0;
int *indice_joueur= &tour;
int main()
{
    //INITIALISATION
    int taille_banquise = init_taille();
    int nombre_joueur = init_nombre_joueur();
    T_case **banquise = init_banquise(taille_banquise);
    int **etatBanquise = init_etat_banquise(taille_banquise);
    T_joueur *tableau_joueur = init_joueur(nombre_joueur);
    affichageBanquise(banquise, taille_banquise);
    int nbGlacons=0;
    init_depart_arriver(banquise, taille_banquise, ptr_case_depart, ptr_case_arrive);
    init_position_joueur(banquise,tableau_joueur,taille_banquise,nombre_joueur,ptr_case_depart);
    apparition_objets(banquise, taille_banquise);
    //CODE
    nbGlacons = totalDeGlacon(banquise, taille_banquise);
    int **passage=init_passage(taille_banquise);
    while(winner(banquise,ptr_case_arrive)==0)
    {
        fonteDesGlaces(banquise,etatBanquise,taille_banquise);
        affichageBanquise(banquise,taille_banquise);
        finPossible(banquise,taille_banquise,passage,tableau_joueur[0].position.x,tableau_joueur[0].position.y);
        tour_joueur(banquise,tableau_joueur,indice_joueur,nombre_joueur);
    }
    return 0;
}
