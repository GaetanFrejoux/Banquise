//INCLUDES

#include "tour.h"

//FONCTIONS
void joueur_vivant(T_case **banquise,T_joueur *tableau_joueur,int* indice_joueur, int nombre_joueur,int* nombre_morts)
{
    while (tableau_joueur[*indice_joueur].etat!=1)
    {
        *indice_joueur = (*indice_joueur+1)%nombre_joueur;
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
        /*
        Si la prochaine case est de l'eau, il faut mort du joueur
        Si la prochaine case est occupée par un joueur, peut pas
        Si la prochaine case n'est pas occupée et est de la glace, peut se déplacer
        Si la prochaine case est occupé par un objet différent d'un glaçon ou d'un piège, peut pas se déplacer
        Si c'est un glaçon, déplace d'abord le glaçon avant de déplacer le joueur
        Si c'est un piège, déplace et le bloc un tour
        */
        case 0 :


            /*if(nouvelle_case.etat==0) // Si un joueur va dans l'eau, il meurt
            {
              mortJoueur
            }*/

            if(nouvelle_case.occupe!=NULL)  //Si un joueur est présent sur la case souhaitait, c'est impossible
            {
              printf("\n\nIl y a un joueur a cette case\n\n");
            }


            if((nouvelle_case.typeObjet==NULL && nouvelle_case.occupe==NULL && nouvelle_case.etat==1)/*||(nouvelle_case.typeObjet!=NULL && nouvelle_case.typeObjet->objet==0)*/) // On a pas besoin de mettre (haut.occupe==NULL && haut.etat==1) si on change en else if car les condition sont vérifiées avant
            {
                //Si il n'y a pas d'objet sur la prochaine case, il se déplace
                tableau_joueur[*indice_joueur].position.y-=1;
                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe;
                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe=NULL;
            }

              else if(nouvelle_case.typeObjet->objet==0)
              {
                  nouvelle_case.typeObjet->vecteur.dy=-1;
                  nouvelle_case.typeObjet->vecteur.dx=0;
                  int casGlacon=numeroCasGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y-1, 0, -1, tailleBanquise);
                  if((casGlacon==0) || (casGlacon==2))
                  {
                      printf("\n\nLe glacon ne peut se deplacer, il rencontre un obstacle\n\n");
                  }
                  else
                  {
                      deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y-1, 0, -1, tailleBanquise);
                      /*
                      Si le joueur n'est pas mort, on le déplace
                      tableau_joueur[*indice_joueur].position.y-=1;
                      banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                      banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe;
                      banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe=NULL;
                      */
                  }
              }

            break;

      case 1 :


            /*if(nouvelle_case.etat==0) // Si un joueur va dans l'eau, il meurt
            {
              mortJoueur
            }*/

            if(nouvelle_case.occupe!=NULL)  //Si un joueur est présent sur la case souhaitait, c'est impossible
            {
              printf("\n\nIl y a un joueur a cette case\n\n");
            }


            if((nouvelle_case.typeObjet==NULL && nouvelle_case.occupe==NULL && nouvelle_case.etat==1)/*||(nouvelle_case.typeObjet!=NULL && nouvelle_case.typeObjet->objet==0)*/) // On a pas besoin de mettre (haut.occupe==NULL && haut.etat==1) si on change en else if car les condition sont vérifiées avant
            {
                //Si il n'y a pas d'objet sur la prochaine case, il se déplace
                tableau_joueur[*indice_joueur].position.x-=1;
                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe;
                banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
              }
              else if(nouvelle_case.typeObjet->objet==0)
              {
                  nouvelle_case.typeObjet->vecteur.dy=0;
                  nouvelle_case.typeObjet->vecteur.dx=-1;
                  int casGlacon=numeroCasGlacon(banquise, tableau_joueur[*indice_joueur].position.x-1, tableau_joueur[*indice_joueur].position.y, -1, 0, tailleBanquise);
                  if((casGlacon==0) || (casGlacon==2))
                  {
                      printf("\n\nLe glacon ne peut se deplacer, il rencontre un obstacle\n\n");
                  }
                  else
                  {
                      deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x-1, tableau_joueur[*indice_joueur].position.y, -1, 0, tailleBanquise);
                      /*
                      Si le joueur n'est pas mort, on le déplace
                      tableau_joueur[*indice_joueur].position.y-=1;
                      banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                      banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe;
                      banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                        */
                  }
              }

            break;
      case 2 :


            /*if(nouvelle_case.etat==0) // Si un joueur va dans l'eau, il meurt
            {
              mortJoueur
            }*/

            if(nouvelle_case.occupe!=NULL)  //Si un joueur est présent sur la case souhaitait, c'est impossible
            {
              printf("\n\nIl y a un joueur a cette case\n\n");
            }


            if((nouvelle_case.typeObjet==NULL && nouvelle_case.occupe==NULL && nouvelle_case.etat==1)/*||(nouvelle_case.typeObjet!=NULL && nouvelle_case.typeObjet->objet==0)*/) // On a pas besoin de mettre (haut.occupe==NULL && haut.etat==1) si on change en else if car les condition sont vérifiées avant
            {
                //Si il n'y a pas d'objet sur la prochaine case, il se déplace
                tableau_joueur[*indice_joueur].position.y+=1;
                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe;
                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe=NULL;
              }
              else if(nouvelle_case.typeObjet->objet==0)
              {
                  nouvelle_case.typeObjet->vecteur.dy=1;
                  nouvelle_case.typeObjet->vecteur.dx=0;
                  int casGlacon=numeroCasGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y+1, 0, 1, tailleBanquise);
                  if((casGlacon==0) || (casGlacon==2))
                  {
                      printf("\n\nLe glacon ne peut se deplacer, il rencontre un obstacle\n\n");
                  }
                  else
                  {
                      deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y+1, 0, 1, tailleBanquise);
                      /*
                      si le joueur n'est pas mort, on le déplace
                      tableau_joueur[*indice_joueur].position.y+=1;
                      banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                      banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe;
                      banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe=NULL;
                      */
                  }
              }

            break;

      case 3 :


            /*if(nouvelle_case.etat==0) // Si un joueur va dans l'eau, il meurt
            {
              mortJoueur
            }*/

            if(nouvelle_case.occupe!=NULL)  //Si un joueur est présent sur la case souhaitait, c'est impossible
            {
              printf("\n\nIl y a un joueur a cette case\n\n");
            }


            if((nouvelle_case.typeObjet==NULL && nouvelle_case.occupe==NULL && nouvelle_case.etat==1)/*||(nouvelle_case.typeObjet!=NULL && nouvelle_case.typeObjet->objet==0)*/) // On a pas besoin de mettre (haut.occupe==NULL && haut.etat==1) si on change en else if car les condition sont vérifiées avant
            {
                //Si il n'y a pas d'objet sur la prochaine case, il se déplace
                tableau_joueur[*indice_joueur].position.x+=1;
                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe;
                banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
              }
              else if(nouvelle_case.typeObjet->objet==0)
              {
                  nouvelle_case.typeObjet->vecteur.dy=0;
                  nouvelle_case.typeObjet->vecteur.dx=+1;
                  int casGlacon=numeroCasGlacon(banquise, tableau_joueur[*indice_joueur].position.x+1, tableau_joueur[*indice_joueur].position.y, 1, 0, tailleBanquise);
                  if((casGlacon==0) || (casGlacon==2))
                  {
                      printf("\n\nLe glacon ne peut se deplacer, il rencontre un obstacle\n\n");
                  }
                  else
                  {
                      deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x+1, tableau_joueur[*indice_joueur].position.y, 1, 0, tailleBanquise);
                      /*
                      Si le joueur n'est pas mort, on le déplace
                      tableau_joueur[*indice_joueur].position.y-=1;
                      banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                      banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe;
                      banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                        */
                  }
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
