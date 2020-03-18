//INCLUDES

#include "banquise.h"

//FONCTIONS

// choisi la couleur de fond et du texte
void color(int t, int f)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
}

 // Affiche la banquise
void affichageBanquise(T_case **banquise, int taille)
{
    //system("cls"); // clear le cmd
    for(int i=0;i<16;i++) //boucle pour tous les cas de couleurs
    {
        (i<10) ? color(15,i): color(0,i);
        switch(i)
        {
        case 0 :
        printf("Depart\n");
        break;
        case 1 :
        printf("Il n'y a rien attribuer en bleu fonce\n");
        break;
        case 2 :
        printf("Joueur 1\n");
        break;
        case 3 :
        printf("Joueur 2\n");
        break;
        case 4 :
        printf("Joueur 3\n");
        break;
        case 5 :
        printf("Joueur 4\n");
        break;
        case 6 :
        printf("Arrive\n");
        break;
        case 7 :
        printf("Glacons\n");
        break;
        case 8 :
        printf("Rocher\n");
        break;
        case 9 :
        printf("Eau\n");
        break;
        case 10 :
        printf("Baton Marteau\n");
        break;
        case 11 :
        printf("Marteau\n");
        break;
        case 12 :
        printf("Bord de la carte\n");
        break;
        case 13 :
        printf("Piege\n");
        break;
        case 14 :
        printf("Ressort\n");
        break;
        case 15 :
        printf("Banquise\n");
        break;


        }
    }
    int i, j;
    for(j=0; j<taille+2; j++) //boucle d'affiche
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
                    if (banquise[i-1][j-1].occupe!=NULL)
                    {
                      color(15,banquise[i-1][j-1].occupe->identite+1); // prend une couleur différente pour chaque joueur.
                      printf(" %d ", banquise[i-1][j-1].occupe->identite);
                    }
                    else if(banquise[i-1][j-1].symbole=='D')
                    {
                        color(15,0);
                        printf(" %c ", banquise[i-1][j-1].symbole);
                    }
                    else if (banquise[i-1][j-1].symbole=='A')
                    {
                        color(15,6);
                        printf(" %c ", banquise[i-1][j-1].symbole);
                    }
                    else if (banquise[i-1][j-1].typeObjet!=NULL)
                    {
                        switch(banquise[i-1][j-1].typeObjet->objet)
                        {
                        case 0 :
                        color(0,7);
                        printf("   ");
                        break;

                        case 1 :
                        color(0,8);
                        printf("   ");
                        break;

                        case 2 :
                        color(0,10);
                        printf("   ");
                        break;

                        case 3 :
                        color(0,11);
                        printf("   ");
                        break;

                        case 4 :
                        color(0,15);
                        printf("   ");
                        break;

                        case 5 :
                        color(0,14);
                        printf("   ");
                        break;

                        }
                    }
                    else
                    {
                      color(0,15);
                      printf("   ");
                    }
                } else
                {
                    color(0,9);
                    printf("   ", banquise[i-1][j-1].symbole);
                }
            }
        }
        color(15,0);
    }

    return;
}

 // Affiche la matrice de l'état de la banquise
void affichageEtatBanquise(int **etatBanquise, int taille)
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

 //Dis si la case est de la glace (1) ou de l'eau (0)
int estDeLaGlace(int **etatBanquise, int i, int j)
{
  return (etatBanquise[i][j]==0) ? 0 : 1; //Si la condition est vérifiée, on dit que c'est de l'eau (0) donc on return faux (0). Si la condition est fausse,on dit que c'est de la glace et on return vrai (1)
}
 // Dis si la case actuelle a le droit de fondre (1) ou non (0)
int banquisePeutFondre(int **etatBanquise, int i, int j, int taille)
{
    // VARIABLES

    int peutFondre=0 ;

    //CODE

    if(i>0 && i<taille-1 && j>0 && j<taille-1)  //On regarde si la case de glace se situe a cote d'une limite du plateau ou ailleur
    {
        peutFondre = estDeLaGlace(etatBanquise, i-1, j) + estDeLaGlace(etatBanquise, i+1, j) + estDeLaGlace(etatBanquise, i, j+1) + estDeLaGlace(etatBanquise, i, j-1);
        if(peutFondre==4) //Si la case de glace est entourée de glace, elle ne peut pas fondre (0)
        {
            return 0;
        }
        else // Si la case de glace possède au moins une case d'eau autour d'elle, elle peut dondre (1)
        {
            return 1;
        }
    }
    else //Si la case de glace est � c�t� d'une limite du plateau, elle peut fondre (1)
    {
        return 1;
    }
}

 // Fonction permettant de copier l'�tat de la banquise et de la sauvegard�e dans la matrice etatBanquise
