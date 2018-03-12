#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>


#define TAILLE_BLOC         32
#define NB_BLOCS_LARGEUR    11
#define NB_BLOCS_HAUTEUR    11
#define LARGEUR_FENETRE     32 * 11
#define HAUTEUR_FENETRE     32 * 11
#define OBSTACLE 1
#define IA 5

enum {VIDE, MUR, BONUS, MALUS, SPAWN};
enum{HAUT, BAS, GAUCHE, DROITE};

void pause();
void deplacer_joueur(int carte[NB_BLOCS_HAUTEUR ][NB_BLOCS_LARGEUR], int direction, SDL_Rect *position);


int main(int argc, char *argv[])
{
    int carte[11][11] = {0};
    int i, j;
    int continuer = 1;

    for(i = 0; i < NB_BLOCS_HAUTEUR; i++)
    {
        for(j = 0; j < NB_BLOCS_LARGEUR; j++)
        {
            carte[i][j] = VIDE;
        }
    }


    SDL_Surface *ecran = NULL, *mur = NULL, *bonus = NULL, *malus = NULL, *spawn = NULL, *imageDeFond = NULL, *ia[4], *vide;
    SDL_Rect positionMap, positionFond, positionjoueur;
    SDL_Event event;

    positionFond.x = 0;
    positionFond.y = 0;


    SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL

    ecran = SDL_SetVideoMode(640, 375, 32, SDL_HWSURFACE); // Ouverture de la fenÍtre
    SDL_WM_SetCaption("NUKETOWN2022", NULL);

    imageDeFond = SDL_LoadBMP("Fond.bmp");
  //  On blitte par-dessus l'Ècran /
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

  // SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));


// Placement des objets ‡ l'Ècran
carte[0][0] = 1;
carte[0][1] = 1;
carte[0][2] = 1;
carte[0][3] = 1;
carte[0][4] = 1;
carte[0][5] = 1;
carte[0][6] = 1;
carte[0][7] = 1;
carte[0][8] = 1;
carte[0][9] = 1;
carte[0][10] = 1;
carte[1][0] = 1;
carte[1][1] = 3;
carte[1][2] = 2;/*
carte[1][3] = ;
carte[1][4] = ;
carte[1][5] = ;
carte[1][6] = ;
carte[1][7] = ;
carte[1][8] = ;
carte[1][9] = ;*/
carte[1][10] = 1;
carte[2][0] = 1;/*
carte[2][1] = ;
carte[2][2] = ;
carte[2][3] = ;
carte[2][4] = ;
carte[2][5] = ;
carte[2][6] = ;
carte[2][7] = ;
carte[2][8] = ;
carte[2][9] = ;*/
carte[2][10] = 1;
carte[3][0] = 1; /*
carte[3][1] = ;
carte[3][2] = ;
carte[3][3] = ;
carte[3][4] = ;
carte[3][5] = ;
carte[3][6] = ;*/
carte[3][7] =4 ;/*
carte[3][8] = ;*/
carte[3][9] = 3;
carte[3][10] = 1;
carte[4][0] = 1; /*
carte[4][1] = ;
carte[4][2] = ;
carte[4][3] = ;
carte[4][4] = ;
carte[4][5] = ;
carte[4][6] = ;
carte[4][7] = ;
carte[4][8] = ;
carte[4][9] = ;*/
carte[4][10] = 1;
carte[5][0] = 1; /*
carte[5][1] = ;
carte[5][2] = ;
carte[5][3] = ;
carte[5][4] = ;
carte[5][5] = ;*/
carte[5][6] =1 ;
carte[5][7] =1 ;/*
carte[5][8] = ;
carte[5][9] = ;*/
carte[5][10] = 1;
carte[6][0] = 1; /*
carte[6][1] = ;
carte[6][2] = ;
carte[6][3] = ;
carte[6][4] = ;
carte[6][5] = ;
carte[6][6] = ;
carte[6][7] = ;
carte[6][8] = ;
carte[6][9] = ;*/
carte[6][10] = 1;
carte[7][0] = 1;
carte[7][1] = 4;/*
carte[7][2] = ;
carte[7][3] = ;*/
carte[7][4] = 3;/*
carte[7][5] = ;
carte[7][6] = ;
carte[7][7] = ;
carte[7][8] = ;
carte[7][9] = ;*/
carte[7][10] = 1;
carte[8][0] = 1; /*
carte[8][1] = ;*/
carte[8][2] = 1;/*
carte[8][3] = ;
carte[8][4] = ;
carte[8][5] = ;
carte[8][6] = ;*/
carte[8][7] =2 ;/*
carte[8][8] = ;
carte[8][9] = ;*/
carte[8][10] = 1;
carte[9][0] = 1;
/*carte[9][1] = ;
carte[9][2] = ;*/
carte[9][3] = 4 ;/*
carte[9][4] = ;
carte[9][5] = ;*/
carte[9][6] = 2;
/*carte[9][7] = ;
carte[9][8] = ;
carte[9][9] = ;*/
carte[9][10] = 1;
carte[10][0] = 1;
carte[10][1] = 1;
carte[10][2] = 1;
carte[10][3] = 1;
carte[10][4] = 1;
carte[10][5] = 1;
carte[10][6] = 1;
carte[10][7] = 1;
carte[10][8] = 1;
carte[10][9] = 1;
carte[10][10] = 1;
carte[5][5] = 5;

positionjoueur.x = 5;
positionjoueur.y = 5;
mur = SDL_LoadBMP("mur.bmp");
bonus = SDL_LoadBMP("bonus.bmp");
malus = SDL_LoadBMP("malus.bmp");
spawn = SDL_LoadBMP("spawn.bmp");

ia[BAS] = SDL_LoadBMP("ia_bas.bmp");
ia[HAUT] = SDL_LoadBMP("ia_haut.bmp");
ia[GAUCHE] = SDL_LoadBMP("ia_gauche.bmp");
ia[DROITE] = SDL_LoadBMP("ia_droite.bmp");
vide = SDL_LoadBMP("vide.bmp");
SDL_Surface *iaactuel = ia[BAS];
int point = 0;





        while(continuer)
        {
            SDL_SetColorKey(iaactuel, SDL_SRCCOLORKEY, SDL_MapRGB(iaactuel->format, 255, 255, 255));
            SDL_WaitEvent(&event);
            while(event.type != SDL_KEYDOWN)
            {
                SDL_WaitEvent(&event);
            }

            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    exit(EXIT_SUCCESS);
                    break;
                case SDLK_UP:
                    if(carte[positionjoueur.x][positionjoueur.y - 1] == 2)
                    {
                        point++;
                    }
                    if(carte[positionjoueur.x][positionjoueur.y - 1] == 3)
                    {
                        point--;
                    }
                    deplacer_joueur(carte, HAUT, &positionjoueur);
                    iaactuel = ia[HAUT];
                    break;
                case SDLK_DOWN:
                    if(carte[positionjoueur.x][positionjoueur.y + 1] == 2)
                    {
                        point++;
                    }
                    if(carte[positionjoueur.x][positionjoueur.y + 1] == 3)
                    {
                        point--;
                    }
                    deplacer_joueur(carte, BAS, &positionjoueur);
                    iaactuel = ia[BAS];
                    break;
                case SDLK_LEFT:
                    if(carte[positionjoueur.x - 1][positionjoueur.y] == 2)
                    {
                        point++;
                    }
                    if(carte[positionjoueur.x - 1][positionjoueur.y] == 3)
                    {
                        point--;
                    }
                    deplacer_joueur(carte, GAUCHE, &positionjoueur);
                    iaactuel = ia[GAUCHE];
                    break;
                case SDLK_RIGHT:
                    if(carte[positionjoueur.x + 1][positionjoueur.y] == 2)
                    {
                        point++;
                    }
                    if(carte[positionjoueur.x + 1][positionjoueur.y] == 3)
                    {
                        point--;
                    }
                    deplacer_joueur(carte, DROITE, &positionjoueur);
                    iaactuel = ia[DROITE];
                    break;
            }
        for (i = 0 ; i < 11 ; i++)
        {
            for (j = 0 ; j < 11 ; j++)
            {
                positionMap.x = i * 32;
                positionMap.y = j * 32;

                switch(carte[i][j])
                {
                    case 1:
                        SDL_BlitSurface(vide, NULL, ecran, &positionMap);
                        SDL_BlitSurface(mur, NULL, ecran, &positionMap);
                        break;

                    case 2:
                        SDL_BlitSurface(vide, NULL, ecran, &positionMap);
                        SDL_BlitSurface(bonus, NULL, ecran, &positionMap);
                        break;

                    case 3:
                        SDL_BlitSurface(vide, NULL, ecran, &positionMap);
                        SDL_BlitSurface(malus, NULL, ecran, &positionMap);
                        break;

                    case 4:
                        SDL_BlitSurface(vide, NULL, ecran, &positionMap);
                        SDL_BlitSurface(spawn, NULL, ecran, &positionMap);
                        break;
                    case 5:
                        SDL_BlitSurface(vide, NULL, ecran, &positionMap);
                        SDL_BlitSurface(iaactuel, NULL, ecran, &positionMap);
                        break;
                    case VIDE:
                        SDL_BlitSurface(vide, NULL, ecran, &positionMap);
                        break;
                }
            }

        }
    SDL_Flip(ecran);
        }

    SDL_FreeSurface(mur);
    SDL_FreeSurface(bonus);
    SDL_FreeSurface(malus);
    SDL_FreeSurface(spawn);






    SDL_Quit(); // ArrÍt de la SDL



    return EXIT_SUCCESS; // Fermeture du programme
}


