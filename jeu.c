//INCLUDES

#include "jeu.h"

//FONCTIONS
//fonction qui gere les deplace automatique (vecteur)
void deplacementAutomatique(T_case **banquise, int tailleBanquise, T_joueur *tableau_joueur, int nombre_joueur) // Permet de d�placer les gla�ons ou les marteaux en mouvement � la fin d'un tour
{
    int i, j;
    for(j=0; j<tailleBanquise; j++)  // On parcours la banquise � la recherche de gla�ons
    {
        for(i=0; i<tailleBanquise; i++)
        {
            if(banquise[i][j].typeObjet!=NULL)
            {
                if(banquise[i][j].typeObjet->objet==0)  // Quand on trouve des gla�ons, on les fait se d�placer en fonction de leur vecteur
                {
                    deplacementGlacon(banquise, i, j, banquise[i][j].typeObjet->vecteur.dx, banquise[i][j].typeObjet->vecteur.dy, tailleBanquise, tableau_joueur, nombre_joueur);
                }
                if(banquise[i][j].typeObjet->objet==3)  // Quand on trouve des t�tes de marteau, on les fait se d�placer en fonction de leur vecteur et du nombre de d�placement restant � leur axe
                {
                    deplacementMarteau(banquise, i, j, banquise[i][j].typeObjet->vecteur.dx, banquise[i][j].typeObjet->vecteur.dy, tailleBanquise, banquise[banquise[i][j].typeObjet->position.x][banquise[i][j].typeObjet->position.y].typeObjet->nbTourMarteau, tableau_joueur, nombre_joueur);
                }

            }
        }
    }
}



// Lance le jeu
void jeu() 
{

  //VARIABLES
  T_position case_depart, case_arrive;
  T_position *ptr_case_depart = &case_depart , *ptr_case_arrive = &case_arrive;
  int tour=0;
  int *indice_joueur= &tour;
  int fin = 0;

  //INITIALISATION
  int taille_banquise = init_taille(); //initialisation de la taille
  int nombre_joueur = init_nombre_joueur(); //initialisation du nombre de joueur
  T_case **banquise = init_banquise(taille_banquise);
  int **etatBanquise = init_etat_banquise(taille_banquise);
  T_joueur *tableau_joueur = init_joueur(nombre_joueur);
  int nbGlacons=0;
  init_depart_arriver(banquise, taille_banquise, ptr_case_depart, ptr_case_arrive);
  init_position_joueur(banquise,tableau_joueur,taille_banquise,nombre_joueur,ptr_case_depart);
  initialisationDesObjets(banquise,taille_banquise,etatBanquise);
  //CODE
  nbGlacons = totalDeGlacon(banquise, taille_banquise);
  int **passage=init_passage(taille_banquise);
  while(winner(banquise,ptr_case_arrive)==0 && fin == 0)
  {
      affichageBanquise(banquise,taille_banquise);
      peutOnFinir(banquise, taille_banquise, tableau_joueur, *indice_joueur);
      deplacementJoueur(banquise,tableau_joueur,indice_joueur,nombre_joueur,taille_banquise);
      fonteDesGlaces(banquise,tableau_joueur,etatBanquise,taille_banquise);
      fin = qui_est_mort(banquise,tableau_joueur,nombre_joueur);
      joueur_suivant(banquise,tableau_joueur,indice_joueur,nombre_joueur);
      printf("\n\nOK\n\n");
      /*deplacementAutomatique(banquise, taille_banquise, tableau_joueur, nombre_joueur);*/
      // On a mis cette dernière fonction en commentaire car sinon notre fonction bug. Il doit y avoir des bug mais on ne sais pas où

  }

  printf("Fin de partie");
}