void majBanquise(T_case **banquise, int **etatBanquise, int taille)
{
    int i, j;
    for (i=0;i<taille;i++) //On parcourt la matrice banquise
    {
        for (j=0;j<taille;j++)
        {
            etatBanquise[i][j]=banquise[i][j].etat; // On copie la valeur de son �tat dans la matrice etatBanquise
        }
    }

    return;
}

// Fonction permettant d'appliquer la fonte des glaces du terrain
void fonteDesGlaces(T_case **banquise,T_joueur *tableau_joueur, int **etatBanquise, int taille)
{
    // VARIABLES

    srand(time(NULL));
    int i, j, fonteBanquise;

    //CODE

    for(j=0; j<taille; j++) // On parcours la banquise et on regarde si les cases sont de l'eau ou de la banquise
    {
        for(i=0;i<taille; i++)
        {
            if((etatBanquise[i][j]==1) && (banquisePeutFondre(etatBanquise,i,j,taille)==1) && (banquise[i][j].checkpoint==0) && (banquise[i][j].typeObjet==NULL))
            /*
            On regarde si la case est une case de banquise, si la case peut fondre (1) ou non (0).
            Si la case est la case de départ ou d'arrivée, elle ne peut pas fondre
            */
            {
                //Si oui, on tire un nombre aléatoire pour voir si elle peut fondre
                fonteBanquise = rand() % 100; // Ici, la banquise à 10% de chance de fondre
                if(fonteBanquise < 10) // On compare le nombre au pourcentage choisi, et si le nombre rentre dans le pourcentage :
                {
                    banquise[i][j].etat = 0; //La banquise devient de l'eau
                    if(banquise[i][j].typeObjet!=NULL)
                    {
                        if(banquise[i][j].typeObjet->objet==2) // Si l'objet est un axe de marteau, on le supprime ainsi que sa tête de marteau
                        {
                            banquise[banquise[i][j].typeObjet->position.x][banquise[i][j].typeObjet->position.y].typeObjet = NULL;
                            banquise[banquise[i][j].typeObjet->position.x][banquise[i][j].typeObjet->position.y].symbole = 'E';
                            banquise[i][j].typeObjet = NULL;
                            banquise[i][j].symbole = 'E';
                        }
                        else if(banquise[i][j].typeObjet->objet==0)  // Si l'objet est un glaçon, il tombe dans l'eau (suppréssion) et la case redevient de la banquise
                        {
                            banquise[i][j].etat = 1;
                            banquise[i][j].typeObjet = NULL;
                        }
                        else
                        {
                            banquise[i][j].typeObjet = NULL; // Si la case fond, on supprimes les autres objets
                            if(banquise[i][j].occupe!=NULL) // Si un joueur était présent sur la case, il meurt et on incrémente le nombre de morts
                            {
                              tableau_joueur[banquise[i][j].occupe->representation].etat=0;
                              banquise[i][j].occupe = NULL;
                            }
                            banquise[i][j].symbole = 'E'; // Le symbole change
                        }
                    }
                    if(banquise[i][j].typeObjet==NULL)
                    {
                        banquise[i][j].typeObjet = NULL; // Il n'y a plus d'objet sur la case
                        if(banquise[i][j].occupe!=NULL)
                        {
                          tableau_joueur[banquise[i][j].occupe->representation].etat=0;
                        }
                        banquise[i][j].symbole = 'E'; // Le symbole change
                    }
                }
            }
        }

    }

    majBanquise(banquise, etatBanquise, taille); // Une fois la banquise enti�rement chang�e, on peut mettre � jour l'�tat de la surface de la banquise dans la deuxi�me matrice


    return;
}

//Fonction permettant d'appliquer la fonte aux gla�ons
void glaconFond(T_case **banquise, int taille)
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

// Compte le nombre total de glaçons présents sur la banquise
int totalDeGlacon(T_case **banquise, int taille)
{

  //VARIABLES


  int i,j,nbGlacon=0;

  //CODE


  for(j=0; j<taille; j++) // On parcours la banquise et on regarde si les cases sont de l'eau ou de la banquise
  {
      for(i=0;i<taille; i++)
      {
          if(banquise[i][j].typeObjet!=NULL) //On regarde si la case pointe sur un objet ou sur null
          {
            if(banquise[i][j].typeObjet->objet==0) // Si la case pointe sur un objet, on regarde si c'est un glaçon
            {
              nbGlacon += 1; //Si c'est un glaçon, on incrémente le nombre de glaçons de 1
            }
          }
      }

  }

  //RETURN


  return nbGlacon;
}

