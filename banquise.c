//INCLUDES

#include "banquise.h"

//FONCTIONS

void color(int t, int f)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
}
void affichageBanquise(T_case **banquise, int taille,T_position *ptr_case_depart, T_position *ptr_case_arrive)  // Affiche la banquise
{
    int i, j;
    for(j=0; j<taille+2; j++)
    {
        printf("\n");
        for(i=0;i<taille+2; i++)
        {
            if((i==0) || (i==taille+1) || (j==0) || (j==taille+1))
            {
                color(12,0);
                printf("///");
            }
            else
            {
                if(banquise[i-1][j-1].etat==1)
                {
                    if(((i==ptr_case_depart->x+1)&&(j==ptr_case_depart->y+1)))
                        color(0,3);
                    else if (((i==ptr_case_arrive->x+1)&&(j==ptr_case_arrive->y+1)))
                        color(0,4);
                    else
                        color(0,15);

                    printf("   ", banquise[i-1][j-1].symbole);
                } else
                {
                    color(0,9);
                    printf("   ", banquise[i-1][j-1].symbole);
                }
            }
        }
    }

    return;
}


void affichageEtatBanquise(int **etatBanquise, int taille)  // Affiche la matrice de l'�tat de la banquise FONCTION OK
{
    int i, j;
    for(j=0; j<taille+2; j++) //On fait un affichage de toute la banquise, plus des limites du tableau de jeu. C'est pourquoi on a taille +2.
    {
        printf("\n");
        for(i=0;i<taille+2; i++)
        {
            if((i==0) || (i==taille+1) || (j==0) || (j==taille+1)) // Si les coordonn�es i et j corespondent � la limite du plateau (i = 0 ou taille+1 ou j=0 ou taille+1), on affiche une limite
            {
                printf("///");
            }
            else //Sinon on affiche ce qui occupe ou ce qu'est la case
            {
                printf(" %d ", etatBanquise[i-1][j-1]);
            }
        }
        printf("\n"); //On saute une ligne � chaque fin de ligne pour repr�senter le plateau
    }

    return;
}

int estDeLaGlace(int **etatBanquise, int i, int j) //Dis si la case est de la glace (1) ou de l'eau (0)  FONCTION OK
{
  return (etatBanquise[i][j]==0) ? 0 : 1; //Si la condition est vérifiée, on dit que c'est de l'eau (0) donc on return faux (0). Si la condition est fausse,on dit que c'est de la glace et on return vrai (1)
}

int banquisePeutFondre(int **etatBanquise, int i, int j, int taille) // Dis si la case actuelle a le droit de fondre (1) ou non (0)  FONCTION OK
{
    // VARIABLES

    int peutFondre=0 ;

    //CODE

    if(i>0 && i<taille-1 && j>0 && j<taille-1)  //On regarde si la case de glace se situe � c�t� d'une limite du plateau o� ailleur
    {
        peutFondre = estDeLaGlace(etatBanquise, i-1, j) + estDeLaGlace(etatBanquise, i+1, j) + estDeLaGlace(etatBanquise, i, j+1) + estDeLaGlace(etatBanquise, i, j-1);
        if(peutFondre==4) //Si la case de glace est entour�e de glace, elle ne peut pas fondre (0)
        {
            return 0;
        }
        else // Si la case de glace pos�de au moins une case d'eau autour d'elle, elle peut dondre (1)
        {
            return 1;
        }
    }
    else //Si la case de glace est � c�t� d'une limite du plateau, elle peut fondre (1)
    {
        return 1;
    }
}

void majBanquise(T_case **banquise, int **etatBanquise, int taille) // Fonction permettant de copier l'�tat de la banquise et de la sauvegard�e dans la matrice etatBanquise FONCTION OK
{
    int i, j, etat;
    for (i=0;i<taille;i++) //On parcourt la matrice banquise
    {
        for (j=0;j<taille;j++)
        {
            etatBanquise[i][j]=banquise[i][j].etat; // On copie la valeur de son �tat dans la matrice etatBanquise
        }
    }

    return;
}

void fonteDesGlaces(T_case **banquise, int **etatBanquise, int taille) // Fonction permettant d'appliquer la fonte des glaces du terrain FONCTION OK
{
    // VARIABLES

    srand(time(NULL));
    int i, j, fonteBanquise;

    //CODE

    for(j=0; j<taille; j++) // On parcours la banquise et on regarde si les cases sont de l'eau ou de la banquise
    {
        for(i=0;i<taille; i++)
        {
            if((etatBanquise[i][j]==1) && (banquisePeutFondre(etatBanquise,i,j,taille)==1) && (banquise[i][j].checkpoint==0))
            /*
            On regarde si la case est une case de banquise, si la case peut fondre (1) ou non (0).
            Si la case est la case de départ ou d'arrivée, elle ne peut pas fondre
            */
            {
                //Si oui, on tire un nombre al�atoire pour voir si elle peut fondre
                fonteBanquise = rand() % 100; // Ici, la banquise � 5% de chance de fondre
                if(fonteBanquise < 5) // On compare le nombre au pourcentage choisi, et si le nombre rentre dans le pourcentage :
                {
                    banquise[i][j].etat = 0; //La banquise devient de l'eau
                    banquise[i][j].typeObjet = NULL; // Il n'y a plus d'objet sur la case
                    banquise[i][j].occupe = NULL; // Il n'y a plus de joueur
                    banquise[i][j].symbole = '^'; // Le symbole change
                }
            }
        }

    }

    //affichageBanquise(banquise, taille); // On affiche la nouvelle banquise apr�s la fonte des glaces.

    majBanquise(banquise, etatBanquise, taille); // Une fois la banquise enti�rement chang�e, on peut mettre � jour l'�tat de la surface de la banquise dans la deuxi�me matrice


    return;
}

void glaconFond(T_case **banquise, int taille)  //Fonction permettant d'appliquer la fonte aux gla�ons
{
    //VARIABLES

    int i,j,fonteGlacon;

    //CODE

    for(i=0;i<taille;i++) //On parcours la surface de la banquise � la recherche des gla�ons !
    {
        for(j=0;j<taille;j++)
        {
            if(banquise[i][j].typeObjet == 0)  // Si on trouve un gla�on, il a 5% de chance de fondre
            {
                fonteGlacon = rand() % 100; // On tire un nombre al�atoire entre 0 et 99
                if(fonteGlacon < 5) // On le compare au pourcentage de chance de fonde du gla�on
                {
                    banquise[i][j].typeObjet = NULL; // Si il est dans le pourcentage, le gla�on fond.
                }
            }
        }

    }

}
