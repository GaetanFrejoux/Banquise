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
    int nombre_joueur =init_nombre_joueur();
    T_case **banquise = init_banquise(taille_banquise);
    int **etatBanquise = init_etat_banquise(taille_banquise);
    affichageBanquise(banquise, taille_banquise, ptr_case_depart, ptr_case_arrive);
    init_depart_arriver(banquise,taille_banquise,ptr_case_depart,ptr_case_arrive);
    affichageEtatBanquise(etatBanquise, taille_banquise);
    //CODE

    fonteDesGlaces(banquise, etatBanquise, taille_banquise);
    affichageBanquise(banquise, taille_banquise, ptr_case_depart, ptr_case_arrive);
    fonteDesGlaces(banquise, etatBanquise, taille_banquise);
    affichageBanquise(banquise, taille_banquise, ptr_case_depart, ptr_case_arrive);
    fonteDesGlaces(banquise, etatBanquise, taille_banquise);
    affichageBanquise(banquise, taille_banquise, ptr_case_depart, ptr_case_arrive);
    fonteDesGlaces(banquise, etatBanquise, taille_banquise);
    affichageBanquise(banquise, taille_banquise, ptr_case_depart, ptr_case_arrive);
    fonteDesGlaces(banquise, etatBanquise, taille_banquise);
    affichageBanquise(banquise, taille_banquise, ptr_case_depart, ptr_case_arrive);
    fonteDesGlaces(banquise, etatBanquise, taille_banquise);
    affichageBanquise(banquise, taille_banquise, ptr_case_depart, ptr_case_arrive);
    fonteDesGlaces(banquise, etatBanquise, taille_banquise);
    affichageBanquise(banquise, taille_banquise, ptr_case_depart, ptr_case_arrive);
    fonteDesGlaces(banquise, etatBanquise, taille_banquise);
    affichageBanquise(banquise, taille_banquise, ptr_case_depart, ptr_case_arrive);

    return 0;
}