//fonction qui regarde s'il y a un gagnant
int winner(T_case** banquise,T_position *ptr_case_arrive)
{
    if(banquise[ptr_case_arrive->x][ptr_case_arrive->y].occupe!=NULL)
    {
        printf("\nLe gagnant est : %s\n",banquise[ptr_case_arrive->x][ptr_case_arrive->y].occupe->nom);
        return 1;
    }
    return 0;
}

// Cette fonction indique dans quel cas un glaçon se situe et comment il va réagir lors d'un déplacement
int numeroCasGlacon(T_case **banquise, int i, int j, int directionX, int directionY, int tailleBanquise)
/*
Fonction qui indique le retour d'un glaçon qui se déplace:
0 : le glaçon reste sur Place
1 : le glaçon se déplace normalement
2 : le glaçon reste sur place et la tête de marteau va se déplacer.
3 : le glaçon effectue encore un déplacement et s'arrête à l'endroit du piège, en le remplaçant
4 : le glaçon rencontre un ressort, il va donc changer de sens
*/
{
  int retour = 0;


  if(directionX==-1)
  {
    if(i-1<0) // Si la case d'après est hors de la zone de la banquise, le glaçon peut s'y déplacer
    {
      retour = 1;
    }
    else if(banquise[i-1][j].typeObjet==NULL) // Si il n'y a pas d'objet sur la case d'après, le glaçon peut s'y déplacer
    {
      retour = 1;
    }
    else if((banquise[i-1][j].typeObjet->objet==0) || (banquise[i-1][j].typeObjet->objet==1) || (banquise[i-1][j].typeObjet->objet==2)) //Si il y a un autre glaçon, un rocher ou l'axe d'un marteau sur la case d'après, le glaçon ne peut pas s'y déplacer.
    {
      retour = 0;
    }
    else if(banquise[i-1][j].typeObjet->objet==3) //Si le glaçon rencontre une tête de marteau,
    {
        if(banquise[i-2][j].typeObjet==NULL) // Si c'est sur l'un des deux autres côtés que le prolongement de l'axe, le marteau se met à tourner et le glaçon s'arrête
        {
            return 2;
        }
        else // Si c'est sur le coté dans le prolongement de l'axe, le glaçon s'arrète simplement
        {
            if(banquise[i-2][j].typeObjet->objet==2)
            {
                return 0;
            }
            else
            {
                return 2;
            }
        }
    }
    else if(banquise[i-1][j].typeObjet->objet==4) // Si on rencontre un priège, on est dans le cas 3
    {
      retour = 3;
    }
    else if(banquise[i-1][j].typeObjet->objet==5) // Si on rencontre un ressort, on est dans le cas 4
    {
      retour = 4;
    }
    else
    {
      printf("\n\n\nERROR\n\n\n");
    }
  }


  if(directionX==1)
  {
    if(i+1>=tailleBanquise) // Si la case d'après est hors de la zone de la banquise, le glaçon peut s'y déplacer
    {
      retour = 1;
    }
    else if(banquise[i+1][j].typeObjet==NULL) // Si il n'y a pas d'objet sur la case d'après, le glaçon peut s'y déplacer
    {
      retour = 1;
    }
    else if((banquise[i+1][j].typeObjet->objet==0) || (banquise[i+1][j].typeObjet->objet==1) || (banquise[i+1][j].typeObjet->objet==2)) //Si il y a un autre glaçon, un rocher ou l'axe d'un marteau sur la case d'après, le glaçon ne peut pas s'y déplacer.
    {
      retour = 0;
    }
    else if(banquise[i+1][j].typeObjet->objet==3) //Si le glaçon rencontre une tête de marteau,
    {
        if(banquise[i+2][j].typeObjet==NULL) // Si c'est sur l'un des deux autres côtés que le prolongement de l'axe, le marteau se met à tourner et le glaçon s'arrête
        {
            return 2;
        }
        else // Si c'est sur le coté dans le prolongement de l'axe, le glaçon s'arrète simplement
        {
            if(banquise[i+2][j].typeObjet->objet==2)
            {
                return 0;
            }
            else
            {
                return 2;
            }
        }
    }
    else if(banquise[i+1][j].typeObjet->objet==4) // Si on rencontre un priège, on est dans le cas 3
    {
      retour = 3;
    }
    else if(banquise[i+1][j].typeObjet->objet==5) // Si on rencontre un ressort, on est dans le cas 4
    {
      retour = 4;
    }
    else
    {
      printf("\n\n\nERROR\n\n\n");
    }

  }


  if(directionY==-1)
  {
    if(j-1<0) // Si la case d'après est hors de la zone de la banquise, le glaçon peut s'y déplacer
    {
      retour = 1;
    }
    else if(banquise[i][j-1].typeObjet==NULL) // Si il n'y a pas d'objet sur la case d'après, le glaçon peut s'y déplacer
    {
      retour = 1;
    }
    else if((banquise[i][j-1].typeObjet->objet==0) || (banquise[i][j-1].typeObjet->objet==1) || (banquise[i][j-1].typeObjet->objet==2)) //Si il y a un autre glaçon, un rocher ou l'axe d'un marteau sur la case d'après, le glaçon ne peut pas s'y déplacer.
    {
      retour = 0;
    }
    else if(banquise[i][j-1].typeObjet->objet==3) //Si le glaçon rencontre une tête de marteau,
    {
        if(banquise[i][j-2].typeObjet==NULL) // Si c'est sur l'un des deux autres côtés que le prolongement de l'axe, le marteau se met à tourner et le glaçon s'arrête
        {
            return 2;
        }
        else // Si c'est sur le coté dans le prolongement de l'axe, le glaçon s'arrète simplement
        {
            if(banquise[i][j-2].typeObjet->objet==2)
            {
                return 0;
            }
            else
            {
                return 2;
            }
        }
    }
    else if(banquise[i][j-1].typeObjet->objet==4) // Si on rencontre un priège, on est dans le cas 3
    {
      retour = 3;
    }
    else if(banquise[i][j-1].typeObjet->objet==5) // Si on rencontre un ressort, on est dans le cas 4
    {
      retour = 4;
    }
    else
    {
      printf("\n\n\nERROR\n\n\n");
    }

  }


  if(directionY==1)
  {
    if(j+1>=tailleBanquise) // Si la case d'après est hors de la zone de la banquise, le glaçon peut s'y déplacer
    {
      retour = 1;
    }
    else if(banquise[i][j+1].typeObjet==NULL) // Si il n'y a pas d'objet sur la case d'après, le glaçon peut s'y déplacer
    {
      retour = 1;
    }
    else if((banquise[i][j+1].typeObjet->objet==0) || (banquise[i][j+1].typeObjet->objet==1) || (banquise[i][j+1].typeObjet->objet==2)) //Si il y a un autre glaçon, un rocher ou l'axe d'un marteau sur la case d'après, le glaçon ne peut pas s'y déplacer.
    {
      retour = 0;
    }
    else if(banquise[i][j+1].typeObjet->objet==3) //Si le glaçon rencontre une tête de marteau,
    {
        if(banquise[i][j+2].typeObjet==NULL) // Si c'est sur l'un des deux autres côtés que le prolongement de l'axe, le marteau se met à tourner et le glaçon s'arrête
        {
            return 2;
        }
        else // Si c'est sur le coté dans le prolongement de l'axe, le glaçon s'arrète simplement
        {
            if(banquise[i][j+2].typeObjet->objet==2)
            {
                return 0;
            }
            else
            {
                return 2;
            }
        }
    }
    else if(banquise[i][j+1].typeObjet->objet==4) // Si on rencontre un priège, on est dans le cas 3
    {
      retour = 3;
    }
    else if(banquise[i][j+1].typeObjet->objet==5) // Si on rencontre un ressort, on est dans le cas 4
    {
      retour = 4;
    }
    else
    {
      printf("\n\n\nERROR\n\n\n");
    }

  }

  return retour;

}

