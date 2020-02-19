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
    init_depart_arriver(banquise, taille_banquise, ptr_case_depart, ptr_case_arrive);
    init_position_joueur(banquise,tableau_joueur,taille_banquise,nombre_joueur,ptr_case_depart);
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
    printf("Le nombre de glacons present sur la carte est de %d\n",nbGlacons);
    affichageBanquise(banquise,taille_banquise);
    printf("\n%s\n",tableau_joueur[0].nom);
    printf(" x : %d\n",tableau_joueur[0].position.x);
    printf(" y : %d\n",tableau_joueur[0].position.y);

    printf("\n%s\n",banquise[ptr_case_depart->x][ptr_case_depart->y].occupe->nom);

    return 0;
}
