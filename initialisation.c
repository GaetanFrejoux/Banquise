
#include "initialisation.h"

//FONCTIONS

int init_nombre_joueur()
{
    int nombre=0;
    do
    {
    printf("\nVeuillez choisir le nombre de joueur entre 1 et 4: "); //Demande � l'utisateur de rentrer une valeur.
    scanf("%d",&nombre);   // Demande de l'input par l'utilisateur.
    }
    while(nombre>4||nombre<1);
    return nombre; // retourne la valeur que l'utilisateur a inscrite.
}

int init_taille() // Demande la taille du plateau de jeu
{
    int taille=0;
    do
    {
        printf("\nVeuillez choisir la taille de la banquise ( minimum : 8 , conseiller : 20 ) : "); //Demande � l'utisateur de rentrer une valeur.
        scanf("%d",&taille);   // Demande de l'input par l'utilisateur.
    }
    while(taille<3);
    return taille; // retourne la valeur que l'utilisateur a inscrite.
}

T_case **init_banquise(int taille) // Cr�er la matrice de la banquise et la banquise initiale.
{
    int i, j;
    T_case **banquise;
    banquise =(T_case **)malloc(sizeof(T_case *)*(taille));
    for(i=0;i<taille;i++)
    {
        banquise[i] =(T_case *)malloc(sizeof(T_case)*(taille));
    }
    for (i=0;i<taille;i++)
    {
        for (j=0;j<taille;j++)  // A modifier, utilisé que pour test
        {
            if(i==5 || j==5)
            {
                banquise[i][j].checkpoint=0;
                banquise[i][j].etat=0;
                banquise[i][j].occupe=NULL;
                banquise[i][j].symbole='E';
                banquise[i][j].typeObjet=NULL;
            }
            else
            {
                banquise[i][j].checkpoint=0;
                banquise[i][j].etat=1;
                banquise[i][j].occupe=NULL;
                banquise[i][j].symbole='V';
                banquise[i][j].typeObjet=NULL;
            }
        }
    }
    return banquise;
}

int **init_etat_banquise(int taille) // Cr�er une matrice qui permettra de sauvegarder l'�tat du sol de la banquise (1 pour banquise)
{
    int i, j;
    int **etatBanquise;
    etatBanquise =(int **)malloc(sizeof(int *)*(taille));
    for(i=0;i<taille;i++)
    {
        etatBanquise[i] =(int *)malloc(sizeof(int)*(taille));
    }
    for (i=0;i<taille;i++)
    {
        for (j=0;j<taille;j++)
        {
            etatBanquise[i][j]=1;
        }
    }
    return etatBanquise;
}

void init_depart_arriver(T_case **map,int taille,T_position *ptr_case_depart, T_position *ptr_case_arrive)
{
    srand(time(NULL));
    T_position depart,arrive;
    do
    {
        depart.x=rand()%taille;
        depart.y=rand()%taille;
        arrive.x=rand()%taille;
        arrive.y=rand()%taille;
    }
    while((map[depart.x][depart.y].etat!=1)||(map[arrive.x][arrive.y].etat!=1)||((depart.x==arrive.x)&&(depart.y==arrive.y))||((depart.x==0)||(depart.y==0)||(depart.x==taille-1)||(depart.y==taille-1)));
    map[depart.x][depart.y].checkpoint=1;
    map[depart.x][depart.y].symbole='D';
    map[arrive.x][arrive.y].checkpoint=2;
    map[arrive.x][arrive.y].symbole='A';
    ptr_case_depart->x=depart.x;
    ptr_case_arrive->x=arrive.x;
    ptr_case_depart->y=depart.y;
    ptr_case_arrive->y=arrive.y;
    return;
}

