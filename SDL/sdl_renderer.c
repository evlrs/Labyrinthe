#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(){

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }
    
  SDL_Window *win = NULL;
  win = SDL_CreateWindow("Fenêtre", 0, 0, 700, 700, 0);
 
  if (win == NULL) {
    SDL_Log("Error : SDL window creation - %s\n", SDL_GetError());   
    SDL_DestroyWindow(win);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  SDL_Renderer *renderer;
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
  rect.x = rect.y = 300;
  rect.w = rect.h = 100;
  SDL_RenderFillRect(renderer, &rect );

  /* afficher à l'ecran */
  SDL_RenderPresent(renderer);
  SDL_Delay(500);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
}
