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
    //CODE
    init_depart_arriver(banquise, taille_banquise, ptr_case_depart, ptr_case_arrive);
    init_position_joueur(banquise,tableau_joueur,taille_banquise,nombre_joueur,ptr_case_depart);
    apparition_glacons(banquise, taille_banquise);
    nbGlacons = totalDeGlacon(banquise, taille_banquise);
    for(int i=0;i<taille_banquise;i++)
    {
      for(int j=0;j<taille_banquise;j++)
      {
        if(banquise[i][j].typeObjet!=(NULL))
        {
            afficheCase(banquise[i][j].typeObjet);
        }
      }
    }
    printf("Le nombre de glacons present sur la carte est de %d\n",nbGlacons);
    affichageBanquise(banquise,taille_banquise);

    for(int i=0;i<taille_banquise;i++)
    {
      for(int j=0;j<taille_banquise;j++)
      {
        if(banquise[i][j].typeObjet!=(NULL))
        {
            printf("\n\n%d",banquise[i][j].typeObjet->position.x);
        }
      }
    }
    return 0;
}
