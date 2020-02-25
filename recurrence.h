#ifndef RECURRENCE_H_INCLUDED
#define RECURRENCE_H_INCLUDED

//INCLUDES

#include "struct.h"
#include "banquise.h"
#include "initialisation.h"

//PROTOTYPES

int **init_passage(int tailleBanquise);
void remiseAZeroPassage(int **passage, int tailleBanquise);
void finPossible(T_case **banquise, int tailleBanquise, int **passage, int i, int j);
int aijeLeDroit(int **passage, T_case **banquise, int i, int j);
int finPossibleAuxiliaire(int **passage, T_case **banquise, int i, int j, int tailleBanquise);

/*T_file creerFile();
void enfiler(T_file *F, int i, int j);
T_file creerFile();
int dejaVu(T_file *chemin, int i, int j);
int finPossible(T_case **banquise, int i, int j, int tailleBanquise);
int finPossibleAuxiliaire(T_case **banquise, T_file *chemin, int tailleBanquise, int i, int j);*/

#endif // RECURRENCE_H_INCLUDED
