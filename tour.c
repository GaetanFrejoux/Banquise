//INCLUDES

#include "tour.h"

//FONCTIONS
void tour_joueur(T_case **banquise,T_joueur *tableau_joueur)
{
    int choix=-1;
    char mouvement='p';
    do
    {
    printf("\nchoix "); //Demande � l'utisateur de rentrer une valeur.
    scanf("%c",&mouvement);   // Demande de l'input par l'utilisateur.
    }
    while(mouvement!="z"||mouvement!='q'||mouvement!='s'||mouvement!='d');

    if(mouvement=='z') choix=0;
    else if(mouvement=='q') choix=1;
    else if(mouvement=='s') choix=2;
    else choix=3;

    switch(choix)
    {
        case 0 :
            tableau_joueur[0].position.y-=1;
            banquise[tableau_joueur[0].position.x][tableau_joueur[0].position.y-1].occupe=(T_joueur*)malloc(sizeof(T_joueur));
            banquise[tableau_joueur[0].position.x][tableau_joueur[0].position.y-1].occupe=banquise[tableau_joueur[0].position.x][tableau_joueur[0].position.y].occupe;
            banquise[tableau_joueur[0].position.x][tableau_joueur[0].position.y].occupe=NULL;
            break;

        case 1 :

            break;

        case 2 :

            break;

        case 3 :

            break;
    }
}
