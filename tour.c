//INCLUDES

#include "tour.h"

//FONCTIONS

void glaconKiller(T_case **banquise, T_joueur *tableau_joueur, int i, int j, int nombre_joueur)
{
    if((banquise[i][j].typeObjet->objet==0) && (banquise[i][j].occupe!=NULL))
    {
        int joueur;
        for(joueur=0; joueur<nombre_joueur; joueur++)
        {
            if((tableau_joueur[joueur].position.x==i) && (tableau_joueur[joueur].position.y==j)) // On regarde qui est le joueur dont la position correspond à celle du glaçon
            {
                tableau_joueur[joueur].etat=0; // Une fois trouvé, il meurt
                banquise[i][j].occupe=NULL;
                printf("\n\nUn joueur est mort !\n\n");
            }
        }
    }
}

void deplacementJoueur(T_case **banquise, T_joueur *tableau_joueur, int *indice_joueur, int nombre_joueur, int tailleBanquise, int *ptr_nombre_morts)
{
    if(tableau_joueur[*indice_joueur].passeTour==1)
    {
        tableau_joueur[*indice_joueur].passeTour=0;
        printf("\n\nVous passez votre tour car au tour precedent vous etes tombe dans un piege !\n\n");
    }
    else
    {
        T_case nouvelleCase;
        int choix;
        char mouvement;
        do
        {
            printf("\n(z = Haut / q = Gauche / s = Bas / d = Droite) :");
            scanf("%c",&mouvement);
        }while((mouvement!='z') && (mouvement!='q') && (mouvement!='s') && (mouvement!='d'));

        if(mouvement=='z')
        {
            choix=0;
        }
        else if(mouvement=='q')
        {
            choix=1;
        }
        else if(mouvement=='s')
        {
            choix=2;
        }
        else if(mouvement=='d')
        {
           choix=3;
        }
        else
        {
            printf("\n\nERROR variable mouvement dans fonction deplacementJoueur\n\n");
            return;
        }

        switch(choix)
        {
        case 0:// x 0 y -1



            if(tableau_joueur[*indice_joueur].position.y-1<0) // Cas du joueur qui sort de la zone de jeu (plateau de jeu)
            {
                printf("\n\nLe deplacement ne c'est pas fait cas sinon le joueur sort de la zone de jeu\n\n");
            }
            else
            {
                nouvelleCase = banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1];

                if(nouvelleCase.etat==0) // Cas du joueur qui vas dans l'eau
                {
                    printf("\n\nLe joueur est mort en tombant dans l'eau\n\n");
                        banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                        banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                        banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                        tableau_joueur[*indice_joueur].position.y-=1;
                }

                else // Si on passe les deux premiers cas, la prochaine case est une case de banquise
                {
                    if(nouvelleCase.occupe!=NULL) //Cas ou la case de déplacement est déjà occupée par un autre joueur
                    {
                        printf("\n\nLe deplacement ne peut etre realise car une autre joueur occupe la case\n\n");
                    }

                    else if(nouvelleCase.typeObjet==NULL) //Cas ou la case de déplacement est libre
                    {
                        banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                        banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                        banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                        tableau_joueur[*indice_joueur].position.y-=1;
                    }

                    else if(nouvelleCase.typeObjet!=NULL) //Si la case suivante contient un objet
                    {
                        if((nouvelleCase.typeObjet->objet==1) || (nouvelleCase.typeObjet->objet==2) || (nouvelleCase.typeObjet->objet==5)) // Si c'est un rocher, un axe de marteau, ou un ressort, le déplacement ne se fait pas
                        {
                            printf("\n\nLa case est occupe par un objet statique. Le deplacement ne peut etre effectuer\n\n");
                        }

                        else if(nouvelleCase.typeObjet->objet==4) // Si c'est un piège, le prochain tour du joueur est passé
                        {
                            printf("\n\nVous etes sur un piege ! Vous passez votre prochain tour !\n\n");
                            banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].typeObjet=NULL; //On supprime le piège
                            banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe=(T_joueur*)malloc(sizeof(T_joueur)); // On réalise le déplacement
                            banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                            banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                            tableau_joueur[*indice_joueur].position.y-=1;
                            tableau_joueur[*indice_joueur].passeTour=1;

                        }

                        else if(nouvelleCase.typeObjet->objet==0) // Si c'est un glaçon
                        {
                            int casGlacon = numeroCasGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y-1, 0, -1, tailleBanquise); // On regarde son cas
                            if(casGlacon==0) // Si le glaçon ne peux pas bouger, le personnage ne bouge pas
                            {
                                printf("\n\nLe deplacement ne peut se faire cas le glacon sur la prochaine case ne peut se deplacer\n\n");
                            }

                            else if(casGlacon==1) // Si le glaçon peut bouger
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y-1, 0, -1, tailleBanquise);  // On effectue son déplacement


                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe=(T_joueur*)malloc(sizeof(T_joueur));  // Puis celui du joueur
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                                tableau_joueur[*indice_joueur].position.y-=1;
                            }

                            else if(casGlacon==2) // Si le glaçon rencontre une tête de marteau
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y-1, 0, -1, tailleBanquise); // On effectue le déplacement du glaçon pour actionner la rotation du marteau

                                printf("\n\nBravo ! Vous avez active un marteau !\n\n"); // On ne déplace pas le personnage car le glaçon n'a pas bougé
                            }

                            else if(casGlacon==3) // Si le glaçon va rencontrer un piege,
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y-1, 0, -1, tailleBanquise);  // On effectue le déplacement du glaçon dans le piège


                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe=(T_joueur*)malloc(sizeof(T_joueur));  // Puis on déplace le joueur
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                                tableau_joueur[*indice_joueur].position.y-=1;
                            }

                            else if(casGlacon==4)
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y-1, 0, -1, tailleBanquise); // On effectue le déplacement du glaçon

                                glaconKiller(banquise, tableau_joueur, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y, nombre_joueur); // On appel la fonction qui regarde si un glaçon a percuté un joueur et qui le fait mourrir si c'est le cas
                            }

                            else
                            {
                                printf("\n\nERROR variable casGlacon valeur inconnue\n\n");
                            }
                        }

                        else if(nouvelleCase.typeObjet->objet==3)
                        {
                            printf("\n\nCas de la tete de marteau a gerer\n\n");
                        }

                        else
                        {
                            printf("\n\nERROR dans la fonction deplacement joueur dans les cas des objets\n\n");
                        }
                    }
                    else
                    {
                        printf("\n\nERROR cas non pris en charge\n\n");
                    }
                }
            }
        break;
        case 1://x -1 y 0


            if(tableau_joueur[*indice_joueur].position.x-1<0) // Cas du joueur qui sort de la zone de jeu (plateau de jeu)
            {
                printf("\n\nLe deplacement ne c'est pas fait cas sinon le joueur sort de la zone de jeu\n\n");
            }
            else
            {
                nouvelleCase = banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y];


                if(nouvelleCase.etat==0) // Cas du joueur qui vas dans l'eau
                {
                    printf("\n\nLe joueur est mort en tombant dans l'eau\n\n");
                    banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                    banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                    banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                    tableau_joueur[*indice_joueur].position.x-=1;

                }

                else // Si on passe les deux premiers cas, la prochaine case est une case de banquise
                {
                    if(nouvelleCase.occupe!=NULL) //Cas ou la case de déplacement est déjà occupée par un autre joueur
                    {
                        printf("\n\nLe deplacement ne peut etre realise car une autre joueur occupe la case\n\n");
                    }

                    else if(nouvelleCase.typeObjet==NULL) //Cas ou la case de déplacement est libre
                    {
                        banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                        banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                        banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                        tableau_joueur[*indice_joueur].position.x-=1;
                    }

                    else if(nouvelleCase.typeObjet!=NULL) //Si la case suivante contient un objet
                    {
                        if((nouvelleCase.typeObjet->objet==1) || (nouvelleCase.typeObjet->objet==2) || (nouvelleCase.typeObjet->objet==5)) // Si c'est un rocher, un axe de marteau, ou un ressort, le déplacement ne se fait pas
                        {
                            printf("\n\nLa case est occupe par un objet statique. Le deplacement ne peut etre effectuer\n\n");
                        }

                        else if(nouvelleCase.typeObjet->objet==4) // Si c'est un piège, le prochain tour du joueur est passé
                        {
                            printf("\n\nVous etes sur un piege ! Vous passez votre prochain tour !\n\n");
                            banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y].typeObjet=NULL; //On supprime le piège
                            banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur)); // On réalise le déplacement
                            banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                            banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                            tableau_joueur[*indice_joueur].position.x-=1;
                            tableau_joueur[*indice_joueur].passeTour=1;

                        }

                        else if(nouvelleCase.typeObjet->objet==0) // Si c'est un glaçon
                        {
                            int casGlacon = numeroCasGlacon(banquise, tableau_joueur[*indice_joueur].position.x-1, tableau_joueur[*indice_joueur].position.y, -1, 0, tailleBanquise); // On regarde son cas
                            if(casGlacon==0) // Si le glaçon ne peux pas bouger, le personnage ne bouge pas
                            {
                                printf("\n\nLe deplacement ne peut se faire cas le glacon sur la prochaine case ne peut se deplacer\n\n");
                            }

                            else if(casGlacon==1) // Si le glaçon peut bouger
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x-1, tableau_joueur[*indice_joueur].position.y, -1, 0, tailleBanquise);  // On effectue son déplacement


                                banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));  // Puis celui du joueur
                                banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                                tableau_joueur[*indice_joueur].position.x-=1;
                            }

                            else if(casGlacon==2) // Si le glaçon rencontre une tête de marteau
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x-1, tableau_joueur[*indice_joueur].position.y, -1, 0, tailleBanquise); // On effectue le déplacement du glaçon pour actionner la rotation du marteau

                                printf("\n\nBravo ! Vous avez active un marteau !\n\n"); // On ne déplace pas le personnage car le glaçon n'a pas bougé
                            }

                            else if(casGlacon==3) // Si le glaçon va rencontrer un piege,
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x-1, tableau_joueur[*indice_joueur].position.y, -1, 0, tailleBanquise);  // On effectue le déplacement du glaçon dans le piège


                                banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));  // Puis on déplace le joueur
                                banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                                tableau_joueur[*indice_joueur].position.x-=1;
                            }

                            else if(casGlacon==4)
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x-1, tableau_joueur[*indice_joueur].position.y, -1, 0, tailleBanquise); // On effectue le déplacement du glaçon

                                glaconKiller(banquise, tableau_joueur, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y, nombre_joueur); // On appel la fonction qui regarde si un glaçon a percuté un joueur et qui le fait mourrir si c'est le cas
                            }

                            else
                            {
                                printf("\n\nERROR variable casGlacon valeur inconnue\n\n");
                            }
                        }

                        else if(nouvelleCase.typeObjet->objet==3)
                        {
                            printf("\n\nCas de la tete de marteau a gerer\n\n");
                        }

                        else
                        {
                            printf("\n\nERROR dans la fonction deplacement joueur dans les cas des objets\n\n");
                        }
                    }
                    else
                    {
                        printf("\n\nERROR cas non pris en charge\n\n");
                    }
                }
            }

        break;
        case 2://x 0 y 1


            if(tableau_joueur[*indice_joueur].position.y+1>=tailleBanquise) // Cas du joueur qui sort de la zone de jeu (plateau de jeu)
            {
                printf("\n\nLe deplacement ne c'est pas fait cas sinon le joueur sort de la zone de jeu\n\n");
            }
            else
            {
                nouvelleCase = banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1];

                if(nouvelleCase.etat==0) // Cas du joueur qui vas dans l'eau
                {
                    printf("\n\nLe joueur est mort en tombant dans l'eau\n\n");
                        banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                        banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                        banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                        tableau_joueur[*indice_joueur].position.y+=1;
                }

                else // Si on passe les deux premiers cas, la prochaine case est une case de banquise
                {
                    if(nouvelleCase.occupe!=NULL) //Cas ou la case de déplacement est déjà occupée par un autre joueur
                    {
                        printf("\n\nLe deplacement ne peut etre realise car une autre joueur occupe la case\n\n");
                    }

                    else if(nouvelleCase.typeObjet==NULL) //Cas ou la case de déplacement est libre
                    {
                        banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                        banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                        banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                        tableau_joueur[*indice_joueur].position.y+=1;
                    }

                    else if(nouvelleCase.typeObjet!=NULL) //Si la case suivante contient un objet
                    {
                        if((nouvelleCase.typeObjet->objet==1) || (nouvelleCase.typeObjet->objet==2) || (nouvelleCase.typeObjet->objet==5)) // Si c'est un rocher, un axe de marteau, ou un ressort, le déplacement ne se fait pas
                        {
                            printf("\n\nLa case est occupe par un objet statique. Le deplacement ne peut etre effectuer\n\n");
                        }

                        else if(nouvelleCase.typeObjet->objet==4) // Si c'est un piège, le prochain tour du joueur est passé
                        {
                            printf("\n\nVous etes sur un piege ! Vous passez votre prochain tour !\n\n");
                            banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].typeObjet=NULL; //On supprime le piège
                            banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe=(T_joueur*)malloc(sizeof(T_joueur)); // On réalise le déplacement
                            banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                            banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                            tableau_joueur[*indice_joueur].position.y+=1;
                            tableau_joueur[*indice_joueur].passeTour=1;

                        }

                        else if(nouvelleCase.typeObjet->objet==0) // Si c'est un glaçon
                        {
                            int casGlacon = numeroCasGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y+1, 0, 1, tailleBanquise); // On regarde son cas
                            if(casGlacon==0) // Si le glaçon ne peux pas bouger, le personnage ne bouge pas
                            {
                                printf("\n\nLe deplacement ne peut se faire cas le glacon sur la prochaine case ne peut se deplacer\n\n");
                            }

                            else if(casGlacon==1) // Si le glaçon peut bouger
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y+1, 0, 1, tailleBanquise);  // On effectue son déplacement


                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe=(T_joueur*)malloc(sizeof(T_joueur));  // Puis celui du joueur
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                                tableau_joueur[*indice_joueur].position.y+=1;
                            }

                            else if(casGlacon==2) // Si le glaçon rencontre une tête de marteau
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y+1, 0, 1, tailleBanquise); // On effectue le déplacement du glaçon pour actionner la rotation du marteau

                                printf("\n\nBravo ! Vous avez active un marteau !\n\n"); // On ne déplace pas le personnage car le glaçon n'a pas bougé
                            }

                            else if(casGlacon==3) // Si le glaçon va rencontrer un piege,
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y+1, 0, 1, tailleBanquise);  // On effectue le déplacement du glaçon dans le piège


                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe=(T_joueur*)malloc(sizeof(T_joueur));  // Puis on déplace le joueur
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                                tableau_joueur[*indice_joueur].position.y+=1;
                            }

                            else if(casGlacon==4)
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y+1, 0, 1, tailleBanquise); // On effectue le déplacement du glaçon

                                glaconKiller(banquise, tableau_joueur, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y, nombre_joueur); // On appel la fonction qui regarde si un glaçon a percuté un joueur et qui le fait mourrir si c'est le cas
                            }

                            else
                            {
                                printf("\n\nERROR variable casGlacon valeur inconnue\n\n");
                            }
                        }

                        else if(nouvelleCase.typeObjet->objet==3)
                        {
                            printf("\n\nCas de la tete de marteau a gerer\n\n");
                        }

                        else
                        {
                            printf("\n\nERROR dans la fonction deplacement joueur dans les cas des objets\n\n");
                        }
                    }
                    else
                    {
                        printf("\n\nERROR cas non pris en charge\n\n");
                    }
                }
            }
        break;
        case 3://x 1 y 0


            if(tableau_joueur[*indice_joueur].position.x+1>=tailleBanquise) // Cas du joueur qui sort de la zone de jeu (plateau de jeu)
            {
                printf("\n\nLe deplacement ne c'est pas fait cas sinon le joueur sort de la zone de jeu\n\n");
            }
            else
            {
                nouvelleCase = banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y];

                if(nouvelleCase.etat==0) // Cas du joueur qui vas dans l'eau
                {
                    printf("\n\nLe joueur est mort en tombant dans l'eau\n\n");
                        banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                        banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                        banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                        tableau_joueur[*indice_joueur].position.x+=1;
                }

                else // Si on passe les deux premiers cas, la prochaine case est une case de banquise
                {
                    if(nouvelleCase.occupe!=NULL) //Cas ou la case de déplacement est déjà occupée par un autre joueur
                    {
                        printf("\n\nLe deplacement ne peut etre realise car une autre joueur occupe la case\n\n");
                    }

                    else if(nouvelleCase.typeObjet==NULL) //Cas ou la case de déplacement est libre
                    {
                        banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));
                        banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                        banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                        tableau_joueur[*indice_joueur].position.x+=1;
                    }

                    else if(nouvelleCase.typeObjet!=NULL) //Si la case suivante contient un objet
                    {
                        if((nouvelleCase.typeObjet->objet==1) || (nouvelleCase.typeObjet->objet==2) || (nouvelleCase.typeObjet->objet==5)) // Si c'est un rocher, un axe de marteau, ou un ressort, le déplacement ne se fait pas
                        {
                            printf("\n\nLa case est occupe par un objet statique. Le deplacement ne peut etre effectuer\n\n");
                        }

                        else if(nouvelleCase.typeObjet->objet==4) // Si c'est un piège, le prochain tour du joueur est passé
                        {
                            printf("\n\nVous etes sur un piege ! Vous passez votre prochain tour !\n\n");
                            banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].typeObjet=NULL; //On supprime le piège
                            banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur)); // On réalise le déplacement
                            banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                            banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                            tableau_joueur[*indice_joueur].position.x+=1;
                            tableau_joueur[*indice_joueur].passeTour=1;

                        }

                        else if(nouvelleCase.typeObjet->objet==0) // Si c'est un glaçon
                        {
                            int casGlacon = numeroCasGlacon(banquise, tableau_joueur[*indice_joueur].position.x+1, tableau_joueur[*indice_joueur].position.y, 1, 0, tailleBanquise); // On regarde son cas
                            if(casGlacon==0) // Si le glaçon ne peux pas bouger, le personnage ne bouge pas
                            {
                                printf("\n\nLe deplacement ne peut se faire cas le glacon sur la prochaine case ne peut se deplacer\n\n");
                            }

                            else if(casGlacon==1) // Si le glaçon peut bouger
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x+1, tableau_joueur[*indice_joueur].position.y, 1, 0, tailleBanquise);  // On effectue son déplacement


                                banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));  // Puis celui du joueur
                                banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                                tableau_joueur[*indice_joueur].position.x+=1;
                            }

                            else if(casGlacon==2) // Si le glaçon rencontre une tête de marteau
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x+1, tableau_joueur[*indice_joueur].position.y, 1, 0, tailleBanquise); // On effectue le déplacement du glaçon pour actionner la rotation du marteau

                                printf("\n\nBravo ! Vous avez active un marteau !\n\n"); // On ne déplace pas le personnage car le glaçon n'a pas bougé
                            }

                            else if(casGlacon==3) // Si le glaçon va rencontrer un piege,
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x+1, tableau_joueur[*indice_joueur].position.y, 1, 0, tailleBanquise);  // On effectue le déplacement du glaçon dans le piège


                                banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));  // Puis on déplace le joueur
                                banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                                tableau_joueur[*indice_joueur].position.x+=1;
                            }

                            else if(casGlacon==4)
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x+1, tableau_joueur[*indice_joueur].position.y, 1, 0, tailleBanquise); // On effectue le déplacement du glaçon

                                glaconKiller(banquise, tableau_joueur, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y, nombre_joueur); // On appel la fonction qui regarde si un glaçon a percuté un joueur et qui le fait mourrir si c'est le cas
                            }

                            else
                            {
                                printf("\n\nERROR variable casGlacon valeur inconnue\n\n");
                            }
                        }

                        else if(nouvelleCase.typeObjet->objet==3)
                        {
                            printf("\n\nCas de la tete de marteau a gerer\n\n");
                        }

                        else
                        {
                            printf("\n\nERROR dans la fonction deplacement joueur dans les cas des objets\n\n");
                        }
                    }
                    else
                    {
                        printf("\n\nERROR cas non pris en charge\n\n");
                    }
                }
            }
        break;
        default :
            printf("\n\nERROR defaut de cas dans la fonction deplacementJoueur\n\n");
            return;
        }
    }
    printf("\n\n\n\nVoila l'indice dans deplacement joueur : %d",*indice_joueur);
    printf("\n\n\n\nVoila l'indice dans deplacement joueur : %d",*indice_joueur);
    printf("\n\n\n\nVoila l'indice dans deplacement joueur : %d",*indice_joueur);
    printf("\n\n\n\nVoila l'indice dans deplacement joueur : %d",*indice_joueur);
    printf("\n\n\n\nVoila l'indice dans deplacement joueur : %d",*indice_joueur);
    printf("\n\n\n\nVoila l'indice dans deplacement joueur : %d",*indice_joueur);
    printf("\n\n\n\nVoila l'indice dans deplacement joueur : %d",*indice_joueur);

}

