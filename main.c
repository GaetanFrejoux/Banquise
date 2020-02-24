//INCLUDES

#include "banquise.h"
#include "initialisation.h"

//VARIABLES
T_position case_depart, case_arrive;
T_position *ptr_case_depart = &case_depart , *ptr_case_arrive = &case_arrive;
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
    while(winner(banquise,ptr_case_arrive)==0)
    {
        fonteDesGlaces(banquise,etatBanquise,taille_banquise);
        affichageBanquise(banquise,taille_banquise);
        tour_joueur(banquise,tableau_joueur);
    }
    return 0;
}