void apparition_objets(T_case **banquise, int taille) //Place des glacons de manière aléatoire sur la banquise.
{
  /*
  Ici, si le nombre passe en dessous de 10 %,
  et que la case n'est pas occupée par un joueur ou un objet,
  on créer le glaçon
  */
  //VARIABLES


  int i,j,k, pourcentage=0;
  int indice= -1;
  int possible=0;
  int possible_all=0;
  int nb_glacon=0,nb_rocher=0,nb_marteau=0,nb_piege=0;
  srand(time(NULL));
  //CODE

  for(i=0; i<taille; i++) // On parcours la banquise
  {
      for(j=0;j<taille; j++)
      {

        pourcentage = rand() % 100; //A chaque case, on tire un nombre au sort pour savoir si l'on pose un objet ou non
        if((banquise[i][j].occupe==NULL) && (banquise[i][j].typeObjet==NULL) && banquise[i][j].checkpoint==0)
        {
            if(pourcentage<5)
            indice=0;
            else if (pourcentage<10)
            indice=1;
            else if (pourcentage<30)
            indice=2;
            else if (pourcentage<35)
            indice=3;
            else if (pourcentage<40)
            indice=4;
            if(indice!=-1)
            {
                if( i>1 && i<taille-1 && j>1 && j<taille-1 )
                {
                    for(int a=i-1;a<i+2;a++)
                    {   if (possible_all==1) break;
                        for(int b=j-1;b<j+2;b++)
                        {   if (possible_all==1) break;
                            if(banquise[a][b].typeObjet!=NULL)
                            {
                                if(banquise[a][b].typeObjet->objet==2) possible_all=1;
                            }
                        }
                    }
                }

                if(possible_all==0)
                {
                    switch (indice)
                    {
                        case 0:
                        banquise[i][j].typeObjet=(T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i][j].typeObjet->objet=0;
                        break;
                        case 1:
                        banquise[i][j].typeObjet=(T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i][j].typeObjet->objet=1;
                        break;
                        case 2:
                        if( i>2 && i<taille-2 && j>2 && j<taille-2 )
                        {
                            for(int a=i-2;a<i+3;a++)
                            { if (possible==1) break;
                                for(int b=j-2;b<j+3;b++)
                                {
                                    if (possible==1) break;
                                    if(banquise[a][b].occupe!=NULL||banquise[a][b].typeObjet!=NULL)
                                    {
                                        possible=1;
                                    }
                                }
                            }
                            printf("%d\n",possible);
                            if(possible==0)
                            {
                                banquise[i][j].typeObjet=(T_objet*)(malloc(sizeof(T_objet)));
                                banquise[i+1][j].typeObjet=(T_objet*)(malloc(sizeof(T_objet)));
                                banquise[i][j].typeObjet->objet=2;
                                banquise[i+1][j].typeObjet->objet=3;

                            }
                            possible=0;
                        }
                        break;

                        case 3:
                        banquise[i][j].typeObjet=(T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i][j].typeObjet->objet=4;
                        break;
                        case 4:
                        banquise[i][j].typeObjet=(T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i][j].typeObjet->objet=5;
                        break;
                        default : break;
                    }
                }

            }
            indice=-1;
          }
          possible_all=0;
        }
      }
  return;
}



void initialisationDesObjets(T_case **banquise, int tailleBanquise, int **etatBanquise) // Créer les différents objets sur la carte
{
    int i,j;
    srand(time(NULL));
    apparitionMarteau(banquise, tailleBanquise, etatBanquise); // On créer d'abord les marteau pour qu'il prennent la place qu'il faut

    apparitionObjet(banquise, tailleBanquise, etatBanquise, 0, 5);
    apparitionObjet(banquise, tailleBanquise, etatBanquise, 1, 2);
    apparitionObjet(banquise, tailleBanquise, etatBanquise, 4, 3);
    apparitionObjet(banquise, tailleBanquise, etatBanquise, 5, 2);

     majBanquise(banquise, etatBanquise, tailleBanquise); // Une fois qu'on a fini de faire apparaitre les objets, on remet l'état de la banquise à son état initiale

}

void apparitionObjet(T_case **banquise, int tailleBanquise, int **etatBanquise, int numeroObjet, int pourcentage)
{
    int i, j;
    int indice = 0;
    /*srand(time(NULL));*/
    for(j=0; j<tailleBanquise; j++)
    {
        for(i=0; i<tailleBanquise; i++)
        {
            indice = rand() %100;
            if(indice < pourcentage)
            {
                if((banquise[i][j].occupe==NULL) && (etatBanquise[i][j]==1) && (banquise[i][j].checkpoint==0)) // Si la case n'est pas occupée par un joueur, qu'elle ne contient pas d'objet et que ce n'est pas le point d'arrivée ou de départ
                {
                    if((numeroObjet==1) || (numeroObjet==4) || (numeroObjet==5) || (numeroObjet==0)) // Si le numero de l'objet est bien différent d'un numéro du marteau, on créer l'objet, sinon, on ne fait rien
                    etatBanquise[i][j] = 0; // On indique que la case est occupée par un objet
                    banquise[i][j].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                    banquise[i][j].typeObjet->objet = numeroObjet;
                    if(numeroObjet==0) // Si un glaçon est créer, on initialise son vecteur à 0
                    {
                        banquise[i][j].typeObjet->vecteur.dx = 0;
                        banquise[i][j].typeObjet->vecteur.dy = 0;
                    }
                }
            }
        }
    }
}

