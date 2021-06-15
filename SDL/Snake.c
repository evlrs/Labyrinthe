#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define LARGEUR 600
#define LONGEUR 600
#define COULEUR 6
#define TAILLE_H 20
#define TAILLE_W 60



SDL_Window   *window;
SDL_Renderer *renderer;

int Init_Window()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        fprintf(stderr,"Erreur d'initialisation de la SDL : %s \n",SDL_GetError());
        return EXIT_FAILURE;
    }
    window = SDL_CreateWindow("SDL Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
            LARGEUR, LARGEUR, 
            SDL_WINDOW_RESIZABLE); 
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

void draw (int X, int Y)
{
    SDL_Rect rect;
    SDL_Rect in_rect;

    int direction = 0;
    int nb_iter = 200;

    int R,V,B;  int color=0;
    int w=TAILLE_W;
    int h=TAILLE_H;
    srand(time(NULL));

    for (int i = 0; i < nb_iter; i++)
    {
        color = rand()%COULEUR;
        switch (color)
            {
            case 0 :
                R=0;
                V=0;
                B=0;
                break;
            case 1 :
                R=255;
                V=0;
                B=0;
                break;
            case 2 :
                R=0;
                V=255;
                B=0;
                break;
            case 3 :
                R=255;
                V=255;
                B=0;
                break;
            case 4 :
                R=0;
                V=0;
                B=255;
                break;
            case 5 :
                R=255;
                V=0;
                B=255;
                break;
            default:
                break;
            }
        
        SDL_SetRenderDrawColor(renderer, R, V, B, 0);
        rect.x = X;
        rect.y = Y;
        rect.w = w;
        rect.h = h;
        SDL_RenderFillRect(renderer, &rect );
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        in_rect.x = X+1;
        in_rect.y = Y+1;
        in_rect.w = w-2;
        in_rect.h = h-2;
        SDL_RenderFillRect(renderer, &in_rect );
        /* afficher à l'ecran */
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        SDL_RenderClear(renderer);
        
        if(1==rand()%3)
            direction = rand()%4;

        switch (direction)
            {
            case 0 :
                if (X<= LARGEUR-100)
                {
                    w=TAILLE_W;
                    h=TAILLE_H;
                    X=X+15;
                }
                break;
            case 1 :
               if (Y<= LONGEUR-100)
                {
                    w=TAILLE_H;
                    h=TAILLE_W;
                    Y=Y+15;
                }
                break;
            case 2 :
                if(X <= 0)
                {
                    w=TAILLE_W;
                    h=TAILLE_H;
                    X=X-15;
                }
                break;
            case 3 :
                if (Y <= 0)
                {
                    w=TAILLE_H;
                    h=TAILLE_W;
                    Y=Y-15;
                }
                break;
            }
        
    }

}

int main ()
{
    Init_Window();

    draw(10,10);

    SDL_Delay(500);

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return(0);
}