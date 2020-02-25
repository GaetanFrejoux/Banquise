//INCLUDES

#include "tour.h"

//FONCTIONS
void tour_joueur(T_case **banquise,T_joueur *tableau_joueur,int* indice_joueur, int nombre_joueur)
{
    T_case haut = banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1];
    T_case bas = banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1];
    T_case gauche = banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y];
    T_case droite = banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y];
    int choix=-1;
    char mouvement;
    while(mouvement!='z'&& mouvement!='q'&& mouvement!='s'&& mouvement!='d')
    {
    printf("\n(z = Haut / q = Gauche / s = Bas / d = Droite) :");
    scanf("%c",&mouvement);
    }

    if(mouvement=='z') choix=0;
    else if(mouvement=='q') choix=1;
    else if(mouvement=='s') choix=2;
    else choix=3;
    switch(choix)
    {
        case 0 :

            if((haut.typeObjet==NULL && haut.occupe==NULL)||(haut.typeObjet!=NULL && haut.typeObjet->objet==0))
            {
                tableau_joueur[*indice_joueur].position.y-=1;
                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe;
                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe=NULL;
                if(haut.typeObjet!=NULL)
                {
                 banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].typeObjet=(T_objet*)malloc(sizeof(T_objet));
                 banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].typeObjet=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].typeObjet;
                 banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].typeObjet=NULL;
                }
            }

            break;

        case 1 :
            if(gauche.typeObjet==NULL && haut.occupe==NULL)
            {
                tableau_joueur[*indice_joueur].position.x-=1;
                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe;
                banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
            }
            break;
        case 2 :
            if(bas.typeObjet==NULL && haut.occupe==NULL)
            {
                tableau_joueur[*indice_joueur].position.y+=1;
                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe;
                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe=NULL;
            }
            break;
        case 3 :
            if(droite.typeObjet==NULL && haut.occupe==NULL)
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
