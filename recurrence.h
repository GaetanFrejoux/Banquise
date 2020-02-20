#ifndef RECURRENCE_H_INCLUDED
#define RECURRENCE_H_INCLUDED

//INCLUDES

#include "struct.h"
#include "banquise.h"
#include "initialisation.h"

//PROTOTYPES

T_file creerFile();
void enfiler(T_file *F, int i, int j);
T_file creerFile();
int dejaVu(T_file *chemin, int i, int j);
int finPossible(T_case **banquise, int i, int j, int tailleBanquise);
int finPossibleAuxiliaire(T_case **banquise, T_file *chemin, int tailleBanquise, int i, int j);

#endif // RECURRENCE_H_INCLUDED
