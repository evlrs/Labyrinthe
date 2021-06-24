#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define LARGEUR 400
#define HAUTEUR 400

#define LIGNE 5
#define COLONE 5

SDL_Window *window;
SDL_Renderer *renderer;

int Init_Window(char *titre, int larg, int longr);

SDL_Texture *Init_Texture(char *img);

void Init_Rect_Mur(SDL_Rect *etat, SDL_Rect *source);

void Init_Tab(int tab[LIGNE][COLONE]);

void affi_Tex(int tab[LIGNE][COLONE]);

void affi_Gra(int tab[LIGNE][COLONE], SDL_Texture *Mur, SDL_Rect *source, SDL_Rect *dest);

void Init_SDL_Laby(int Grille[LIGNE][COLONE]);