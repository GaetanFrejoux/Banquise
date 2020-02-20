//INCLUDES

#include "banquise.h"
#include "initialisation.h"

//VARIABLES
T_position case_depart, case_arrive;
T_position *ptr_case_depart = &case_depart , *ptr_case_arrive = &case_arrive;
int nbGlacons=0;
int main()
{
    //INITIALISATION
    int taille_banquise = init_taille();
    int nombre_joueur = init_nombre_joueur();
    T_case **banquise = init_banquise(taille_banquise);
    int **etatBanquise = init_etat_banquise(taille_banquise);
    T_joueur *tableau_joueur = init_joueur(nombre_joueur);
    init_depart_arriver(banquise, taille_banquise, ptr_case_depart, ptr_case_arrive);
    init_position_joueur(banquise,tableau_joueur,taille_banquise,nombre_joueur,ptr_case_depart);
    nbGlacons=apparition_glacons(banquise, taille_banquise);
    //CODE
    fonteDesGlaces(banquise,etatBanquise,taille_banquise);
    affichageBanquise(banquise,taille_banquise);
    //TESTS
    printf("\n\nLe nombre de glacons present sur la carte est de %d\n",nbGlacons);
    return 0;
}
