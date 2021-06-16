#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define LARGEUR 200
#define LONGEUR 200
#define COULEUR 6
#define TAILLE 12


SDL_Window   *window;


int Init_Window(int decal_d, int decal_g)
{

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        fprintf(stderr,"Erreur d'initialisation de la SDL : %s \n",SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("SDL Programme 0.1", decal_d, decal_g, 
            LARGEUR, LONGEUR, 
            SDL_WINDOW_RESIZABLE); 
    
    if (window == 0) 
    {
        fprintf(stderr,"Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    }

    return(0); 
}

int main ()
{
    int X_fin = 1200;
    int X_debut = 0;
    for (int i = 0; i < 1100; i=i+100)
    {
        Init_Window(X_fin-i,i/2);
        Init_Window(X_debut+i,i/2);
    }

    SDL_Delay(5000);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return(0);
}