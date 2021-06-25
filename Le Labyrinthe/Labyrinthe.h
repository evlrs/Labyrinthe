#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define LARGEUR 1500
#define HAUTEUR 800

#define LIGNE 50
#define COLONE 40


SDL_Window *window;
SDL_Renderer *renderer;

int Init_Window(char *titre, int larg, int longr);

SDL_Texture *Init_Texture(char *img);

void Init_Rect_Mur(SDL_Rect *etat, SDL_Rect *source);

void affi_Mur(int tab[LIGNE][COLONE], SDL_Texture *Mur, SDL_Rect *source, SDL_Rect *dest);

void affi_Parc(int tab[LIGNE][COLONE], SDL_Rect *colo,int max);

void affi_Tex(int tab[LIGNE][COLONE]);