int qui_est_mort(T_case **banquise,T_joueur *tableau_joueur,int nombre_joueur,int *ptr_nombre_morts)
{
    for(int i=0;i<nombre_joueur;i++)
    {
        if(tableau_joueur[i].etat==1)
        {
            if(banquise[tableau_joueur[i].position.x][tableau_joueur[i].position.y].etat==0)
            {
                tableau_joueur[i].etat=0;
                *ptr_nombre_morts= *ptr_nombre_morts+1;
                printf("Nombre de mort : %d", *ptr_nombre_morts);
            }
        }
    }
    if(*ptr_nombre_morts==nombre_joueur)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void joueur_vivant(T_case **banquise,T_joueur *tableau_joueur,int* indice_joueur, int nombre_joueur)
{
    *indice_joueur=(*indice_joueur+1)%nombre_joueur;
    int compteur=0;
    while(compteur<nombre_joueur-1)
    {
        if((tableau_joueur[*indice_joueur].etat)==0)
        {
            *indice_joueur = (*indice_joueur+1)%nombre_joueur;
        }
        compteur++;

        printf("\n\n\n\nnique ta mere: %d",*indice_joueur);
    }
}
T_case case_adjacente(T_case **banquise,T_joueur *tableau_joueur,int* indice_joueur,int tailleBanquise,int x,int y)
{
    int pos_x,pos_y;
    pos_x=tableau_joueur[*indice_joueur].position.x+x;
    pos_y=tableau_joueur[*indice_joueur].position.y+y;
    if(pos_x>=tailleBanquise || pos_x<0 || pos_y>=tailleBanquise || pos_y<0 )
        return banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y];
    else
        return banquise[pos_x][pos_y];
}
