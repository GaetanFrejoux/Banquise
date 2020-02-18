//INCLUDES

#include "initialisation.h"

//FONCTIONS

int init_nombre_joueur()
{
    int nombre=0;
    do
    {
    printf("\nVeuillez choisir le nombre de joueur entre 1 et 4:  "); //Demande à l'utisateur de rentrer une valeur.
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
        printf("\nVeuillez choisir la taille de la banquise \(minimum 2\):  "); //Demande à l'utisateur de rentrer une valeur.
        scanf("%d",&taille);   // Demande de l'input par l'utilisateur.
    }
    while(taille<2);
    return taille; // retourne la valeur que l'utilisateur a inscrite.
}

T_case **init_banquise(int taille) // Créer la matrice de la banquise et la banquise initiale.
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

int **init_etat_banquise(int taille) // Créer une matrice qui permettra de sauvegarder l'état du sol de la banquise
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

void init_depart_arriver(T_case **map,int taille)
{
    srand(time(NULL));
    int x_dep,x_arr,y_dep,y_arr;
    do
    {
        x_dep=rand()%taille;
        x_arr=rand()%taille;
        y_dep=rand()%taille;
        y_arr=rand()%taille;
    }
    while((map[x_dep][y_dep].etat!=1)||(map[x_arr][y_arr].etat!=1)||((x_dep==x_arr)&&(y_dep==y_arr)));
    map[x_dep][y_dep].checkpoint=1;
    map[x_dep][y_dep].symbole='D';
    map[x_arr][y_arr].checkpoint=1;
    map[x_arr][y_arr].symbole='A';
    return;
}

T_joueur *init_joueur(int nb_joueur)
{
    T_joueur *tab_joueur;
    tab_joueur =(T_joueur *)malloc(sizeof(T_joueur)*nb_joueur);
    for(int i=0 ; i<nb_joueur; i++)
    {
        printf("Nom du premier joueur : ");
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