//Cette fonction donne un vecteur de déplacement au glaçon en fonction du cas rencontrer
void vecteurGlacon(T_case **banquise, int i, int j, int directionX, int directionY, int tailleBanquise, int *ptrPiege, T_joueur *tableau_joueur, int nombre_joueur)
{
    int cas = numeroCasGlacon(banquise, i, j, directionX, directionY, tailleBanquise);
    switch(cas)
    {
    case 0 :
        banquise[i][j].typeObjet->vecteur.dx=0;
        banquise[i][j].typeObjet->vecteur.dy=0;
        break;

    case 1 :
        banquise[i][j].typeObjet->vecteur.dx=directionX;
        banquise[i][j].typeObjet->vecteur.dy=directionY;
        break;

    case 2 :
        banquise[i][j].typeObjet->vecteur.dx=0;
        banquise[i][j].typeObjet->vecteur.dy=0;
        deplacementMarteau(banquise, i+directionX, j+directionY, directionX, directionY, tailleBanquise, 3, tableau_joueur, nombre_joueur);
        break;

    case 3 : //Pour le piège, on donne quand même le déplacement, on imobilisera le glaçon après le déplacement
        banquise[i][j].typeObjet->vecteur.dx=directionX;
        banquise[i][j].typeObjet->vecteur.dy=directionY;
        *ptrPiege=1;
        break;

    case 4 :
        banquise[i][j].typeObjet->vecteur.dx=-directionX;
        banquise[i][j].typeObjet->vecteur.dy=-directionY;
        vecteurGlacon(banquise, i, j, banquise[i][j].typeObjet->vecteur.dx, banquise[i][j].typeObjet->vecteur.dy, tailleBanquise, ptrPiege, tableau_joueur, nombre_joueur); // Dans le cas du ressort, on vérifie que le glaçon ne rencontre rien et peut bouger lors du retour.
        break;

    default :
        printf("\n\nERROR : vecteurGlacon\n\n");
    }
}

 //Cette fonction réalise le déplacement du glaçon et si le glaçon rencontre un joueur, appel une fonction de mort du joueur