void apparitionMarteau(T_case **banquise, int tailleBanquise, int **etatBanquise) // On utilise etatBanquise pour indiquer les cases occupées par un objet. A la fin de la création des objets, on devra remettre etatBanquise normalement.
{
    int i, j, indice;
    /*srand(time(NULL));*/
    for(j=1; j<tailleBanquise-1; j++)
    {
        for(i=1; i<tailleBanquise-1; i++)
        {
            indice = rand() % 100;
            if((indice < 1) && (banquise[i][j].checkpoint==0) && (etatBanquise[i][j]==1) && (banquise[i][j].occupe==NULL)) // Si on est dans le pourcentage et qu'on est pas sur la case d'arrivée, on peut tenter de crer le marteau
            {
                creationMarteau(banquise, etatBanquise, i, j);
            }
        }
    }
}

void creationMarteau(T_case **banquise, int **etatBanquise, int i, int j)
{
    int x, y;
    int cas = -1;
    int possible=1;
    for(y=j-1; y<=j+1; y++) //Dans cette boucle, on vérifie que les cases autour de l'axe ne soient pas déja prises pour le passage d'une tête de marteau
    {
        for(x=i-1; x<=i+1; x++)
        {
            if((etatBanquise[x][y]==0) || (banquise[x][y].occupe!=NULL))
            {
                possible=0;
            }
        }
    }
    if(possible==1) // Si les cases ne sont pas prises pour le passage d'une tête de marteau, on créer le marteau
    {
        cas = rand() % 4; //On tire un nombre aléatoire pour savoir où on va mettre la tête de marteau

        for(y=j-1; y<=j+1; y++) // On va donc indiquer sur etatBanquise que la place de l'axe et les cases autours sont occupées par le marteau et son passage
        {
            for(x=i-1; x<=i+1; x++)
            {
                etatBanquise[x][y]=cas;
            }
        }

        switch (cas)
        {
            case 0: // Cas où la tête de marteau va être au dessus de l'axe x 0 y -1

                banquise[i][j-1].typeObjet = (T_objet*)(malloc(sizeof(T_objet))); // On initialise la tête de marteau
                banquise[i][j-1].typeObjet->objet = 3;

                banquise[i][j-1].typeObjet->vecteur.dx = 0; // On indique que la tête de marteau ne bouge pas
                banquise[i][j-1].typeObjet->vecteur.dy = 0;

                banquise[i][j-1].typeObjet->position.x = i; // On donne les coordonnées de l'axe du marteau, utile pour plus tard
                banquise[i][j-1].typeObjet->position.y = j;

                banquise[i][j].typeObjet = (T_objet*)(malloc(sizeof(T_objet))); // On initialise l'axe de marteau
                banquise[i][j].typeObjet->objet = 2;

                banquise[i][j].typeObjet->vecteur.dx = 0; // On indique que l'axe de marteau ne bouge pas
                banquise[i][j].typeObjet->vecteur.dy = 0;

                banquise[i][j].typeObjet->position.x = i; // On donne les coordonnées de la tête du marteau, utile pour plus tard
                banquise[i][j].typeObjet->position.y = j-1;

                break;

            case 1: // Cas où la tête de marteau va être a gauche de l'axe x -1 y 0

                banquise[i-1][j].typeObjet = (T_objet*)(malloc(sizeof(T_objet))); // On initialise la tête de marteau
                banquise[i-1][j].typeObjet->objet = 3;

                banquise[i-1][j].typeObjet->vecteur.dx = 0; // On indique que la tête de marteau ne bouge pas
                banquise[i-1][j].typeObjet->vecteur.dy = 0;

                banquise[i-1][j].typeObjet->position.x = i; // On donne les coordonnées de l'axe du marteau, utile pour plus tard
                banquise[i-1][j].typeObjet->position.y = j;

                banquise[i][j].typeObjet = (T_objet*)(malloc(sizeof(T_objet))); // On initialise l'axe de marteau
                banquise[i][j].typeObjet->objet = 2;

                banquise[i][j].typeObjet->vecteur.dx = 0; // On indique que l'axe de marteau ne bouge pas
                banquise[i][j].typeObjet->vecteur.dy = 0;

                banquise[i][j].typeObjet->position.x = i-1; // On donne les coordonnées de la tête du marteau, utile pour plus tard
                banquise[i][j].typeObjet->position.y = j;

                break;

            case 2: // Cas où la tête de marteau va être en dessous de l'axe x 0 y 1
                banquise[i][j+1].typeObjet = (T_objet*)(malloc(sizeof(T_objet))); // On initialise la tête de marteau
                banquise[i][j+1].typeObjet->objet = 3;

                banquise[i][j+1].typeObjet->vecteur.dx = 0; // On indique que la tête de marteau ne bouge pas
                banquise[i][j+1].typeObjet->vecteur.dy = 0;

                banquise[i][j+1].typeObjet->position.x = i; // On donne les coordonnées de l'axe du marteau, utile pour plus tard
                banquise[i][j+1].typeObjet->position.y = j;

                banquise[i][j].typeObjet = (T_objet*)(malloc(sizeof(T_objet))); // On initialise l'axe de marteau
                banquise[i][j].typeObjet->objet = 2;

                banquise[i][j].typeObjet->vecteur.dx = 0; // On indique que l'axe de marteau ne bouge pas
                banquise[i][j].typeObjet->vecteur.dy = 0;

                banquise[i][j].typeObjet->position.x = i; // On donne les coordonnées de la tête du marteau, utile pour plus tard
                banquise[i][j].typeObjet->position.y = j+1;
                break;

            case 3: // Cas où la tête de marteau va être a droite de l'axe x 1 y 0

                banquise[i+1][j].typeObjet = (T_objet*)(malloc(sizeof(T_objet))); // On initialise la tête de marteau
                banquise[i+1][j].typeObjet->objet = 3;

                banquise[i+1][j].typeObjet->vecteur.dx = 0; // On indique que la tête de marteau ne bouge pas
                banquise[i+1][j].typeObjet->vecteur.dy = 0;

                banquise[i+1][j].typeObjet->position.x = i; // On donne les coordonnées de l'axe du marteau, utile pour plus tard
                banquise[i+1][j].typeObjet->position.y = j;

                banquise[i][j].typeObjet = (T_objet*)(malloc(sizeof(T_objet))); // On initialise l'axe de marteau
                banquise[i][j].typeObjet->objet = 2;

                banquise[i][j].typeObjet->vecteur.dx = 0; // On indique que l'axe de marteau ne bouge pas
                banquise[i][j].typeObjet->vecteur.dy = 0;

                banquise[i][j].typeObjet->position.x = i+1; // On donne les coordonnées de la tête du marteau, utile pour plus tard
                banquise[i][j].typeObjet->position.y = j;

                break;

            default :

                printf("\n\nERROR fonction creationMarteau defaut dans les cas\n\n");
        }
    }
}



