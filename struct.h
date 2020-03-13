#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

//INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

//ENUMERATION

typedef enum {eau, banquise} T_surface; // Type qui d�fini la surface du plateau : si c'est une limite de jeu, une case d'eau o� rien ne peut se trouver ou une case de glace
typedef enum {rien_dir, depart, arrive} T_direction; // D�fini si la case est une case de d�part, de fin ou ni l'un, ni l'autre.
typedef enum {glacon_obj=0, rocher=1, marteauAxe=2, marteauTete=3, piege=4, ressort=5 } T_typeObjet; //D�fini le type d'objet se trouvant sur une case de glace.
typedef enum {rouge, vert, bleu, jaune} T_couleur; //D�fini les couleurs que peuvent prendre les personnages
typedef enum {mort,vivant} T_etat; //D�fini si le joueur est vivant ou mort.

//STRUCTURES

typedef struct
{
    int x;
    int y;
}T_position; //D�fini une position

typedef struct
{
    int dx;
    int dy;
}T_vecteur; //D�fini un vecteur

typedef struct
{
    T_typeObjet objet;
    T_position position;
    T_vecteur vecteur;
}T_objet; // D�fini les diff�rents objets

typedef struct
{
    char nom[20];
    T_couleur representation;
    int identite;
    T_position position;
    T_vecteur direction;
    int score;
    int passeTour; // Si passeTour est à 0, le joueur peut jouer son tour normalement, si il est à 1, il doit passer son tour (piège)
    T_etat etat;
}T_joueur;  // D�fini un joueur

typedef struct
{
    T_surface etat;
    T_joueur *occupe;
    T_objet *typeObjet;
    T_direction checkpoint;
    char symbole;
}T_case;  //D�fini tout ce qui compose une case


#endif // STRUCT_H_INCLUDED
