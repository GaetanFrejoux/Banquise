//INCLUDES

#include "initialisation.h"

//FONCTIONS

int init_nombre_joueur()
{
    int nombre=0;
    do
    {
    printf("\nVeuillez choisir le nombre de joueur entre 1 et 4:  "); //Demande � l'utisateur de rentrer une valeur.
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
        printf("\nVeuillez choisir la taille de la banquise (minimum 2):  "); //Demande � l'utisateur de rentrer une valeur.
        scanf("%d",&taille);   // Demande de l'input par l'utilisateur.
    }
    while(taille<2);
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
        for (j=0;j<taille;j++)
        {
            banquise[i][j].checkpoint=0;
            banquise[i][j].etat=1;
            banquise[i][j].occupe=NULL;
            banquise[i][j].symbole='V';
            banquise[i][j].typeObjet=NULL;
        }
    }
    return banquise;
}

int **init_etat_banquise(int taille) // Cr�er une matrice qui permettra de sauvegarder l'�tat du sol de la banquise
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
    while((map[depart.x][depart.y].etat!=1)||(map[arrive.x][arrive.y].etat!=1)||((depart.x==arrive.x)&&(depart.y==arrive.y)));
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


void apparition_glacons(T_case **banquise, int taille) //Place des glacons de manière aléatoire sur la banquise.
{

  //VARIABLES


  int i,j, pourcentageApparitionGlacon=0;
  srand(time(NULL));

  //CODE

  for(i=0; i<taille; i++) // On parcours la banquise
  {
      for(j=0;j<taille; j++)
      {
        T_objet nouveau_rocher;
        pourcentageApparitionGlacon = rand() % 100; //A chaque case, on tire un nombre au sort pour savoir si l'on pose un glacon ou non
        if((pourcentageApparitionGlacon<10) && (banquise[i][j].occupe==NULL) && (banquise[i][j].typeObjet==NULL))
        /*
        Ici, si le nombre passe en dessous de 10 %,
        et que la case n'est pas occupée par un joueur ou un objet,
        on créer le glaçon
        */
        {//On créer un nouvel objet pour que le pointeur objet de la case puisse directement pointer sur l'objet en question
          nouveau_rocher.objet=0;  // On initialise le glaçon
          nouveau_rocher.position.x=i;
          nouveau_rocher.position.y=j;
          nouveau_rocher.vecteur.dx=0;
          nouveau_rocher.vecteur.dy=0;
          T_objet *ptr_nouveau_rocher=&nouveau_rocher;
          banquise[i][j].typeObjet=ptr_nouveau_rocher;
        }
        //Le glaçon est créer
      }

  }

  //RETURN


  return;
}


T_joueur *init_joueur(int nb_joueur) //Creer un tableau de joueur avec 4 maximum
{
    T_joueur *tab_joueur;
    tab_joueur =(T_joueur *)malloc(sizeof(T_joueur)*nb_joueur);
    for(int i=0 ; i<nb_joueur; i++)
    {
        printf("Nom du joueur %d  : ",i+1);
        scanf("%s",&tab_joueur->nom);
        tab_joueur->representation=i;
        tab_joueur->identite=i+1;
        tab_joueur->position.x=0;
        tab_joueur->position.y=0;
        tab_joueur->direction.dx=-1;
        tab_joueur->direction.dy=-1;
        int score;
    }
    return tab_joueur;
}
void init_position_joueur(T_case **map,T_joueur *tableau_joueur,int taille_map,int nb_joueur,T_position *position_depart)
{
      tableau_joueur[0].position.x=position_depart->x-1;
      tableau_joueur[0].position.y=position_depart->y;
      map[position_depart->x-1][position_depart->y].occupe=&tableau_joueur[0];
      tableau_joueur[1].position.x=position_depart->x;
      tableau_joueur[1].position.y=position_depart->y-1;
      map[position_depart->x][position_depart->y+1].occupe=&tableau_joueur[1];
      tableau_joueur[2].position.x=position_depart->x+1;
      tableau_joueur[2].position.y=position_depart->y;
      map[position_depart->x+1][position_depart->y].occupe=&tableau_joueur[2];
      tableau_joueur[3].position.x=position_depart->x;
      tableau_joueur[3].position.y=position_depart->y+1;
      map[position_depart->x][position_depart->y-1].occupe=&tableau_joueur[3];



  /*
    tableau_joueur[0].position.x=position_depart->x;
    tableau_joueur[0].position.y=position_depart->y;
    map[position_depart->x][position_depart->y].occupe=&tableau_joueur[0];
  */
}
