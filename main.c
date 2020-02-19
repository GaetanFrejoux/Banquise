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
    affichageBanquise(banquise, taille_banquise);
    init_depart_arriver(banquise, taille_banquise, ptr_case_depart, ptr_case_arrive);

    int nbGlacons=0;
    affichageEtatBanquise(etatBanquise, taille_banquise);
    //CODE
    apparition_glacons(banquise, taille_banquise);
    for(int i=0;i<taille_banquise;i++)
    {
      for(int j=0;j<taille_banquise;j++)
      {
        if(banquise[i][j].typeObjet!=NULL)
        {
            printf("%d\n",banquise[i][j].typeObjet->objet);
        }
      }
    }

    fonteDesGlaces(banquise, etatBanquise, taille_banquise);
    affichageBanquise(banquise, taille_banquise);
    fonteDesGlaces(banquise, etatBanquise, taille_banquise);
    affichageBanquise(banquise, taille_banquise);
    fonteDesGlaces(banquise, etatBanquise, taille_banquise);
    affichageBanquise(banquise, taille_banquise);
    fonteDesGlaces(banquise, etatBanquise, taille_banquise);
    affichageBanquise(banquise, taille_banquise);
    fonteDesGlaces(banquise, etatBanquise, taille_banquise);
    affichageBanquise(banquise, taille_banquise);
    nbGlacons = totalDeGlacon(banquise, taille_banquise);
    printf("Le nombre de glacons present sur la carte est de %d\n",nbGlacons);


    return 0;
}