void deplacementGlacon(T_case **banquise, int i, int j, int directionX, int directionY, int tailleBanquise, T_joueur *tableau_joueur, int nombre_joueur)
{
    int casPiege=0;
    int *ptrPiege=&casPiege;
    if((directionX==0) && (directionY==0))  // Si le glaçon ne bouge pas, on arrête la fonction
    {
        return;
    }
    else
    {
        if((i+directionX <0) || (j+directionY<0)  || (i+directionX>=tailleBanquise)  || (j+directionY>= tailleBanquise))
            //Si le glaçon sort de la zone de jeu, il est supprimé
        {
            banquise[i][j].typeObjet=NULL;
        }
        else
            //Si le glaçon ne sort pas de la zone de jeu, on calcul son nouveau vecteur et on lui applique un déplacement
        {
            vecteurGlacon(banquise, i, j, directionX, directionY, tailleBanquise, ptrPiege, tableau_joueur, nombre_joueur);
            if((banquise[i][j].typeObjet->vecteur.dx==0) && (banquise[i][j].typeObjet->vecteur.dy==0))
            {
                return;
            }
            else
            {
                if(*ptrPiege==1) //Si on est dans le cas du piège, ptrPiege=1. On enlève le piège de la prochaine casse pour dire qu'il est utilisé.
                {
                    banquise[i+banquise[i][j].typeObjet->vecteur.dx][j+banquise[i][j].typeObjet->vecteur.dy].typeObjet=NULL;
                }
                banquise[i+banquise[i][j].typeObjet->vecteur.dx][j+banquise[i][j].typeObjet->vecteur.dy].typeObjet=(T_objet*)malloc(sizeof(T_objet));
                banquise[i+banquise[i][j].typeObjet->vecteur.dx][j+banquise[i][j].typeObjet->vecteur.dy].typeObjet=banquise[i][j].typeObjet;
                glaconKiller(banquise,tableau_joueur, i+banquise[i][j].typeObjet->vecteur.dx, j+banquise[i][j].typeObjet->vecteur.dy, nombre_joueur);
                if(*ptrPiege==1) //Si on est dans le cas du piège, une fois le déplacement réalisé, on met le vecteur du glaçon à 0 pour qu'il ne bouge plus.
                {
                    banquise[i+banquise[i][j].typeObjet->vecteur.dx][j+banquise[i][j].typeObjet->vecteur.dy].typeObjet->vecteur.dx=0;
                    banquise[i+banquise[i][j].typeObjet->vecteur.dx][j+banquise[i][j].typeObjet->vecteur.dy].typeObjet->vecteur.dy=0;
                }
                else
                {
                    transformationGlacon(banquise, i+banquise[i][j].typeObjet->vecteur.dx, j+banquise[i][j].typeObjet->vecteur.dy); // On regarde si le glaçon est tombé dans de l'eau
                }
                banquise[i][j].typeObjet=NULL;
            }
        }
    }
    return;
}

 // Fonction qui regarde si un glaçon est dans de l'eau. Si c'est le cas, elle transforme le tout en case de banquise
void transformationGlacon(T_case **banquise, int i, int j)
{
    if(banquise[i][j].typeObjet!=NULL)
    {
        if((banquise[i][j].typeObjet->objet==0) && (banquise[i][j].etat==0))
        {
            banquise[i][j].etat=1;
            banquise[i][j].typeObjet=NULL;
        }
    }
}
