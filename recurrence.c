//INCLUDES

#include "recurrence.h"

//FONCTIONS

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

void remiseAZeroPassage(int **passage, int tailleBanquise)
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

void finPossible(T_case **banquise, int tailleBanquise, int **passage, int i, int j)
{
    int retour = 0;

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

    remiseAZeroPassage(passage, tailleBanquise);
}

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

int finPossibleAuxiliaire(int **passage, T_case **banquise, int i, int j, int tailleBanquise)
{
  int retour=0, x=i, y=j;
  passage[i][j]=1;
  if(banquise[i][j].checkpoint==2)
  {
    return 1;
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
  if(retour==0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}







/*T_file creerFile()
{
    T_file F;
    F.deb=F.fin=NULL;
    return F;
}

void enfiler(T_file *F, int i, int j)
{
    T_cellule *nouveau=(T_cellule *)malloc(sizeof(T_cellule));
    nouveau->x=i;
    nouveau->y=j;
    nouveau->suivant=NULL;
    if(F->deb==NULL)
    {
        F->deb=nouveau;
        F->fin=nouveau;
    }
    else
    {
        F->fin->suivant=nouveau;
        F->fin=nouveau;
    }
}

void defiler(T_file *F)
{
    T_cellule *tmp=F->deb;
    if(F->deb!=NULL)
    {
        F->deb=F->deb->suivant;
        free (tmp);
        if(F->deb==NULL)
        {
            F->fin=NULL;
        }
    }
}

int dejaVu(T_file *chemin, int i, int j) //Regarde si on est d�j� pass� par la case i,j ou non. Si retourne 1 , oui, si 0, non
{
    int retour = 0;
    T_cellule *celluleActuelle = chemin->deb;
    while(celluleActuelle != NULL)
    {
        if((celluleActuelle->x==i) && (celluleActuelle->y==j))
        {
            retour = 1;
        }
        celluleActuelle = celluleActuelle->suivant;
    }
    return retour;
}

int finPossible(T_case **banquise, int i, int j, int tailleBanquise)
/*
Regarde si il existe un chemin pour aller d'un point donn�e en coordonn�es i, j, jusqu'� l'arriv�e.
Si oui, il renvoie le nombre de coups minimum.
Si non, il renvoie le nombre de gla�on minimum nescessaire.
*/
/*
{
    T_file chemin = creerFile();
    return finPossibleAuxiliaire(banquise, chemin, tailleBanquise, i, j);
    /*if((banquise[i+1][j].etat==1) && (banquise[i+1][j].typeObjet->objet!=1) && (banquise[i+1][j].typeObjet->objet!=2))
    {
        T_file a = creerFile();
        if(finPossibleAuxiliaire(banquise, a, tailleBanquise, i+1, j)==1)
        {
            return 1;
        }
    }
    else if((banquise[i][j+1].etat==1) && (banquise[i][j+1].typeObjet->objet!=1) && (banquise[i][j+1].typeObjet->objet!=2))
    {
        T_file b = creerFile();
        if(finPossibleAuxiliaire(banquise, b, tailleBanquise, i, j+1)==1)
        {
            return 1;
        }
    }
    else if((banquise[i-1][j].etat==1) && (banquise[i-1][j].typeObjet->objet!=1) && (banquise[i-1][j].typeObjet->objet!=2))
    {
        T_file c = creerFile();
        if(finPossibleAuxiliaire(banquise, c, tailleBanquise, i-1, j)==1)
        {
            return 1;
        }
    }
    else if((banquise[i][j-1].etat==1) && (banquise[i][j-1].typeObjet->objet!=1) && (banquise[i][j-1].typeObjet->objet!=2))
    {
        T_file d = creerFile();
        if(finPossibleAuxiliaire(banquise, d, tailleBanquise, i, j-1)==1)
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }*//*
}


int finPossibleAuxiliaire(T_case **banquise, T_file *chemin, int tailleBanquise, int i, int j)
{
    if(banquise[i][j].checkpoint==2) //On regarde si la case est celle d'arriv�e
    {
        return 1; //A ce moment, si c'est la cas, on s'arr�te et on retourne 1 (vrai)
    }
    else
    {
        enfiler(chemin, i, j);
        if((banquise[i+1][j].etat==1) && (banquise[i+1][j].typeObjet->objet!=1) && (banquise[i+1][j].typeObjet->objet!=2) && (dejaVu(chemin, i+1, j)==0) && (i+1<tailleBanquise))
            /*
            Si la case suivante est de la glace
            et qu'il n'y a pas de rocher
            et qu'il n'y a pas d'axe de marteau
            et qu'on est pas d�j� pass� par cette case
            et que i ou j ne devienent pas inf�rieurs ou sup�rieurs aux limites de la carte,
            alors on continue de chercher des chemins
            */
        /*{
            finPossibleAuxiliaire(banquise, chemin, tailleBanquise, i+1, j);
        }
        else if((banquise[i][j+1].etat==1) && (banquise[i][j+1].typeObjet->objet!=1) && (banquise[i][j+1].typeObjet->objet!=2) && (dejaVu(chemin, i, j+1)==0) && (j+1<tailleBanquise))
        {
            while((chemin->fin.x!=i) && (chemin->fin.y!=j))
            {
                defiler(chemin);
            }
            finPossibleAuxiliaire(banquise, chemin, tailleBanquise, i, j+1);
        }
        else if((banquise[i-1][j].etat==1) && (banquise[i-1][j].typeObjet->objet!=1) && (banquise[i-1][j].typeObjet->objet!=2) && (dejaVu(chemin, i-1, j)==0) && (i-1>-1))
        {
            while((chemin->fin.x!=i) && (chemin->fin.y!=j))
            {
                defiler(chemin);
            }
            finPossibleAuxiliaire(banquise, chemin, tailleBanquise, i-1, j);
        }
        else if((banquise[i][j-1].etat==1) && (banquise[i][j-1].typeObjet->objet!=1) && (banquise[i][j-1].typeObjet->objet!=2) && (dejaVu(chemin, i, j-1)==0) && (j-1>-1))
        {
            while((chemin->fin.x!=i) && (chemin->fin.y!=j))
            {
                defiler(chemin);
            }
            finPossibleAuxiliaire(banquise, chemin, tailleBanquise, i, j-1);
        }
        else
        {
            return 0;
        }
    }

}*/
