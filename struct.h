#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

//INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

//ENUMERATION

typedef enum {eau, banquise} T_surface; // Type qui défini la surface du plateau : si c'est une limite de jeu, une case d'eau où rien ne peut se trouver ou une case de glace
typedef enum {rien_dir, depart, arrive} T_direction; // Défini si la case est une case de départ, de fin ou ni l'un, ni l'autre.
typedef enum {glacon_obj, rocher, marteauAxe, marteauTete, piege} T_typeObjet; //Défini le type d'objet se trouvant sur une case de glace.
typedef enum {rouge, vert, bleu, jaune} T_couleur; //Défini les couleurs que peuvent prendre les personnages

//STRUCTURES

typedef struct
{
    int x;
    int y;
}T_position; //Défini une position

typedef struct
{
    int dx;
    int dy;
}T_vecteur; //Défini un vecteur

typedef struct
{
    T_typeObjet objet;
    T_position position;
    T_vecteur vecteur;
}T_objet; // Défini les différents objets

typedef struct
{
    char nom[20];
    T_couleur representation;
    int identite;
    T_position position;
    T_vecteur direction;
    int score;
}T_joueur;  // Défini un joueur

typedef struct
{
    T_surface etat;
    T_joueur *occupe;
    T_objet *typeObjet;
    T_direction checkpoint;
    char symbole;
}T_case;  //Défini tout ce qui compose une case





#endif // STRUCT_H_INCLUDED
