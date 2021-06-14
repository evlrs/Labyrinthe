#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
void creaFenetre(SDL_Window* window, int largeur, int longeur, int x, int y );

int main(){

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }
    
    SDL_Window *win = NULL;
    creaFenetre(win,0,0,600,600);

    SDL_Renderer* renderer = NULL;
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == 0) {
     fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    }

    SDL_Rect rect;
    /* couleur de fond */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    /* dessiner en blanc */
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    rect.x = rect.y = 0;
    rect.w = rect.h = 600;
    SDL_RenderFillRect(renderer, &rect );

    /* afficher à l'ecran */
    SDL_RenderPresent(renderer);
    SDL_Delay(500);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
}

void creaFenetre(SDL_Window* window, int largeur, int longeur, int x, int y )
{
  window = SDL_CreateWindow("Fenêtre", x, y, largeur, longeur, 0);
 
  if (window == NULL) {
    SDL_Log("Error : SDL window creation - %s\n", SDL_GetError());   
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
}