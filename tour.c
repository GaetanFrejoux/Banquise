//INCLUDES

#include "tour.h"

//FONCTIONS
int joueur_vivant(T_case **banquise,T_joueur *tableau_joueur,int* indice_joueur, int nombre_joueur,int* nombre_morts)
{
  int compteur = 0;
  if(banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].etat==0)
  {
    tableau_joueur[*indice_joueur].etat=0;
    *nombre_morts++;
  }
  if(*nombre_morts==nombre_joueur)
  {
      return 1;
  }
  else
  {
    while (tableau_joueur[*indice_joueur].etat!=1 && compteur <nombre_joueur-1)
    {
        *indice_joueur = (*indice_joueur+1)%nombre_joueur;
        compteur++;
    }
    return 0;
  }

}
T_case case_adjacente(T_case **banquise,T_joueur *tableau_joueur,int* indice_joueur,int tailleBanquise,int x,int y)
{
    int pos_x,pos_y;
    pos_x=tableau_joueur[*indice_joueur].position.x+x;
    pos_y=tableau_joueur[*indice_joueur].position.y+y;
    if(pos_x>=tailleBanquise || pos_x<0 || pos_y>=tailleBanquise || pos_y<0 )
        return banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y];
    else
        return banquise[pos_x][pos_y];
}
void tour_joueur(T_case **banquise,T_joueur *tableau_joueur,int* indice_joueur, int nombre_joueur, int tailleBanquise) //Il faudra faire attention à ne pas pouvoir se déplacer hors du plateau de jeu
{
    T_case nouvelle_case;
    int choix=-1;
    char mouvement;
    while(mouvement!='z'&& mouvement!='q'&& mouvement!='s'&& mouvement!='d')
    {
    printf("\n(z = Haut / q = Gauche / s = Bas / d = Droite) :");
    scanf("%c",&mouvement);
    }

    if(mouvement=='z')
    {
        nouvelle_case = case_adjacente(banquise,tableau_joueur,indice_joueur,tailleBanquise,0,-1);
        choix=0;
    }
    else if(mouvement=='q')
    {
        nouvelle_case = case_adjacente(banquise,tableau_joueur,indice_joueur,tailleBanquise,-1,0);
        choix=1;
    }
    else if(mouvement=='s')
    {
        nouvelle_case = case_adjacente(banquise,tableau_joueur,indice_joueur,tailleBanquise,0,1);
        choix=2;
    }
    else
    {
        nouvelle_case = case_adjacente(banquise,tableau_joueur,indice_joueur,tailleBanquise,1,0);
       choix=3;
    }
      switch(choix)
      {
          case 0 :


              /*if(haut.etat==0) // Si un joueur va dans l'eau, il meurt
              {
                mortJoueur
              }*/

              if(nouvelle_case.occupe!=NULL)
              {
                printf("\n\nIl y a un joueur a cette case\n\n");
              }

              if((nouvelle_case.typeObjet==NULL && nouvelle_case.occupe==NULL && nouvelle_case.etat==1)/*||(nouvelle_case.typeObjet!=NULL && nouvelle_case.typeObjet->objet==0)*/) // On a pas besoin de mettre (haut.occupe==NULL && haut.etat==1) si on change en else if car les condition sont vérifiées avant
              {
                  tableau_joueur[*indice_joueur].position.y-=1;
                  banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                  banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe;
                  banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe=NULL;/*
                  if(nouvelle_case.typeObjet!=NULL)
                  {
                   banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].typeObjet=(T_objet*)malloc(sizeof(T_objet));
                   banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].typeObjet=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].typeObjet;
                   banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].typeObjet=NULL;
                 }*/
              }

              if(nouvelle_case.typeObjet!=NULL)
              {
                if((nouvelle_case.typeObjet==1) || (nouvelle_case.typeObjet==2) || (nouvelle_case.typeObjet==3) || (nouvelle_case.typeObjet==5)) //Si la case d'après fait parti du marteau, est un rocher ou un ressort, la joueur ne peut s'y déplacer
                {
                  printf("\n\nUn objet bloque le passage\n\n");
                }
                else if(nouvelle_case.typeObjet==4)//Il faudra creer quelque chose pour le ressort
                {

                }
                else if(nouvelle_case.typeObjet==0)
                {
                  int actionGlacon = glaconPeutSeDeplacer(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y-1, 0, -1, tailleBanquise);
                  if(actionGlacon==0)
                  {
                    printf("\n\nUn glacon bloque le passage et ne peut etre deplace dans ce sens\n\n");
                  }
                  else if(actionGlacon==1)
                  {
                    //Parti déplacement du glaçon
                    deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y-1, 0, -1, tailleBanquise);

                    tableau_joueur[*indice_joueur].position.y-=1; //Partie déplacement joueur
                    banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                    banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe;
                    banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe=NULL;
                  }
                  else if(actionGlacon==4)
                  {
                    deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y-1, 0, 1, tailleBanquise);
                  }
                }
              }

              break;

          case 1 :
              if(nouvelle_case.typeObjet==NULL && nouvelle_case.occupe==NULL)
              {
                  tableau_joueur[*indice_joueur].position.x-=1;
                  banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                  banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe;
                  banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
              }
              break;
          case 2 :
              if(nouvelle_case.typeObjet==NULL && nouvelle_case.occupe==NULL)
              {
                  tableau_joueur[*indice_joueur].position.y+=1;
                  banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                  banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe;
                  banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe=NULL;
              }
              break;
          case 3 :
              if(nouvelle_case.typeObjet==NULL && nouvelle_case.occupe==NULL)
              {
                  tableau_joueur[*indice_joueur].position.x+=1;
                  banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                  banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y].occupe;
                  banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
              }
              break;
      }
    *indice_joueur = (*indice_joueur+1)%nombre_joueur;
}

void qui_est_mort(T_case **banquise,T_joueur *tableau_joueur,int nombre_joueur)
{
    for(int i=0;i<nombre_joueur;i++)
    {
        if(banquise[tableau_joueur[i].position.x][tableau_joueur[i].position.y].etat==0)
        {
            tableau_joueur[i].etat=0;
        }
    }
}
