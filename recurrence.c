//INCLUDES

#include "recurrence.h"

//FONCTIONS
//fonction permettant de savoir si nous sommes deja passé par une case pour les fonctions recursive
int **init_passage(int tailleBanquise)
{
    int i,j;
    int **passage;
    passage =(int **)malloc(sizeof(int *)*(tailleBanquise)); //On créer un tableau pour savoir si l'on est déjà passé par la (1) ou non (0)
    for(i=0;i<tailleBanquise;i++)
    {
        passage[i] =(int *)malloc(sizeof(int)*(tailleBanquise));
    }

    for(j=0;j<tailleBanquise;j++) //On initialise toutes les cases à 0
    {
        for(i=0;i<tailleBanquise;i++)
        {
            passage[i][j]=0;
        }
    }
    return passage;
}
//fonction qui remet a 0 toutes les case.
void remiseAZeroPassage(int **passage, int tailleBanquise) // On a eu besoin de cette fonction dans une ancienne version de finPossible
{
    int i,j;
    for(j=0;j<tailleBanquise;j++) //On initialise toutes les cases à 0
    {
        for(i=0;i<tailleBanquise;i++)
        {
            passage[i][j]=0;
        }
    }
}
//fonction qui permet de tester si une fin est possible
void finPossible(T_case **banquise, int tailleBanquise, int i, int j) // On regarde si on peut rejoindre l'arrivée à partir de la position i, j
{
    int retour = 0;

    int **passage=init_passage(tailleBanquise);

    retour = finPossibleAuxiliaire(passage, banquise, i, j, tailleBanquise); // On appel la fonction auxiliaire pour tester les différents chemins possibles

    if(retour == 1)
    {
        printf("\n\nIl y a une solution possible\n\n");
    }
    else if(retour == 0)
    {
        printf("\n\nIl n'y a pas de solution possible\n\n");
    }
    else
    {
        printf("\n\nERROR\n\n");
    }

    /*remiseAZeroPassage(passage, tailleBanquise);*/
}
//fonction qui permet de savoir s'il est possible de se deplacer dans cette case
int aijeLeDroit(int **passage, T_case **banquise, int i, int j)
{
  if(banquise[i][j].etat==1 && banquise[i][j].typeObjet!=NULL)
  {
    if((banquise[i][j].typeObjet->objet!=1) && (banquise[i][j].typeObjet->objet!=2) && (banquise[i][j].typeObjet->objet!=5) && (passage[i][j]==0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
  }
  else
  {
    if((banquise[i][j].etat==1) && (passage[i][j]==0))
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
}
//fonction auxiliaire de fin possible
int finPossibleAuxiliaire(int **passage, T_case **banquise, int i, int j, int tailleBanquise)
{
  int retour=0, x=i, y=j;
  passage[i][j]=1;
  if(banquise[i][j].checkpoint==2)
  {
    retour = 1;
  }

  if(i+1<tailleBanquise && (retour!=1))
  {
    x=i+1;
    y = j;
    if(aijeLeDroit(passage, banquise, x, y)==1)
    {
      retour = finPossibleAuxiliaire(passage, banquise, x, y, tailleBanquise);
    }
  }
  if((i-1>=0) && (retour!=1))
  {
      x=i-1;
      y = j;
      if(aijeLeDroit(passage, banquise, x, y)==1)
      {
        retour = finPossibleAuxiliaire(passage, banquise, x, y, tailleBanquise);
      }
  }
  if((j+1<tailleBanquise) && (retour!=1))
  {
      x = i;
      y=j+1;
      if(aijeLeDroit(passage, banquise, x, y)==1)
      {
        retour = finPossibleAuxiliaire(passage, banquise, x, y, tailleBanquise);
      }
  }
  if((j-1>=0) && (retour!=1))
  {
      x = i;
      y=j-1;
      if(aijeLeDroit(passage, banquise, x, y)==1)
      {
        retour = finPossibleAuxiliaire(passage, banquise, x, y, tailleBanquise);
      }
  }

  return retour;

}
//fonction auxiliaire de finPossibleEau
int finPossibleEauAuxiliaire(int **passageEau, T_case **banquise, int i, int j, int tailleBanquise)
{
  int retour=0, x=i, y=j;
  passageEau[i][j]=1;
  if(banquise[i][j].checkpoint==2)
  {
    retour = 1;
  }

  if(i+1<tailleBanquise && (retour!=1))
  {
    x=i+1;
    y = j;
    if(passageEau[x][y]==0)
    {
      retour = finPossibleEauAuxiliaire(passageEau, banquise, x, y, tailleBanquise);
    }
  }
  if((i-1>=0) && (retour!=1))
  {
      x=i-1;
      y = j;
      if(passageEau[x][y]==0)
      {
        retour = finPossibleEauAuxiliaire(passageEau, banquise, x, y, tailleBanquise);
      }
  }
  if((j+1<tailleBanquise) && (retour!=1))
  {
      x = i;
      y=j+1;
      if(passageEau[x][y]==0)
      {
        retour = finPossibleEauAuxiliaire(passageEau, banquise, x, y, tailleBanquise);
      }
  }
  if((j-1>=0) && (retour!=1))
  {
      x = i;
      y=j-1;
      if(passageEau[x][y]==0)
      {
        retour = finPossibleEauAuxiliaire(passageEau, banquise, x, y, tailleBanquise);
      }
  }

  return retour;

}
//fonction qui initialise une matrice pour savoir si il existe un passageEau
int **initPassageEau(T_case **banquise, int tailleBanquise)
{
    int i, j;
    int **passageEau;
    passageEau =(int **)malloc(sizeof(int *)*(tailleBanquise)); //On créer un tableau pour savoir si l'on est déjà passé par la (1) ou non (0)
    for(i=0;i<tailleBanquise;i++)
    {
        passageEau[i] =(int *)malloc(sizeof(int)*(tailleBanquise));
    }


    for(j=0; j<tailleBanquise; j++)
    {
        for(i=0; i<tailleBanquise; i++)
        {
            if(banquise[i][j].etat==0)
            {
                passageEau[i][j]=-1; // -1 indique que la case est de l'eau
            }
            else if(banquise[i][j].etat==1)
            {
                if(banquise[i][j].typeObjet==NULL)
                {
                    passageEau[i][j]=0; // 0 Indique de la glace libre où avec un objet que l'on peut déplacer
                }
                else if(banquise[i][j].typeObjet!=NULL)
                {
                    if((banquise[i][j].typeObjet->objet==1) || (banquise[i][j].typeObjet->objet==2) || (banquise[i][j].typeObjet->objet==5))
                    {
                        passageEau[i][j]=-2; // -2 indique que la case est un objet que l'on ne peut déplacer
                    }
                    else
                    {
                        passageEau[i][j]=0;
                    }
                }
            }

        }
    }

    return passageEau;
}
//fonction qui creer un nouveau passage
void nouveauPassage(int **passageEau, int **sauvegardePassage, int tailleBanquise)
{
    int i, j;
    for(j=0; j<tailleBanquise; j++)
    {
        for(i=0; i<tailleBanquise; i++)
        {
            passageEau[i][j] = sauvegardePassage[i][j];
        }
    }
}
//fonction qui permet de savoir s'il est possible d'agrandir la surface
void peutOnAgrandir(int **sauvegardePassage, int i, int j, int tailleBanquise)
{
    if(i-1>=0)
    {
        if(sauvegardePassage[i-1][j]==-1) // Si on trouve une case qui est de l'eau
        {
            sauvegardePassage[i-1][j]=0; // On la considère comme de la glace, en suposant qu'on utilise un glaçon pour la combler
        }
    }
    if(i+1<tailleBanquise)
    {
        if(sauvegardePassage[i+1][j]==-1) // Si on trouve une case qui est de l'eau
        {
            sauvegardePassage[i+1][j]=0; // On la considère comme de la glace, en suposant qu'on utilise un glaçon pour la combler
        }
    }
    if(i-1>=0)
    {
        if(sauvegardePassage[i][j-1]==-1) // Si on trouve une case qui est de l'eau
        {
            sauvegardePassage[i][j-1]=0; // On la considère comme de la glace, en suposant qu'on utilise un glaçon pour la combler
        }
    }
    if(i+1<tailleBanquise)
    {
        if(sauvegardePassage[i][j+1]==-1) // Si on trouve une case qui est de l'eau
        {
            sauvegardePassage[i][j+1]=0; // On la considère comme de la glace, en suposant qu'on utilise un glaçon pour la combler
        }
    }
}
//fonction qui agrandit la surface
void augmentationSurfaceUtilise(int **passageEau, int **sauvegardePassage, int tailleBanquise)
{
    int i, j;
    for(j=0; j<tailleBanquise; j++)
    {
        for(i=0; i<tailleBanquise; i++)
        {
            if(passageEau[i][j]==1) // Si une case a était utilisé pour calculer un chemin, on regarde si ses cases adjacentes sont de l'eau ou non Si oui, on les considèrent comme de la glace en supposant qu'on utilise un glaçon
            {
                peutOnAgrandir(sauvegardePassage, i, j, tailleBanquise);
            }
        }
    }
}
//fonction qui test si il existe une fin possible avec de l'eau
int finPossibleEau(T_case **banquise, int tailleBanquise, int i, int j)
{
    int **passageEau = initPassageEau(banquise, tailleBanquise);
    int **sauvegardePassage = initPassageEau(banquise, tailleBanquise);
    int caseEauUtilise = 0;
    int retour = 0;
    do
    {
        retour = finPossibleEauAuxiliaire(passageEau, banquise, i, j, tailleBanquise);
        if(retour==0)
        {
            caseEauUtilise = caseEauUtilise+1;
            augmentationSurfaceUtilise(passageEau, sauvegardePassage, tailleBanquise);
            nouveauPassage(passageEau, sauvegardePassage, tailleBanquise);
        }
    }while(retour==0);

    return caseEauUtilise;
}
//fonction general qui effectue le test d'une fin possible ?
void peutOnFinir(T_case **banquise, int tailleBanquise, T_joueur *tableau_joueur, int numeroJoueur)
{
    int nbGlaconRestant = totalDeGlacon(banquise, tailleBanquise);
    int nbGlaconNescessaire = finPossibleEau(banquise, tailleBanquise, tableau_joueur[numeroJoueur].position.x, tableau_joueur[numeroJoueur].position.y);
    if(nbGlaconNescessaire==0)
    {
        printf("\n\nLe joueur %d peut rejoindre l'arrivee sans transformer de case\n\n", numeroJoueur);
    }
    else if(nbGlaconRestant - nbGlaconNescessaire >= 0)
    {
        printf("\n\nLe joueur %d peut rejoindre l'arrivee. Pour cela, il faut transformer %d case d'eau en glace avec des glacon\n\n", numeroJoueur, nbGlaconNescessaire);
    }
    else
    {
        printf("\n\nLe joueur %d ne peut pas rejoindre l'arrivee. Il n'y a pas assez de glacons\n\n", numeroJoueur);
    }
}
