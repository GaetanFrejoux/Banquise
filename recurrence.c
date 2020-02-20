//INCLUDES

#include "recurrence.h"

//FONCTIONS

T_file creerFile()
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

int dejaVu(T_file *chemin, int i, int j) //Regarde si on est déjà passé par la case i,j ou non. Si retourne 1 , oui, si 0, non
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
Regarde si il existe un chemin pour aller d'un point donnée en coordonnées i, j, jusqu'à l'arrivée.
Si oui, il renvoie le nombre de coups minimum.
Si non, il renvoie le nombre de glaçon minimum nescessaire.
*/
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
    }*/
}


int finPossibleAuxiliaire(T_case **banquise, T_file *chemin, int tailleBanquise, int i, int j)
{
    if(banquise[i][j].checkpoint==2) //On regarde si la case est celle d'arrivée
    {
        return 1; //A ce moment, si c'est la cas, on s'arrête et on retourne 1 (vrai)
    }
    else
    {
        enfiler(chemin, i, j);
        if((banquise[i+1][j].etat==1) && (banquise[i+1][j].typeObjet->objet!=1) && (banquise[i+1][j].typeObjet->objet!=2) && (dejaVu(chemin, i+1, j)==0) && (i+1<tailleBanquise))
            /*
            Si la case suivante est de la glace
            et qu'il n'y a pas de rocher
            et qu'il n'y a pas d'axe de marteau
            et qu'on est pas déjà passé par cette case
            et que i ou j ne devienent pas inférieurs ou supérieurs aux limites de la carte,
            alors on continue de chercher des chemins
            */
        {
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

}