void deplacer_joueur(int carte[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR], int direction, SDL_Rect *position)
{

    switch(direction)
    {
    case HAUT:
        if((position->y - 1) < 0 || carte[position->x][position->y - 1] == OBSTACLE || carte[position->x][position->y - 1] == 4 )
        {
            break;
        }
        carte[position->x][position->y] = VIDE;
        carte[position->x][position->y - 1] = IA;
        position->y--;
        break;
    case BAS:
        if((position->y + 1) > NB_BLOCS_LARGEUR - 1 || carte[position->x][position->y + 1] == OBSTACLE || carte[position->x][position->y + 1] == 4)
        {
            break;
        }
        carte[position->x][position->y] = VIDE;
        carte[position->x][position->y + 1] = IA;
        position->y++;
        break;
    case GAUCHE:
        if((position->x - 1) < 0 || carte[position->x - 1 ][position->y] == OBSTACLE || carte[position->x - 1 ][position->y] == 4)
        {
            break;
        }
        carte[position->x][position->y] = VIDE;
        carte[position->x - 1][position->y] = IA;
        position->x--;
        break;
    case DROITE:
        if((position->x + 1) > NB_BLOCS_HAUTEUR - 1 || carte[position->x + 1 ][position->y] == OBSTACLE || carte[position->x + 1 ][position->y] == 4)
        {
            break;
        }
        carte[position->x + 1][position->y] = IA;
        carte[position->x][position->y] = VIDE;
        position->x++;
        break;
    }
}
