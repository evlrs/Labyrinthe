#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

#define LARGEUR 1000
#define HAUTEUR 600

SDL_Window   *window =NULL;
SDL_Renderer *renderer= NULL;
SDL_Texture * Texture = NULL;

int Init_Window()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        fprintf(stderr,"Erreur d'initialisation de la SDL : %s \n",SDL_GetError());
        return EXIT_FAILURE;
    }
    window = SDL_CreateWindow("SDL Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR, HAUTEUR,SDL_WINDOW_RESIZABLE); 
        if (window == 0) 
        {
            fprintf(stderr,"Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
        }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED ); /*  SDL_RENDERER_SOFTWARE */
        if (renderer == 0) 
        {
            fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
            SDL_DestroyWindow(window); 
        }
        
        /* couleur de fond */
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(5); 
    return(0);
}

void Init_Texture()
{
    SDL_Surface * Image = NULL;

    Image = IMG_Load("./Image/player-spritemap-v9.png");
    if (Image == 0) 
    {
        fprintf(stderr, "Erreur chargement image : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer); 
    }
    Texture = SDL_CreateTextureFromSurface(renderer,Image);
    if (Image == 0) 
    {
        fprintf(stderr, "Erreur chargement texture : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer); 
    }
    SDL_FreeSurface(Image);
}

void animation()
{
    SDL_Rect dest={0};
    SDL_Rect window_dim={0};
    SDL_Rect source={0};
    SDL_Rect etat={0};

    SDL_GetWindowSize(window, &window_dim.w,&window_dim.h);                    
    SDL_QueryTexture(Texture, NULL, NULL, &source.w, &source.h);       

    dest = window_dim;
}