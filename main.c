//INCLUDES

#include "banquise.h"
#include "initialisation.h"

int main()
{
    //VARIABLES
    int n=0;
    n = init_taille();

    //INITIALISATION

    T_case **banquise = init_banquise(n);
    int **etatBanquise = init_etat_banquise(n);
    affichageBanquise(banquise, n);
    affichageEtatBanquise(etatBanquise, n);

    //CODE

    fonteDesGlaces(banquise, etatBanquise, n);

    return 0;
}