T_joueur *init_joueur(int nb_joueur) //Creer un tableau de joueur
{
    T_joueur *tab_joueur;
    tab_joueur =(T_joueur *)malloc(sizeof(T_joueur)*nb_joueur);
    for(int i=0 ; i<nb_joueur; i++)
    {
        printf("Nom du joueur %d  : ",i+1);
        scanf("%s",tab_joueur[i].nom);
        tab_joueur[i].representation=i;
        tab_joueur[i].identite=i+1;
        tab_joueur[i].position.x=0; // Pour test
        tab_joueur[i].position.y=0; // Pour test
        tab_joueur[i].direction.dx=0;
        tab_joueur[i].direction.dy=0;
        tab_joueur[i].passeTour=0;
        tab_joueur[i].etat=1;
        int score;
    }
    return tab_joueur;
}

void init_position_joueur(T_case **map,T_joueur *tableau_joueur,int taille_map,int nb_joueur,T_position *position_depart)
{
  for(int i=0;i<nb_joueur;i++)
  {
    switch (i)
    {

      case 0 :
      map[(position_depart->x)-1][position_depart->y].occupe=(T_joueur*)(malloc(sizeof(T_joueur)));
      tableau_joueur[0].position.x=(position_depart->x)-1;
      tableau_joueur[0].position.y=position_depart->y;
      map[(position_depart->x)-1][position_depart->y].occupe=&tableau_joueur[0];
      break;

      case 1 :
      map[(position_depart->x)][position_depart->y-1].occupe=(T_joueur*)(malloc(sizeof(T_joueur)));
      tableau_joueur[1].position.x=position_depart->x;
      tableau_joueur[1].position.y=(position_depart->y)-1;
      map[position_depart->x][(position_depart->y)-1].occupe=&tableau_joueur[1];
      break;

      case 2 :
      map[(position_depart->x)+1][position_depart->y].occupe=(T_joueur*)(malloc(sizeof(T_joueur)));
      tableau_joueur[2].position.x=(position_depart->x)+1;
      tableau_joueur[2].position.y=position_depart->y;
      map[(position_depart->x)+1][position_depart->y].occupe=&tableau_joueur[2];
      break;

      case 3 :
      map[(position_depart->x)][position_depart->y+1].occupe=(T_joueur*)(malloc(sizeof(T_joueur)));
      tableau_joueur[3].position.x=position_depart->x;
      tableau_joueur[3].position.y=(position_depart->y)+1;
      map[position_depart->x][(position_depart->y)+1].occupe=&tableau_joueur[3];
      break;

    }
  }
}
