#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

//#include "Labyrinthe.h"
//#include "Gene_Laby.h"


#define LARGEUR 1200
#define HAUTEUR 600

#define LIGNE 20
#define COLONE 25


#define D (1900 / COLONE)
#define NAR ((COLONE - 1) * LIGNE + (LIGNE - 1) * COLONE) //Nb aretes


int Init_Window(char * titre);
SDL_Texture * Init_Texture( char * img);
void Aff_textu_full(SDL_Texture * Texture);
void deplacement(int i,SDL_Texture * character1, SDL_Rect etat[],SDL_Texture* Fond,SDL_Rect * dest,SDL_Rect * destination);