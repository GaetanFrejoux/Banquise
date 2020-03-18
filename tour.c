//INCLUDES

#include "tour.h"

//FONCTIONS
//fonction qui fait mourir le joueur
void mortJoueur(T_case **banquise, T_joueur *tableau_joueur, int numeroJoueur)
{
    tableau_joueur[numeroJoueur].etat=0;
    banquise[tableau_joueur[numeroJoueur].position.x][tableau_joueur[numeroJoueur].position.y].occupe=NULL;
}
//fonction qui tue le joueur si un glacon l'ecrase
void glaconKiller(T_case **banquise, T_joueur *tableau_joueur, int i, int j, int nombre_joueur)
{
    if(banquise[i][j].typeObjet!=NULL)
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
}
//fonction qui permet de déplacer le joueur
void deplacementJoueur(T_case **banquise, T_joueur *tableau_joueur, int *indice_joueur, int nombre_joueur, int tailleBanquise)
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
        //demande le deplacement au joueur
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
                    mortJoueur(banquise, tableau_joueur, *indice_joueur);
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
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y-1, 0, -1, tailleBanquise, tableau_joueur, nombre_joueur);  // On effectue son déplacement


                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe=(T_joueur*)malloc(sizeof(T_joueur));  // Puis celui du joueur
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                                tableau_joueur[*indice_joueur].position.y-=1;
                            }

                            else if(casGlacon==2) // Si le glaçon rencontre une tête de marteau
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y-1, 0, -1, tailleBanquise, tableau_joueur, nombre_joueur); // On effectue le déplacement du glaçon pour actionner la rotation du marteau

                                printf("\n\nBravo ! Vous avez active un marteau !\n\n"); // On ne déplace pas le personnage car le glaçon n'a pas bougé
                            }

                            else if(casGlacon==3) // Si le glaçon va rencontrer un piege,
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y-1, 0, -1, tailleBanquise, tableau_joueur, nombre_joueur);  // On effectue le déplacement du glaçon dans le piège


                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe=(T_joueur*)malloc(sizeof(T_joueur));  // Puis on déplace le joueur
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-1].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                                tableau_joueur[*indice_joueur].position.y-=1;
                            }

                            else if(casGlacon==4)
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y-1, 0, -1, tailleBanquise, tableau_joueur, nombre_joueur); // On effectue le déplacement du glaçon

                                glaconKiller(banquise, tableau_joueur, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y, nombre_joueur); // On appel la fonction qui regarde si un glaçon a percuté un joueur et qui le fait mourrir si c'est le cas
                            }

                            else
                            {
                                printf("\n\nERROR variable casGlacon valeur inconnue\n\n");
                            }
                        }

                        else if(nouvelleCase.typeObjet->objet==3)
                        {
                            if(banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-2].typeObjet!=NULL)
                            {
                                if(banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y-2].typeObjet->objet==2)
                                {
                                    printf("\n\nLe marteau ne peut pas bouger cas vous êtes dans l'axe\n\n");
                                }
                                else
                                {
                                    deplacementMarteau(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y-1, 0, -1, tailleBanquise, 3, tableau_joueur, nombre_joueur);
                                }
                            }
                            else
                            {
                                deplacementMarteau(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y-1, 0, -1, tailleBanquise, 3, tableau_joueur, nombre_joueur);
                            }
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
                    mortJoueur(banquise, tableau_joueur, *indice_joueur);
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
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x-1, tableau_joueur[*indice_joueur].position.y, -1, 0, tailleBanquise, tableau_joueur, nombre_joueur);  // On effectue son déplacement


                                banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));  // Puis celui du joueur
                                banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                                tableau_joueur[*indice_joueur].position.x-=1;
                            }

                            else if(casGlacon==2) // Si le glaçon rencontre une tête de marteau
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x-1, tableau_joueur[*indice_joueur].position.y, -1, 0, tailleBanquise, tableau_joueur, nombre_joueur); // On effectue le déplacement du glaçon pour actionner la rotation du marteau

                                printf("\n\nBravo ! Vous avez active un marteau !\n\n"); // On ne déplace pas le personnage car le glaçon n'a pas bougé
                            }

                            else if(casGlacon==3) // Si le glaçon va rencontrer un piege,
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x-1, tableau_joueur[*indice_joueur].position.y, -1, 0, tailleBanquise, tableau_joueur, nombre_joueur);  // On effectue le déplacement du glaçon dans le piège


                                banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));  // Puis on déplace le joueur
                                banquise[tableau_joueur[*indice_joueur].position.x-1][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                                tableau_joueur[*indice_joueur].position.x-=1;
                            }

                            else if(casGlacon==4)
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x-1, tableau_joueur[*indice_joueur].position.y, -1, 0, tailleBanquise, tableau_joueur, nombre_joueur); // On effectue le déplacement du glaçon

                                glaconKiller(banquise, tableau_joueur, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y, nombre_joueur); // On appel la fonction qui regarde si un glaçon a percuté un joueur et qui le fait mourrir si c'est le cas
                            }

                            else
                            {
                                printf("\n\nERROR variable casGlacon valeur inconnue\n\n");
                            }
                        }

                        else if(nouvelleCase.typeObjet->objet==3)
                        {
                            if(banquise[tableau_joueur[*indice_joueur].position.x-2][tableau_joueur[*indice_joueur].position.y].typeObjet!=NULL)
                            {
                                if(banquise[tableau_joueur[*indice_joueur].position.x-2][tableau_joueur[*indice_joueur].position.y].typeObjet->objet==2)
                                {
                                    printf("\n\nLe marteau ne peut pas bouger cas vous êtes dans l'axe\n\n");
                                }
                                else
                                {
                                    deplacementMarteau(banquise, tableau_joueur[*indice_joueur].position.x-1, tableau_joueur[*indice_joueur].position.y, -1, 0, tailleBanquise, 3, tableau_joueur, nombre_joueur);
                                }
                            }
                            else
                            {
                                deplacementMarteau(banquise, tableau_joueur[*indice_joueur].position.x-1, tableau_joueur[*indice_joueur].position.y, -1, 0, tailleBanquise, 3, tableau_joueur, nombre_joueur);
                            }
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
                    mortJoueur(banquise, tableau_joueur, *indice_joueur);
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
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y+1, 0, 1, tailleBanquise, tableau_joueur, nombre_joueur);  // On effectue son déplacement


                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe=(T_joueur*)malloc(sizeof(T_joueur));  // Puis celui du joueur
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                                tableau_joueur[*indice_joueur].position.y+=1;
                            }

                            else if(casGlacon==2) // Si le glaçon rencontre une tête de marteau
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y+1, 0, 1, tailleBanquise, tableau_joueur, nombre_joueur); // On effectue le déplacement du glaçon pour actionner la rotation du marteau

                                printf("\n\nBravo ! Vous avez active un marteau !\n\n"); // On ne déplace pas le personnage car le glaçon n'a pas bougé
                            }

                            else if(casGlacon==3) // Si le glaçon va rencontrer un piege,
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y+1, 0, 1, tailleBanquise, tableau_joueur, nombre_joueur);  // On effectue le déplacement du glaçon dans le piège


                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe=(T_joueur*)malloc(sizeof(T_joueur));  // Puis on déplace le joueur
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+1].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                                tableau_joueur[*indice_joueur].position.y+=1;
                            }

                            else if(casGlacon==4)
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y+1, 0, 1, tailleBanquise, tableau_joueur, nombre_joueur); // On effectue le déplacement du glaçon

                                glaconKiller(banquise, tableau_joueur, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y, nombre_joueur); // On appel la fonction qui regarde si un glaçon a percuté un joueur et qui le fait mourrir si c'est le cas
                            }

                            else
                            {
                                printf("\n\nERROR variable casGlacon valeur inconnue\n\n");
                            }
                        }

                        else if(nouvelleCase.typeObjet->objet==3)
                        {
                            if(banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+2].typeObjet!=NULL)
                            {
                                if(banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y+2].typeObjet->objet==2)
                                {
                                    printf("\n\nLe marteau ne peut pas bouger cas vous êtes dans l'axe\n\n");
                                }
                                else
                                {
                                    deplacementMarteau(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y+1, 0, 1, tailleBanquise, 3, tableau_joueur, nombre_joueur);
                                }
                            }
                            else
                            {
                                deplacementMarteau(banquise, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y+1, 0, 1, tailleBanquise, 3, tableau_joueur, nombre_joueur);
                            }
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
                    mortJoueur(banquise, tableau_joueur, *indice_joueur);
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
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x+1, tableau_joueur[*indice_joueur].position.y, 1, 0, tailleBanquise, tableau_joueur, nombre_joueur);  // On effectue son déplacement


                                banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));  // Puis celui du joueur
                                banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                                tableau_joueur[*indice_joueur].position.x+=1;
                            }

                            else if(casGlacon==2) // Si le glaçon rencontre une tête de marteau
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x+1, tableau_joueur[*indice_joueur].position.y, 1, 0, tailleBanquise, tableau_joueur, nombre_joueur); // On effectue le déplacement du glaçon pour actionner la rotation du marteau

                                printf("\n\nBravo ! Vous avez active un marteau !\n\n"); // On ne déplace pas le personnage car le glaçon n'a pas bougé
                            }

                            else if(casGlacon==3) // Si le glaçon va rencontrer un piege,
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x+1, tableau_joueur[*indice_joueur].position.y, 1, 0, tailleBanquise, tableau_joueur, nombre_joueur);  // On effectue le déplacement du glaçon dans le piège


                                banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe=(T_joueur*)malloc(sizeof(T_joueur));  // Puis on déplace le joueur
                                banquise[tableau_joueur[*indice_joueur].position.x+1][tableau_joueur[*indice_joueur].position.y].occupe=banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe;
                                banquise[tableau_joueur[*indice_joueur].position.x][tableau_joueur[*indice_joueur].position.y].occupe=NULL;
                                tableau_joueur[*indice_joueur].position.x+=1;
                            }

                            else if(casGlacon==4)
                            {
                                deplacementGlacon(banquise, tableau_joueur[*indice_joueur].position.x+1, tableau_joueur[*indice_joueur].position.y, 1, 0, tailleBanquise, tableau_joueur, nombre_joueur); // On effectue le déplacement du glaçon

                                glaconKiller(banquise, tableau_joueur, tableau_joueur[*indice_joueur].position.x, tableau_joueur[*indice_joueur].position.y, nombre_joueur); // On appel la fonction qui regarde si un glaçon a percuté un joueur et qui le fait mourrir si c'est le cas
                            }

                            else
                            {
                                printf("\n\nERROR variable casGlacon valeur inconnue\n\n");
                            }
                        }

                        else if(nouvelleCase.typeObjet->objet==3)
                        {
                            if(banquise[tableau_joueur[*indice_joueur].position.x+2][tableau_joueur[*indice_joueur].position.y].typeObjet!=NULL)
                            {
                                if(banquise[tableau_joueur[*indice_joueur].position.x+2][tableau_joueur[*indice_joueur].position.y].typeObjet->objet==2)
                                {
                                    printf("\n\nLe marteau ne peut pas bouger cas vous êtes dans l'axe\n\n");
                                }
                                else
                                {
                                    deplacementMarteau(banquise, tableau_joueur[*indice_joueur].position.x+1, tableau_joueur[*indice_joueur].position.y, 1, 0, tailleBanquise, 3, tableau_joueur, nombre_joueur);
                                }
                            }
                            else
                            {
                                deplacementMarteau(banquise, tableau_joueur[*indice_joueur].position.x+1, tableau_joueur[*indice_joueur].position.y, 1, 0, tailleBanquise, 3, tableau_joueur, nombre_joueur);
                            }
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
}
//fonction qui test qui est mort a la fin de chaque tour
int qui_est_mort(T_case **banquise,T_joueur *tableau_joueur,int nombre_joueur)
{   int compteur_vivant=0;
    for(int i=0;i<nombre_joueur;i++)
    {
        if(tableau_joueur[i].etat==1)
        {
            if(banquise[tableau_joueur[i].position.x][tableau_joueur[i].position.y].etat==0)
            {
                tableau_joueur[i].etat=0;
            }
            else
            {
                compteur_vivant++;
            }
        }
    }
    if(compteur_vivant>0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

//fonction qui permet de selectionner le joueur qui jouera ensuite
void joueur_suivant(T_case **banquise,T_joueur *tableau_joueur,int* indice_joueur, int nombre_joueur)
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
    }
}
// Indique la position de la tête du marteau par rapport à l'axe ( 0 : en haut, 1  à gauche, 2 : en bas, 3 : à droite)
int positionTeteMarteau(T_case **banquise, int i, int j)
// On donne pour i et j la position de l'axe du marteau
{
    int x, y;
    int retour = -1;
    x = i - banquise[i][j].typeObjet->position.x;
    y = j - banquise[i][j].typeObjet->position.y;
    if((x==0) && (y==1)) // Si la tête de marteau se trouve au dessus de l'axe
    {
        retour = 0; // On renvoie 0
    }
    else if((x==1) && (y==0))
    {
        retour = 1; // On renvoie 1
    }
    else if((x==0) && (y==-1))
    {
        retour = 2; // On renvoie 2
    }
    else if((x==-1) && (y==0))
    {
        retour = 3; // On renvoie 3
    }
    else
    {
        printf("\n\nERROR dans la fonction positionTeteMarteau, le cas n'est pas trouve\n\n");
    }
    return retour;
}
// Indique si le marteau peut tourner (1) ou non (0)
int marteauPeutBouger(T_case **banquise, int i, int j, int directionX, int directionY, int tailleBanquise, int casMarteau)
// On donne en i et en j la position de la tête de marteau
{
    int retour = 1;
    if(casMarteau==0)
    {
        if(directionX==1)
        {
            if(i+2<tailleBanquise) //Cas 1
            {
                if(objetEmpecheDeplacement(banquise, i+1, j)+objetEmpecheDeplacement(banquise, i+2, j)>=2)
                {
                    retour = 0;
                }
            }
            if((retour==1) && (objetEmpecheDeplacement(banquise, i+1, j+1)+objetEmpecheDeplacement(banquise, i+1, j+2)>=2)) //Cas 2
            {
                retour = 0;
            }
        }
        if(directionX==-1)
        {
            if(i-2>=0) //Cas 1
            {
                if(objetEmpecheDeplacement(banquise, i-1, j)+objetEmpecheDeplacement(banquise, i-2, j)>=2)
                {
                    retour = 0;
                }
            }
            if((retour==1) && (objetEmpecheDeplacement(banquise, i-1, j+1)+objetEmpecheDeplacement(banquise, i-1, j+2)>=2)) // Cas 2
            {
                retour = 0;
            }
        }
    }
    else if(casMarteau==1)
    {
        if(directionY==1)
        {
            if(j+2<tailleBanquise) //Cas 1
            {
                if(objetEmpecheDeplacement(banquise, i, j+1)+objetEmpecheDeplacement(banquise, i, j+2)>=2)
                {
                    retour = 0;
                }
            }
            if((retour==1) && (objetEmpecheDeplacement(banquise, i+1, j+1)+objetEmpecheDeplacement(banquise, i+2, j+1)>=2)) //Cas 2
            {
                retour = 0;
            }
        }
        if(directionY==-1)
        {
            if(j-2>=0) //Cas 1
            {
                if(objetEmpecheDeplacement(banquise, i, j-1)+objetEmpecheDeplacement(banquise, i, j-2)>=2)
                {
                    retour = 0;
                }
            }
            if((retour==1) && (objetEmpecheDeplacement(banquise, i+1, j-1)+objetEmpecheDeplacement(banquise, i+2, j-1)>=2)) //Cas 2
            {
                retour = 0;
            }
        }
    }
    else if(casMarteau==2)
    {
        if(directionX==1)
        {
            if(i+2<tailleBanquise) //Cas 1
            {
                if(objetEmpecheDeplacement(banquise, i+1, j)+objetEmpecheDeplacement(banquise, i+2, j)>=2)
                {
                    retour = 0;
                }
            }
            if((retour==1) && (objetEmpecheDeplacement(banquise, i+1, j-1)+objetEmpecheDeplacement(banquise, i+1, j-2)>=2)) //Cas 2
            {
                retour = 0;
            }
        }
        if(directionX==-1)
        {
            if(i-2>=0) //Cas 1
            {
                if(objetEmpecheDeplacement(banquise, i-1, j)+objetEmpecheDeplacement(banquise, i-2, j)>=2)
                {
                    retour = 0;
                }
            }
            if((retour==1) && (objetEmpecheDeplacement(banquise, i-1, j-1)+objetEmpecheDeplacement(banquise, i-1, j-2)>=2)) // Cas 2
            {
                retour = 0;
            }
        }
    }
    else if(casMarteau==3)
    {
        if(directionY==1)
        {
            if(j+2<tailleBanquise) //Cas 1
            {
                if(objetEmpecheDeplacement(banquise, i, j+1)+objetEmpecheDeplacement(banquise, i, j+2)>=2)
                {
                    retour = 0;
                }
            }
            if((retour==1) && (objetEmpecheDeplacement(banquise, i-1, j+1)+objetEmpecheDeplacement(banquise, i-2, j+1)>=2)) //Cas 2
            {
                retour = 0;
            }
        }
        if(directionY==-1)
        {
            if(j-2>=0) //Cas 1
            {
                if(objetEmpecheDeplacement(banquise, i, j-1)+objetEmpecheDeplacement(banquise, i, j-2)>=2)
                {
                    retour = 0;
                }
            }
            if((retour==1) && (objetEmpecheDeplacement(banquise, i-1, j-1)+objetEmpecheDeplacement(banquise, i-2, j-1)>=2)) //Cas 2
            {
                retour = 0;
            }
        }
    }
    else
    {
        printf("\n\nERROR dans la fonction marteauPeutBouger, casMarteau non trouvé\n\n");
        retour = 0;
    }
    return retour;
}
// Ici, i et j sont les position de la tête de marteau
void deplacementMarteau(T_case **banquise, int i, int j, int directionX, int directionY, int tailleBanquise, int nombreDeDeplacementRestant, T_joueur *tableau_joueur, int nombre_joueur)
{
    int continu = 1; // Indique si l'on continu dans le code ou non
    int compteur;
    int test = 0; // Variable qui indique si la marteau se stoppe après un déplacement ou non.
    if((directionX==0) && (directionY==0))
    {
        return;
    }
    else
    {
        int casMarteau = positionTeteMarteau(banquise, banquise[i][j].typeObjet->position.x, banquise[i][j].typeObjet->position.y);
        if((marteauPeutBouger(banquise, i, j, directionX, directionY, tailleBanquise, casMarteau)==1) && (nombreDeDeplacementRestant!=0))
        {
            if(casMarteau==0) // La tête est en haut de l'axe
            {
                if(directionX==1)
                {

                    // PARTI DEPLACEMENT DES OBJETS


                    if(banquise[i+1][j].typeObjet!=NULL) // On regarde si il y a un glaçon sur la première case
                    {
                        if(banquise[i+1][j].typeObjet->objet==0) // Si le marteau rencontre un glaçon, on déplace le glaçon et comme le marteau a tappé dans un glaçon, on le stop
                        {
                            continu = 0;
                            banquise[i][j+1].typeObjet->nbTourMarteau = 0;
                            banquise[i][j].typeObjet->vecteur.dx = 0;
                            banquise[i][j].typeObjet->vecteur.dy = 0;
                            deplacementGlacon(banquise, i+1, j, 1, 0, tailleBanquise, tableau_joueur, nombre_joueur);
                        }
                    }

                    // On regarde si le marteau va être bloqué après un déplacement

                    if((continu != 0) && (j+3<tailleBanquise)) // Si il n'y a pas de glaçon en deuxième position, on regarde si une fois la rotation faite, le marteau se bloque ou non
                    {
                        if(objetEmpecheDeplacement(banquise, i+1, j+2)+objetEmpecheDeplacement(banquise, i+1, j+3)>=2)
                        {
                            test = 1;
                        }
                    }

                    if((banquise[i+1][j+1].typeObjet!=NULL) && (continu!=0)) // Si il n'y en a pas, on regarde si il y a un glaçon sur la deuxième case
                    {
                        if(banquise[i+1][j+1].typeObjet->objet==0)
                        {
                            if(banquise[i+1][j].occupe!=NULL) // On regarde si un joueur va mourir sur la case précédente
                            {
                                for(compteur=0; compteur<nombre_joueur; compteur++)
                                {
                                    if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j))
                                    {
                                        tableau_joueur[compteur].etat=0;
                                        banquise[i+1][j].occupe=NULL;
                                        printf("\n\nUn joueur est mort\n\n");
                                    }
                                }
                            }
                            if(banquise[i+1][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                            {
                                for(compteur=0; compteur<nombre_joueur; compteur++)
                                {
                                    if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j+1))
                                    {
                                        tableau_joueur[compteur].etat=0;
                                        banquise[i+1][j+1].occupe=NULL;
                                        printf("\n\nUn joueur est mort\n\n");
                                    }
                                }
                            }
                            deplacementGlacon(banquise, i+1, j+1, 0, 1, tailleBanquise, tableau_joueur, nombre_joueur);
                            continu = 0;

                            banquise[i+1][j+1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                            banquise[i+1][j+1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place
                            banquise[i][j+1].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau que le marteau s'est stoppé
                            banquise[i+1][j+1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                            banquise[i+1][j+1].typeObjet->vecteur.dy = 0;

                            banquise[i][j+1].typeObjet->position.x = i+1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                            banquise[i][j+1].typeObjet->position.y = j+1;

                            banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête

                        }
                    }

                    if((continu!=0) && (test == 1)) // Si le marteau va se bloquer, on effectue la rotation, puis on arrête le marteau
                    {
                        if(banquise[i+1][j].occupe!=NULL) // On regarde si un joueur va mourir sur la case précédente
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i+1][j].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i+1][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j+1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i+1][j+1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }

                        continu = 0;

                        banquise[i+1][j+1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i+1][j+1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place
                        banquise[i][j+1].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau que le marteau s'est stoppé
                        banquise[i+1][j+1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                        banquise[i+1][j+1].typeObjet->vecteur.dy = 0;

                        banquise[i][j+1].typeObjet->position.x = i+1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                        banquise[i][j+1].typeObjet->position.y = j+1;

                        banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête
                    }

                    if(continu !=0) // Si il n'y en a pas, on effectue le déplacement du marteau avec la mort des joueurs
                    {

                        // MORT DES JOUEURS

                        if(banquise[i+1][j].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i+1][j].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i+1][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j+1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i+1][j+1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i+1][j+2].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j+2))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i+1][j+2].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }

                        // PARTI DEPLACEMENT DU MARTEAU

                        banquise[i+1][j+1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i+1][j+1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                        banquise[i][j+1].typeObjet->position.x = i+1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                        banquise[i][j+1].typeObjet->position.y = j+1;

                        banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête

                        if(banquise[i+1][j+2].typeObjet!=NULL)
                        {
                            if(banquise[i+1][j+2].typeObjet->objet==0) // Si on rencontre un glaçon, on le fait bouger et on arrête le marteau
                            {
                                deplacementGlacon(banquise, i+1, j+2, 0, 1, tailleBanquise, tableau_joueur, nombre_joueur);
                                banquise[i][j+1].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau qu'il doit s'arrêter
                                banquise[i+1][j+1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                                banquise[i+1][j+1].typeObjet->vecteur.dy = 0;

                            }
                            else
                            {
                                banquise[i][j+1].typeObjet->nbTourMarteau = nombreDeDeplacementRestant-1;;  // On indique à l'axe du marteau le nombre de déplacement à faire restant
                                banquise[i+1][j+1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                                banquise[i+1][j+1].typeObjet->vecteur.dy = 1;
                                if(banquise[i][j+1].typeObjet->nbTourMarteau==0)
                                {
                                  banquise[i+1][j+1].typeObjet->vecteur.dx = 0;
                                  banquise[i+1][j+1].typeObjet->vecteur.dy = 0;
                                }
                            }
                        }
                        else // Sinon on change son nombre de déplacement
                        {
                            banquise[i][j+1].typeObjet->nbTourMarteau = nombreDeDeplacementRestant-1;;  // On indique à l'axe du marteau le nombre de déplacement à faire restant

                            banquise[i+1][j+1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                            banquise[i+1][j+1].typeObjet->vecteur.dy = 1;
                                if(banquise[i][j+1].typeObjet->nbTourMarteau==0)
                                {
                                  banquise[i+1][j+1].typeObjet->vecteur.dx = 0;
                                  banquise[i+1][j+1].typeObjet->vecteur.dy = 0;
                                }
                        }
                    }
                }
                if(directionX==-1)
                {
                    // PARTI DEPLACEMENT DES OBJETS


                    if(banquise[i-1][j].typeObjet!=NULL) // On regarde si il y a un glaçon sur la première case
                    {
                        if(banquise[i-1][j].typeObjet->objet==0) // Si le marteau rencontre un glaçon, on déplace le glaçon et comme le marteau a tappé dans un glaçon, on le stop
                        {
                            continu = 0;
                            banquise[i][j+1].typeObjet->nbTourMarteau = 0;
                            banquise[i][j].typeObjet->vecteur.dx = 0;
                            banquise[i][j].typeObjet->vecteur.dy = 0;
                            deplacementGlacon(banquise, i-1, j, -1, 0, tailleBanquise, tableau_joueur, nombre_joueur);

                        }
                    }

                    // On regarde si le marteau va être bloqué après un déplacement

                    if((continu != 0) && (j+3<tailleBanquise)) // Si il n'y a pas de glaçon en deuxième position, on regarde si une fois la rotation faite, le marteau se bloque ou non
                    {
                        if(objetEmpecheDeplacement(banquise, i-1, j+2)+objetEmpecheDeplacement(banquise, i-1, j+3)>=2)
                        {
                            test = 1;
                        }
                    }

                    if((banquise[i-1][j+1].typeObjet!=NULL) && (continu!=0)) // Si il n'y en a pas, on regarde si il y a un glaçon sur la deuxième case
                    {
                        if(banquise[i-1][j+1].typeObjet->objet==0)
                        {
                            if(banquise[i-1][j].occupe!=NULL) // On regarde si un joueur va mourir sur la case précédente
                            {
                                for(compteur=0; compteur<nombre_joueur; compteur++)
                                {
                                    if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j))
                                    {
                                        tableau_joueur[compteur].etat=0;
                                        banquise[i-1][j].occupe=NULL;
                                        printf("\n\nUn joueur est mort\n\n");
                                    }
                                }
                            }
                            if(banquise[i-1][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                            {
                                for(compteur=0; compteur<nombre_joueur; compteur++)
                                {
                                    if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j+1))
                                    {
                                        tableau_joueur[compteur].etat=0;
                                        banquise[i-1][j+1].occupe=NULL;
                                        printf("\n\nUn joueur est mort\n\n");
                                    }
                                }
                            }
                            deplacementGlacon(banquise, i-1, j+1, 0, 1, tailleBanquise, tableau_joueur, nombre_joueur);
                            continu = 0;

                            banquise[i-1][j+1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                            banquise[i-1][j+1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                            banquise[i][j+1].typeObjet->position.x = i-1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                            banquise[i][j+1].typeObjet->position.y = j+1;

                            banquise[i][j+1].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau que le marteau s'est stoppé
                            banquise[i-1][j+1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                            banquise[i-1][j+1].typeObjet->vecteur.dy = 0;
                            banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête

                        }
                    }

                    if((continu!=0) && (test==1)) // Si le marteau va se bloquer, on effectue la rotation, puis on arrête le marteau
                    {
                        if(banquise[i-1][j].occupe!=NULL) // On regarde si un joueur va mourir sur la case précédente
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i-1][j].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i-1][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j+1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i-1][j+1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        continu = 0;

                        banquise[i-1][j+1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i-1][j+1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                        banquise[i][j+1].typeObjet->position.x = i-1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                        banquise[i][j+1].typeObjet->position.y = j+1;

                        banquise[i][j+1].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau que le marteau s'est stoppé
                        banquise[i-1][j+1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                        banquise[i-1][j+1].typeObjet->vecteur.dy = 0;
                        banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête
                    }

                    if(continu !=0) // Si il n'y en a pas, on effectue le déplacement du marteau avec la mort des joueurs
                    {

                        // MORT DES JOUEURS

                        if(banquise[i-1][j].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i-1][j].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i-1][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j+1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i-1][j+1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i-1][j+2].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j+2))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i-1][j+2].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }

                        // PARTI DEPLACEMENT DU MARTEAU

                        banquise[i-1][j+1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i-1][j+1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                        banquise[i][j+1].typeObjet->position.x = i-1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                        banquise[i][j+1].typeObjet->position.y = j+1;

                        banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête

                        if(banquise[i-1][j+2].typeObjet!=NULL)
                        {
                            if(banquise[i-1][j+2].typeObjet->objet==0) // Si on rencontre un glaçon, on le fait bouger et on arrête le marteau
                            {
                                deplacementGlacon(banquise, i-1, j+2, 0, 1, tailleBanquise, tableau_joueur, nombre_joueur);
                                banquise[i][j+1].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau qu'il doit s'arrêter
                                banquise[i-1][j+1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                                banquise[i-1][j+1].typeObjet->vecteur.dy = 0;

                            }
                            else
                            {
                                banquise[i][j+1].typeObjet->nbTourMarteau = nombreDeDeplacementRestant-1;;  // On indique à l'axe du marteau le nombre de déplacement à faire restant
                                banquise[i-1][j+1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                                banquise[i-1][j+1].typeObjet->vecteur.dy = 1;
                                if(banquise[i][j+1].typeObjet->nbTourMarteau==0)
                                {
                                  banquise[i-1][j+1].typeObjet->vecteur.dx = 0;
                                  banquise[i-1][j+1].typeObjet->vecteur.dy = 0;
                                }
                            }
                        }
                        else // Sinon on change son nombre de déplacement
                        {
                            banquise[i][j+1].typeObjet->nbTourMarteau = nombreDeDeplacementRestant-1;;  // On indique à l'axe du marteau le nombre de déplacement à faire restant
                            banquise[i-1][j+1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                            banquise[i-1][j+1].typeObjet->vecteur.dy = 1;
                            if(banquise[i][j+1].typeObjet->nbTourMarteau==0)
                            {
                              banquise[i-1][j+1].typeObjet->vecteur.dx = 0;
                              banquise[i-1][j+1].typeObjet->vecteur.dy = 0;
                            }
                        }
                    }
                }
            }
            else if(casMarteau==1) // La tête est à gauche de l'axe
            {
                if(directionY==1)
                {
                    // PARTI DEPLACEMENT DES OBJETS


                    if(banquise[i][j+1].typeObjet!=NULL) // On regarde si il y a un glaçon sur la première case
                    {
                        if(banquise[i][j+1].typeObjet->objet==0) // Si le marteau rencontre un glaçon, on déplace le glaçon et comme le marteau a tappé dans un glaçon, on le stop
                        {
                            continu = 0;
                            banquise[i+1][j].typeObjet->nbTourMarteau = 0;
                            banquise[i][j].typeObjet->vecteur.dx = 0;
                            banquise[i][j].typeObjet->vecteur.dy = 0;
                            deplacementGlacon(banquise, i, j+1, 0, 1, tailleBanquise, tableau_joueur, nombre_joueur);
                        }
                    }

                    if((continu!=0) && (i+3<tailleBanquise)) // Si il n'y a pas de glaçon en deuxième position, on regarde si une fois la rotation faite, le marteau se bloque ou non
                    {
                        if(objetEmpecheDeplacement(banquise, i+2, j+1)+objetEmpecheDeplacement(banquise, i+3, j+1)>=2)
                        {
                            test = 1;
                        }
                    }

                    if((banquise[i+1][j+1].typeObjet!=NULL) && (continu!=0)) // Si il n'y en a pas, on regarde si il y a un glaçon sur la deuxième case
                    {
                        if(banquise[i+1][j+1].typeObjet->objet==0)
                        {
                            if(banquise[i][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case précédente
                            {
                                for(compteur=0; compteur<nombre_joueur; compteur++)
                                {
                                    if((tableau_joueur[compteur].position.x==i) && (tableau_joueur[compteur].position.y==j+1))
                                    {
                                        tableau_joueur[compteur].etat=0;
                                        banquise[i][j+1].occupe=NULL;
                                        printf("\n\nUn joueur est mort\n\n");
                                    }
                                }
                            }
                            if(banquise[i+1][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                            {
                                for(compteur=0; compteur<nombre_joueur; compteur++)
                                {
                                    if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j+1))
                                    {
                                        tableau_joueur[compteur].etat=0;
                                        banquise[i+1][j+1].occupe=NULL;
                                        printf("\n\nUn joueur est mort\n\n");
                                    }
                                }
                            }
                            deplacementGlacon(banquise, i+1, j+1, 1, 0, tailleBanquise, tableau_joueur, nombre_joueur);
                            continu = 0;

                            banquise[i+1][j+1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                            banquise[i+1][j+1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                            banquise[i+1][j].typeObjet->position.x = i+1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                            banquise[i+1][j].typeObjet->position.y = j+1;

                            banquise[i+1][j].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau que le marteau s'est stoppé
                            banquise[i+1][j+1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                            banquise[i+1][j+1].typeObjet->vecteur.dy = 0;
                            banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête

                        }
                    }

                    if((continu!=0) && (test==1)) // Si le marteau va se bloquer, on effectue la rotation, puis on arrête le marteau
                    {
                        if(banquise[i][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case précédente
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i) && (tableau_joueur[compteur].position.y==j+1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i][j+1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i+1][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j+1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i+1][j+1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        continu = 0;

                        banquise[i+1][j+1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i+1][j+1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                        banquise[i+1][j].typeObjet->position.x = i+1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                        banquise[i+1][j].typeObjet->position.y = j+1;

                        banquise[i+1][j].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau que le marteau s'est stoppé
                        banquise[i+1][j+1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                        banquise[i+1][j+1].typeObjet->vecteur.dy = 0;
                        banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête
                    }

                    if(continu !=0) // Si il n'y en a pas, on effectue le déplacement du marteau avec la mort des joueurs
                    {

                        // MORT DES JOUEURS

                        if(banquise[i][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i) && (tableau_joueur[compteur].position.y==j+1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i][j+1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i+1][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j+1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i+1][j+1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i+2][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i+2) && (tableau_joueur[compteur].position.y==j+1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i+2][j+1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }

                        // PARTI DEPLACEMENT DU MARTEAU

                        banquise[i+1][j+1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i+1][j+1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                        banquise[i+1][j].typeObjet->position.x = i+1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                        banquise[i+1][j].typeObjet->position.y = j+1;

                        banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête

                        if(banquise[i+2][j+1].typeObjet!=NULL)
                        {
                            if(banquise[i+2][j+1].typeObjet->objet==0) // Si on rencontre un glaçon, on le fait bouger et on arrête le marteau
                            {
                                deplacementGlacon(banquise, i+2, j+1, 1, 0, tailleBanquise, tableau_joueur, nombre_joueur);
                                banquise[i+1][j].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau qu'il doit s'arrêter
                                banquise[i+1][j+1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                                banquise[i+1][j+1].typeObjet->vecteur.dy = 0;

                            }
                            else
                            {
                                banquise[i+1][j].typeObjet->nbTourMarteau = nombreDeDeplacementRestant-1;;  // On indique à l'axe du marteau le nombre de déplacement à faire restant
                                banquise[i+1][j+1].typeObjet->vecteur.dx = 1;  // On donne une nouvelle direction à la tête
                                banquise[i+1][j+1].typeObjet->vecteur.dy = 0;
                                if(banquise[i+1][j].typeObjet->nbTourMarteau==0)
                                {
                                  banquise[i+1][j+1].typeObjet->vecteur.dx = 0;
                                  banquise[i+1][j+1].typeObjet->vecteur.dy = 0;
                                }
                            }
                        }
                        else // Sinon on change son nombre de déplacement
                        {
                            banquise[i+1][j].typeObjet->nbTourMarteau = nombreDeDeplacementRestant-1;;  // On indique à l'axe du marteau le nombre de déplacement à faire restant
                            banquise[i+1][j+1].typeObjet->vecteur.dx = 1;  // On donne une nouvelle direction à la tête
                            banquise[i+1][j+1].typeObjet->vecteur.dy = 0;
                            if(banquise[i+1][j].typeObjet->nbTourMarteau==0)
                            {
                              banquise[i+1][j+1].typeObjet->vecteur.dx = 0;
                              banquise[i+1][j+1].typeObjet->vecteur.dy = 0;
                            }
                        }
                    }
                }
                if(directionY==-1)
                {
                    // PARTI DEPLACEMENT DES OBJETS


                    if(banquise[i][j-1].typeObjet!=NULL) // On regarde si il y a un glaçon sur la première case
                    {
                        if(banquise[i][j-1].typeObjet->objet==0) // Si le marteau rencontre un glaçon, on déplace le glaçon et comme le marteau a tappé dans un glaçon, on le stop
                        {
                            continu = 0;
                            banquise[i+1][j].typeObjet->nbTourMarteau = 0;
                            banquise[i][j].typeObjet->vecteur.dx = 0;
                            banquise[i][j].typeObjet->vecteur.dy = 0;
                            deplacementGlacon(banquise, i, j-1, 0, -1, tailleBanquise, tableau_joueur, nombre_joueur);
                        }
                    }

                    if((continu!=0) && (i+3<tailleBanquise)) // Si il n'y a pas de glaçon en deuxième position, on regarde si une fois la rotation faite, le marteau se bloque ou non
                    {
                        if(objetEmpecheDeplacement(banquise, i+2, j-1)+objetEmpecheDeplacement(banquise, i+3, j-1)>=2)
                        {
                            test = 1;
                        }
                    }

                    if((banquise[i+1][j-1].typeObjet!=NULL) && (continu!=0)) // Si il n'y en a pas, on regarde si il y a un glaçon sur la deuxième case
                    {
                        if(banquise[i+1][j-1].typeObjet->objet==0)
                        {
                            if(banquise[i][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case précédente
                            {
                                for(compteur=0; compteur<nombre_joueur; compteur++)
                                {
                                    if((tableau_joueur[compteur].position.x==i) && (tableau_joueur[compteur].position.y==j-1))
                                    {
                                        tableau_joueur[compteur].etat=0;
                                        banquise[i][j-1].occupe=NULL;
                                        printf("\n\nUn joueur est mort\n\n");
                                    }
                                }
                            }
                            if(banquise[i+1][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                            {
                                for(compteur=0; compteur<nombre_joueur; compteur++)
                                {
                                    if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j-1))
                                    {
                                        tableau_joueur[compteur].etat=0;
                                        banquise[i+1][j-1].occupe=NULL;
                                        printf("\n\nUn joueur est mort\n\n");
                                    }
                                }
                            }
                            deplacementGlacon(banquise, i+1, j-1, 1, 0, tailleBanquise, tableau_joueur, nombre_joueur);
                            continu = 0;

                            banquise[i+1][j-1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                            banquise[i+1][j-1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                            banquise[i+1][j].typeObjet->position.x = i+1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                            banquise[i+1][j].typeObjet->position.y = j-1;

                            banquise[i+1][j].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau que le marteau s'est stoppé
                            banquise[i+1][j-1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                            banquise[i+1][j-1].typeObjet->vecteur.dy = 0;
                            banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête

                        }
                    }

                    if((continu!=0) && (test==1)) // Si le marteau va se bloquer, on effectue la rotation, puis on arrête le marteau
                    {
                        if(banquise[i][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case précédente
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i) && (tableau_joueur[compteur].position.y==j-1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i][j-1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i+1][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j-1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i+1][j-1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        continu = 0;

                        banquise[i+1][j-1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i+1][j-1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                        banquise[i+1][j].typeObjet->position.x = i+1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                        banquise[i+1][j].typeObjet->position.y = j-1;

                        banquise[i+1][j].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau que le marteau s'est stoppé
                        banquise[i+1][j-1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                        banquise[i+1][j-1].typeObjet->vecteur.dy = 0;
                        banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête
                    }

                    if(continu !=0) // Si il n'y en a pas, on effectue le déplacement du marteau avec la mort des joueurs
                    {

                        // MORT DES JOUEURS

                        if(banquise[i][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i) && (tableau_joueur[compteur].position.y==j-1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i][j-1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i+1][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j-1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i+1][j-1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i+2][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i+2) && (tableau_joueur[compteur].position.y==j-1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i+2][j-1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }

                        // PARTI DEPLACEMENT DU MARTEAU

                        banquise[i+1][j-1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i+1][j-1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                        banquise[i+1][j].typeObjet->position.x = i+1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                        banquise[i+1][j].typeObjet->position.y = j-1;

                        banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête

                        if(banquise[i+2][j-1].typeObjet!=NULL)
                        {
                            if(banquise[i+2][j-1].typeObjet->objet==0) // Si on rencontre un glaçon, on le fait bouger et on arrête le marteau
                            {
                                deplacementGlacon(banquise, i+2, j-1, 1, 0, tailleBanquise, tableau_joueur, nombre_joueur);
                                banquise[i+1][j].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau qu'il doit s'arrêter
                                banquise[i+1][j-1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                                banquise[i+1][j-1].typeObjet->vecteur.dy = 0;

                            }
                            else
                            {
                                banquise[i+1][j].typeObjet->nbTourMarteau = nombreDeDeplacementRestant-1;;  // On indique à l'axe du marteau le nombre de déplacement à faire restant
                                banquise[i+1][j-1].typeObjet->vecteur.dx = 1;  // On donne une nouvelle direction à la tête
                                banquise[i+1][j-1].typeObjet->vecteur.dy = 0;
                                if(banquise[i+1][j].typeObjet->nbTourMarteau==0)
                                {
                                  banquise[i+1][j-1].typeObjet->vecteur.dx = 0;
                                  banquise[i+1][j-1].typeObjet->vecteur.dy = 0;
                                }
                            }
                        }
                        else // Sinon on change son nombre de déplacement
                        {
                            banquise[i+1][j].typeObjet->nbTourMarteau = nombreDeDeplacementRestant-1;;  // On indique à l'axe du marteau le nombre de déplacement à faire restant
                            banquise[i+1][j-1].typeObjet->vecteur.dx = 1;  // On donne une nouvelle direction à la tête
                            banquise[i+1][j-1].typeObjet->vecteur.dy = 0;
                            if(banquise[i+1][j].typeObjet->nbTourMarteau==0)
                            {
                              banquise[i+1][j-1].typeObjet->vecteur.dx = 0;
                              banquise[i+1][j-1].typeObjet->vecteur.dy = 0;
                            }
                        }
                    }
                }
            }
            else if(casMarteau==2) // La tête est en bas de l'axe
            {
                if(directionX==1)
                {
                    // PARTI DEPLACEMENT DES OBJETS


                    if(banquise[i+1][j].typeObjet!=NULL) // On regarde si il y a un glaçon sur la première case
                    {
                        if(banquise[i+1][j].typeObjet->objet==0) // Si le marteau rencontre un glaçon, on déplace le glaçon et comme le marteau a tappé dans un glaçon, on le stop
                        {
                            continu = 0;
                            banquise[i][j-1].typeObjet->nbTourMarteau = 0;
                            banquise[i][j].typeObjet->vecteur.dx = 0;
                            banquise[i][j].typeObjet->vecteur.dy = 0;
                            deplacementGlacon(banquise, i+1, j, 1, 0, tailleBanquise, tableau_joueur, nombre_joueur);
                        }
                    }

                    if((continu!=0) && (j-3>=0)) // Si il n'y a pas de glaçon en deuxième position, on regarde si une fois la rotation faite, le marteau se bloque ou non
                    {
                        if(objetEmpecheDeplacement(banquise, i+1, j-2)+objetEmpecheDeplacement(banquise, i+1, j-3)>=2)
                        {
                            test = 1;
                        }
                    }

                    if((banquise[i+1][j-1].typeObjet!=NULL) && (continu!=0)) // Si il n'y en a pas, on regarde si il y a un glaçon sur la deuxième case
                    {
                        if(banquise[i+1][j-1].typeObjet->objet==0)
                        {
                            if(banquise[i+1][j].occupe!=NULL) // On regarde si un joueur va mourir sur la case précédente
                            {
                                for(compteur=0; compteur<nombre_joueur; compteur++)
                                {
                                    if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j))
                                    {
                                        tableau_joueur[compteur].etat=0;
                                        banquise[i+1][j].occupe=NULL;
                                        printf("\n\nUn joueur est mort\n\n");
                                    }
                                }
                            }
                            if(banquise[i+1][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                            {
                                for(compteur=0; compteur<nombre_joueur; compteur++)
                                {
                                    if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j-1))
                                    {
                                        tableau_joueur[compteur].etat=0;
                                        banquise[i+1][j-1].occupe=NULL;
                                        printf("\n\nUn joueur est mort\n\n");
                                    }
                                }
                            }
                            deplacementGlacon(banquise, i+1, j-1, 0, -1, tailleBanquise, tableau_joueur, nombre_joueur);
                            continu = 0;

                            banquise[i+1][j-1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                            banquise[i+1][j-1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                            banquise[i][j-1].typeObjet->position.x = i+1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                            banquise[i][j-1].typeObjet->position.y = j-1;

                            banquise[i][j-1].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau que le marteau s'est stoppé
                            banquise[i+1][j-1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                            banquise[i+1][j-1].typeObjet->vecteur.dy = 0;
                            banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête

                        }
                    }

                    if((continu!=0) && (test==1)) // Si le marteau va se bloquer, on effectue la rotation, puis on arrête le marteau
                    {
                        if(banquise[i+1][j].occupe!=NULL) // On regarde si un joueur va mourir sur la case précédente
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i+1][j].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i+1][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j-1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i+1][j-1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        continu = 0;

                        banquise[i+1][j-1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i+1][j-1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                        banquise[i][j-1].typeObjet->position.x = i+1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                        banquise[i][j-1].typeObjet->position.y = j-1;

                        banquise[i][j-1].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau que le marteau s'est stoppé
                        banquise[i+1][j-1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                        banquise[i+1][j-1].typeObjet->vecteur.dy = 0;
                        banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête
                    }

                    if(continu !=0) // Si il n'y en a pas, on effectue le déplacement du marteau avec la mort des joueurs
                    {

                        // MORT DES JOUEURS

                        if(banquise[i+1][j].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i+1][j].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i+1][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j-1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i+1][j-1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i+1][j-2].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i+1) && (tableau_joueur[compteur].position.y==j-2))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i+1][j-2].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }

                        // PARTI DEPLACEMENT DU MARTEAU

                        banquise[i+1][j-1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i+1][j-1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                        banquise[i][j-1].typeObjet->position.x = i+1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                        banquise[i][j-1].typeObjet->position.y = j-1;

                        banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête

                        if(banquise[i+1][j-2].typeObjet!=NULL)
                        {
                            if(banquise[i+1][j-2].typeObjet->objet==0) // Si on rencontre un glaçon, on le fait bouger et on arrête le marteau
                            {
                                deplacementGlacon(banquise, i+1, j-2, 0, -1, tailleBanquise, tableau_joueur, nombre_joueur);
                                banquise[i][j-1].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau qu'il doit s'arrêter
                                banquise[i+1][j-1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                                banquise[i+1][j-1].typeObjet->vecteur.dy = 0;

                            }
                            else
                            {
                                banquise[i][j-1].typeObjet->nbTourMarteau = nombreDeDeplacementRestant-1;;  // On indique à l'axe du marteau le nombre de déplacement à faire restant
                                banquise[i+1][j-1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                                banquise[i+1][j-1].typeObjet->vecteur.dy = -1;
                                if(banquise[i][j-1].typeObjet->nbTourMarteau==0)
                                {
                                  banquise[i+1][j-1].typeObjet->vecteur.dx = 0;
                                  banquise[i+1][j-1].typeObjet->vecteur.dy = 0;
                                }
                            }
                        }
                        else // Sinon on change son nombre de déplacement
                        {
                            banquise[i][j-1].typeObjet->nbTourMarteau = nombreDeDeplacementRestant-1;;  // On indique à l'axe du marteau le nombre de déplacement à faire restant
                            banquise[i+1][j-1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                            banquise[i+1][j-1].typeObjet->vecteur.dy = -1;
                            if(banquise[i][j-1].typeObjet->nbTourMarteau==0)
                            {
                              banquise[i+1][j-1].typeObjet->vecteur.dx = 0;
                              banquise[i+1][j-1].typeObjet->vecteur.dy = 0;
                            }
                        }
                    }
                }
                if(directionX==-1)
                {
                    // PARTI DEPLACEMENT DES OBJETS


                    if(banquise[i-1][j].typeObjet!=NULL) // On regarde si il y a un glaçon sur la première case
                    {
                        if(banquise[i-1][j].typeObjet->objet==0) // Si le marteau rencontre un glaçon, on déplace le glaçon et comme le marteau a tappé dans un glaçon, on le stop
                        {
                            continu = 0;
                            banquise[i][j-1].typeObjet->nbTourMarteau = 0;
                            banquise[i][j].typeObjet->vecteur.dx = 0;
                            banquise[i][j].typeObjet->vecteur.dy = 0;
                            deplacementGlacon(banquise, i-1, j, -1, 0, tailleBanquise, tableau_joueur, nombre_joueur);
                        }
                    }

                    if((continu!=0) && (j-3>=0)) // Si il n'y a pas de glaçon en deuxième position, on regarde si une fois la rotation faite, le marteau se bloque ou non
                    {
                        if(objetEmpecheDeplacement(banquise, i-1, j-2)+objetEmpecheDeplacement(banquise, i-1, j-3)>=2)
                        {
                            test = 1;
                        }
                    }

                    if((banquise[i-1][j-1].typeObjet!=NULL) && (continu!=0)) // Si il n'y en a pas, on regarde si il y a un glaçon sur la deuxième case
                    {
                        if(banquise[i-1][j-1].typeObjet->objet==0)
                        {
                            if(banquise[i-1][j].occupe!=NULL) // On regarde si un joueur va mourir sur la case précédente
                            {
                                for(compteur=0; compteur<nombre_joueur; compteur++)
                                {
                                    if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j))
                                    {
                                        tableau_joueur[compteur].etat=0;
                                        banquise[i-1][j].occupe=NULL;
                                        printf("\n\nUn joueur est mort\n\n");
                                    }
                                }
                            }
                            if(banquise[i-1][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                            {
                                for(compteur=0; compteur<nombre_joueur; compteur++)
                                {
                                    if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j-1))
                                    {
                                        tableau_joueur[compteur].etat=0;
                                        banquise[i-1][j-1].occupe=NULL;
                                        printf("\n\nUn joueur est mort\n\n");
                                    }
                                }
                            }
                            deplacementGlacon(banquise, i-1, j-1, 0, -1, tailleBanquise, tableau_joueur, nombre_joueur);
                            continu = 0;

                            banquise[i-1][j-1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                            banquise[i-1][j-1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                            banquise[i][j-1].typeObjet->position.x = i-1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                            banquise[i][j-1].typeObjet->position.y = j-1;

                            banquise[i][j-1].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau que le marteau s'est stoppé
                            banquise[i-1][j-1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                            banquise[i-1][j-1].typeObjet->vecteur.dy = 0;
                            banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête

                        }
                    }

                    if((continu!=0) && (test==1)) // Si le marteau va se bloquer, on effectue la rotation, puis on arrête le marteau
                    {
                        if(banquise[i-1][j].occupe!=NULL) // On regarde si un joueur va mourir sur la case précédente
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i-1][j].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i-1][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j-1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i-1][j-1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        continu = 0;

                        banquise[i-1][j-1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i-1][j-1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                        banquise[i][j-1].typeObjet->position.x = i-1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                        banquise[i][j-1].typeObjet->position.y = j-1;

                        banquise[i][j-1].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau que le marteau s'est stoppé
                        banquise[i-1][j-1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                        banquise[i-1][j-1].typeObjet->vecteur.dy = 0;
                        banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête
                    }

                    if(continu !=0) // Si il n'y en a pas, on effectue le déplacement du marteau avec la mort des joueurs
                    {

                        // MORT DES JOUEURS

                        if(banquise[i-1][j].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i-1][j].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i-1][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j-1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i-1][j-1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i-1][j-2].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j-2))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i-1][j-2].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }

                        // PARTI DEPLACEMENT DU MARTEAU

                        banquise[i-1][j-1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i-1][j-1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                        banquise[i][j-1].typeObjet->position.x = i-1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                        banquise[i][j-1].typeObjet->position.y = j-1;

                        banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête

                        if(banquise[i-1][j-2].typeObjet!=NULL)
                        {
                            if(banquise[i-1][j-2].typeObjet->objet==0) // Si on rencontre un glaçon, on le fait bouger et on arrête le marteau
                            {
                                deplacementGlacon(banquise, i-1, j-2, 0, -1, tailleBanquise, tableau_joueur, nombre_joueur);
                                banquise[i][j-1].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau qu'il doit s'arrêter
                                banquise[i-1][j-1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                                banquise[i-1][j-1].typeObjet->vecteur.dy = 0;

                            }
                            else
                            {
                                banquise[i][j-1].typeObjet->nbTourMarteau = nombreDeDeplacementRestant-1;;  // On indique à l'axe du marteau le nombre de déplacement à faire restant
                                banquise[i-1][j-1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                                banquise[i-1][j-1].typeObjet->vecteur.dy = -1;
                                if(banquise[i][j-1].typeObjet->nbTourMarteau==0)
                                {
                                  banquise[i-1][j-1].typeObjet->vecteur.dx = 0;
                                  banquise[i-1][j-1].typeObjet->vecteur.dy = 0;
                                }
                            }
                        }
                        else // Sinon on change son nombre de déplacement
                        {
                            banquise[i][j-1].typeObjet->nbTourMarteau = nombreDeDeplacementRestant-1;;  // On indique à l'axe du marteau le nombre de déplacement à faire restant
                            banquise[i-1][j-1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                            banquise[i-1][j-1].typeObjet->vecteur.dy = -1;
                            if(banquise[i][j-1].typeObjet->nbTourMarteau==0)
                            {
                              banquise[i-1][j-1].typeObjet->vecteur.dx = 0;
                              banquise[i-1][j-1].typeObjet->vecteur.dy = 0;
                            }
                        }
                    }
                }
            }
            else if(casMarteau==3) // La tête est à droite de l'axe
            {
                if(directionY==1)
                {
                    // PARTI DEPLACEMENT DES OBJETS


                    if(banquise[i][j+1].typeObjet!=NULL) // On regarde si il y a un glaçon sur la première case
                    {
                        if(banquise[i][j+1].typeObjet->objet==0) // Si le marteau rencontre un glaçon, on déplace le glaçon et comme le marteau a tappé dans un glaçon, on le stop
                        {
                            continu = 0;
                            banquise[i-1][j].typeObjet->nbTourMarteau = 0;
                            banquise[i][j].typeObjet->vecteur.dx = 0;
                            banquise[i][j].typeObjet->vecteur.dy = 0;
                            deplacementGlacon(banquise, i, j+1, 0, 1, tailleBanquise, tableau_joueur, nombre_joueur);
                        }
                    }

                    if((continu!=0) && (i-3>=0)) // Si il n'y a pas de glaçon en deuxième position, on regarde si une fois la rotation faite, le marteau se bloque ou non
                    {
                        if(objetEmpecheDeplacement(banquise, i-2, j+1)+objetEmpecheDeplacement(banquise, i-3, j+1)>=2)
                        {
                            test = 1;
                        }
                    }

                    if((banquise[i-1][j+1].typeObjet!=NULL) && (continu!=0)) // Si il n'y en a pas, on regarde si il y a un glaçon sur la deuxième case
                    {
                        if(banquise[i-1][j+1].typeObjet->objet==0)
                        {
                            if(banquise[i][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case précédente
                            {
                                for(compteur=0; compteur<nombre_joueur; compteur++)
                                {
                                    if((tableau_joueur[compteur].position.x==i) && (tableau_joueur[compteur].position.y==j+1))
                                    {
                                        tableau_joueur[compteur].etat=0;
                                        banquise[i][j+1].occupe=NULL;
                                        printf("\n\nUn joueur est mort\n\n");
                                    }
                                }
                            }
                            if(banquise[i-1][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                            {
                                for(compteur=0; compteur<nombre_joueur; compteur++)
                                {
                                    if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j+1))
                                    {
                                        tableau_joueur[compteur].etat=0;
                                        banquise[i-1][j+1].occupe=NULL;
                                        printf("\n\nUn joueur est mort\n\n");
                                    }
                                }
                            }
                            deplacementGlacon(banquise, i-1, j+1, -1, 0, tailleBanquise, tableau_joueur, nombre_joueur);
                            continu = 0;

                            banquise[i-1][j+1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                            banquise[i-1][j+1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                            banquise[i-1][j].typeObjet->position.x = i-1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                            banquise[i-1][j].typeObjet->position.y = j+1;

                            banquise[i-1][j].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau que le marteau s'est stoppé
                            banquise[i-1][j+1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                            banquise[i-1][j+1].typeObjet->vecteur.dy = 0;
                            banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête

                        }
                    }

                    if((continu!=0) && (test==1)) // Si le marteau va se bloquer, on effectue la rotation, puis on arrête le marteau
                    {
                        if(banquise[i][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case précédente
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i) && (tableau_joueur[compteur].position.y==j+1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i][j+1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i-1][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j+1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i-1][j+1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        continu = 0;

                        banquise[i-1][j+1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i-1][j+1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                        banquise[i-1][j].typeObjet->position.x = i-1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                        banquise[i-1][j].typeObjet->position.y = j+1;

                        banquise[i-1][j].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau que le marteau s'est stoppé
                        banquise[i-1][j+1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                        banquise[i-1][j+1].typeObjet->vecteur.dy = 0;
                        banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête
                    }

                    if(continu !=0) // Si il n'y en a pas, on effectue le déplacement du marteau avec la mort des joueurs
                    {

                        // MORT DES JOUEURS

                        if(banquise[i][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i) && (tableau_joueur[compteur].position.y==j+1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i][j+1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i-1][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j+1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i-1][j+1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i-2][j+1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i-2) && (tableau_joueur[compteur].position.y==j+1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i-2][j+1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }

                        // PARTI DEPLACEMENT DU MARTEAU

                        banquise[i-1][j+1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i-1][j+1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                        banquise[i-1][j].typeObjet->position.x = i-1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                        banquise[i-1][j].typeObjet->position.y = j+1;

                        banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête

                        if(banquise[i-2][j+1].typeObjet!=NULL)
                        {
                            if(banquise[i-2][j+1].typeObjet->objet==0) // Si on rencontre un glaçon, on le fait bouger et on arrête le marteau
                            {
                                deplacementGlacon(banquise, i-2, j+1, -1, 0, tailleBanquise, tableau_joueur, nombre_joueur);
                                banquise[i-1][j].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau qu'il doit s'arrêter
                                banquise[i-1][j+1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                                banquise[i-1][j+1].typeObjet->vecteur.dy = 0;

                            }
                            else
                            {
                                banquise[i-1][j].typeObjet->nbTourMarteau = nombreDeDeplacementRestant-1;;  // On indique à l'axe du marteau le nombre de déplacement à faire restant
                                banquise[i-1][j+1].typeObjet->vecteur.dx = -1;  // On donne une nouvelle direction à la tête
                                banquise[i-1][j+1].typeObjet->vecteur.dy = 0;
                                if(banquise[i][j+1].typeObjet->nbTourMarteau==0)
                                {
                                  banquise[i+1][j+1].typeObjet->vecteur.dx = 0;
                                  banquise[i+1][j+1].typeObjet->vecteur.dy = 0;
                                }
                            }
                        }
                        else // Sinon on change son nombre de déplacement
                        {
                            banquise[i-1][j].typeObjet->nbTourMarteau = nombreDeDeplacementRestant-1;;  // On indique à l'axe du marteau le nombre de déplacement à faire restant
                            banquise[i-1][j+1].typeObjet->vecteur.dx = -1;  // On donne une nouvelle direction à la tête
                            banquise[i-1][j+1].typeObjet->vecteur.dy = 0;
                            if(banquise[i-1][j].typeObjet->nbTourMarteau==0)
                            {
                              banquise[i-1][j+1].typeObjet->vecteur.dx = 0;
                              banquise[i-1][j+1].typeObjet->vecteur.dy = 0;
                            }
                        }
                    }
                }
                if(directionY==-1)
                {
                    // PARTI DEPLACEMENT DES OBJETS


                    if(banquise[i][j-1].typeObjet!=NULL) // On regarde si il y a un glaçon sur la première case
                    {
                        if(banquise[i][j-1].typeObjet->objet==0) // Si le marteau rencontre un glaçon, on déplace le glaçon et comme le marteau a tappé dans un glaçon, on le stop
                        {
                            continu = 0;
                            banquise[i-1][j].typeObjet->nbTourMarteau = 0;
                            banquise[i][j].typeObjet->vecteur.dx = 0;
                            banquise[i][j].typeObjet->vecteur.dy = 0;
                            deplacementGlacon(banquise, i, j-1, 0, -1, tailleBanquise, tableau_joueur, nombre_joueur);
                        }
                    }

                    if((continu!=0) && (i-3>=0)) // Si il n'y a pas de glaçon en deuxième position, on regarde si une fois la rotation faite, le marteau se bloque ou non
                    {
                        if(objetEmpecheDeplacement(banquise, i-2, j-1)+objetEmpecheDeplacement(banquise, i-3, j-1)>=2)
                        {
                            test = 1;
                        }
                    }

                    if((banquise[i-1][j-1].typeObjet!=NULL) && (continu!=0)) // Si il n'y en a pas, on regarde si il y a un glaçon sur la deuxième case
                    {
                        if(banquise[i-1][j-1].typeObjet->objet==0)
                        {
                            if(banquise[i][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case précédente
                            {
                                for(compteur=0; compteur<nombre_joueur; compteur++)
                                {
                                    if((tableau_joueur[compteur].position.x==i) && (tableau_joueur[compteur].position.y==j-1))
                                    {
                                        tableau_joueur[compteur].etat=0;
                                        banquise[i][j-1].occupe=NULL;
                                        printf("\n\nUn joueur est mort\n\n");
                                    }
                                }
                            }
                            if(banquise[i-1][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                            {
                                for(compteur=0; compteur<nombre_joueur; compteur++)
                                {
                                    if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j-1))
                                    {
                                        tableau_joueur[compteur].etat=0;
                                        banquise[i-1][j-1].occupe=NULL;
                                        printf("\n\nUn joueur est mort\n\n");
                                    }
                                }
                            }
                            deplacementGlacon(banquise, i-1, j-1, -1, 0, tailleBanquise, tableau_joueur, nombre_joueur);
                            continu = 0;

                            banquise[i-1][j-1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                            banquise[i-1][j-1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                            banquise[i-1][j].typeObjet->position.x = i-1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                            banquise[i-1][j].typeObjet->position.y = j-1;

                            banquise[i-1][j].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau que le marteau s'est stoppé
                            banquise[i-1][j-1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                            banquise[i-1][j-1].typeObjet->vecteur.dy = 0;
                            banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête

                        }
                    }

                    if((continu!=0) && (test==1)) // Si le marteau va se bloquer, on effectue la rotation, puis on arrête le marteau
                    {
                        if(banquise[i][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case précédente
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i) && (tableau_joueur[compteur].position.y==j-1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i][j-1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i-1][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j-1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i-1][j-1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        continu = 0;

                        banquise[i-1][j-1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i-1][j-1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                        banquise[i-1][j].typeObjet->position.x = i-1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                        banquise[i-1][j].typeObjet->position.y = j-1;

                        banquise[i-1][j].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau que le marteau s'est stoppé
                        banquise[i-1][j-1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                        banquise[i-1][j-1].typeObjet->vecteur.dy = 0;
                        banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête
                    }

                    if(continu !=0) // Si il n'y en a pas, on effectue le déplacement du marteau avec la mort des joueurs
                    {

                        // MORT DES JOUEURS

                        if(banquise[i][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i) && (tableau_joueur[compteur].position.y==j-1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i][j-1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i-1][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i-1) && (tableau_joueur[compteur].position.y==j-1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i-1][j-1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }
                        if(banquise[i-2][j-1].occupe!=NULL) // On regarde si un joueur va mourir sur la case
                        {
                            for(compteur=0; compteur<nombre_joueur; compteur++)
                            {
                                if((tableau_joueur[compteur].position.x==i-2) && (tableau_joueur[compteur].position.y==j-1))
                                {
                                    tableau_joueur[compteur].etat=0;
                                    banquise[i-2][j-1].occupe=NULL;
                                    printf("\n\nUn joueur est mort\n\n");
                                }
                            }
                        }

                        // PARTI DEPLACEMENT DU MARTEAU

                        banquise[i-1][j-1].typeObjet = (T_objet*)(malloc(sizeof(T_objet)));
                        banquise[i-1][j-1].typeObjet = banquise[i][j].typeObjet;  // On copie les donnée de l'ancienne tête à sa nouvelle place

                        banquise[i-1][j].typeObjet->position.x = i-1; // On indique à l'axe où se trouve la nouvelle t^te de marteau
                        banquise[i-1][j].typeObjet->position.y = j-1;

                        banquise[i][j].typeObjet = NULL; // On supprime l'ancienne tête

                        if(banquise[i-2][j-1].typeObjet!=NULL)
                        {
                            if(banquise[i-2][j-1].typeObjet->objet==0) // Si on rencontre un glaçon, on le fait bouger et on arrête le marteau
                            {
                                deplacementGlacon(banquise, i-2, j-1, -1, 0, tailleBanquise, tableau_joueur, nombre_joueur);
                                banquise[i-1][j].typeObjet->nbTourMarteau = 0;  // On indique à l'axe du marteau qu'il doit s'arrêter
                                banquise[i-1][j-1].typeObjet->vecteur.dx = 0;  // On donne une nouvelle direction à la tête
                                banquise[i-1][j-1].typeObjet->vecteur.dy = 0;

                            }
                            else
                            {
                                banquise[i-1][j].typeObjet->nbTourMarteau = nombreDeDeplacementRestant-1;;  // On indique à l'axe du marteau le nombre de déplacement à faire restant
                                banquise[i-1][j-1].typeObjet->vecteur.dx = -1;  // On donne une nouvelle direction à la tête
                                banquise[i-1][j-1].typeObjet->vecteur.dy = 0;
                                if(banquise[i-1][j].typeObjet->nbTourMarteau==0)
                                {
                                  banquise[i-1][j-1].typeObjet->vecteur.dx = 0;
                                  banquise[i-1][j-1].typeObjet->vecteur.dy = 0;
                                }
                            }
                        }
                        else // Sinon on change son nombre de déplacement
                        {
                            banquise[i-1][j].typeObjet->nbTourMarteau = nombreDeDeplacementRestant-1;;  // On indique à l'axe du marteau le nombre de déplacement à faire restant
                            banquise[i-1][j-1].typeObjet->vecteur.dx = -1;  // On donne une nouvelle direction à la tête
                            banquise[i-1][j-1].typeObjet->vecteur.dy = 0;
                            if(banquise[i-1][j].typeObjet->nbTourMarteau==0)
                            {
                              banquise[i-1][j-1].typeObjet->vecteur.dx = 0;
                              banquise[i-1][j-1].typeObjet->vecteur.dy = 0;
                            }
                        }
                    }
                }
            }
            else
            {
                printf("\n\nERROR dans la fonction deplacementMarteau, casMarteau non trouve\n\n");
            }
        }
        else // Si le marteau ne peut pas bouger, on l'arrête
        {
            banquise[banquise[i][j].typeObjet->position.x][banquise[i][j].typeObjet->position.y].typeObjet->nbTourMarteau = 0;
            banquise[i][j].typeObjet->vecteur.dx = 0;
            banquise[i][j].typeObjet->vecteur.dy = 0;
        }
    }
}
//Si un objet empèche un déplacement, renvoie 1, sinon, si l'emplacement est libre, renvoie 0
int objetEmpecheDeplacement(T_case **banquise, int i, int j)
{
    if(banquise[i][j].typeObjet==NULL)
    {
        return 0;
    }
    else if((banquise[i][j].typeObjet->objet==0) || (banquise[i][j].typeObjet->objet==1) || (banquise[i][j].typeObjet->objet==3))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
