#include <SDL2/SDL.h>
#include <stdio.h>
void creaFenetre(SDL_Window* window, int largeur, int longeur, int x, int y );
/************************************/
/*  exemple de création de fenêtres */
/************************************/

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
    
  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }
  
  SDL_Window *window = NULL;
  int i;
  for(i=0;i<9;++i){
    creaFenetre(window,200,200,i*100,i*100);
    SDL_Delay(100);
    SDL_DestroyWindow(window);
  }
  for(i=0;i<9;++i){
    creaFenetre(window,200,200,800-i*100,i*100);
    SDL_Delay(100);
    SDL_DestroyWindow(window);
  }

  /* Normalement, on devrait ici remplir les fenêtres... */
  SDL_Delay(500);                           // Pause exprimée  en ms

  /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}

void creaFenetre(SDL_Window* window, int largeur, int longeur, int x, int y )
{
  window = SDL_CreateWindow("Fenêtre X", x, y, largeur, longeur, 0);
 
  if (window == NULL) {
    SDL_Log("Error : SDL window creation - %s\n", SDL_GetError());   
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
}