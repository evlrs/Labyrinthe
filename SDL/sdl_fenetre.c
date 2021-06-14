#include <SDL2/SDL.h>
#include <stdio.h>

/************************************/
/*  exemple de création de fenêtres */
/************************************/

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  SDL_Window *window_1 = NULL,              
      *window_2 = NULL,
      *window_3 = NULL,
      *window_4 = NULL,
      *window_5 = NULL,
      *window_6 = NULL,
      *window_7 = NULL,
      *window_8 = NULL,
      *window_9 = NULL,
      *window_10 = NULL,
      *window_11 = NULL,
      *window_12 = NULL;                      

    SDL_Window* W=[window_1,window_2];
  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }

  /* Création de la fenêtre de gauche */
  window_1 = SDL_CreateWindow(
      "Fenêtre à gauche",                    // codage en utf8, donc accents possibles
      0, 0,                                  // coin haut gauche en haut gauche de l'écran
      200, 200,                              // largeur = 400, hauteur = 300
      SDL_WINDOW_RESIZABLE);                 // redimensionnable

  if (window_1 == NULL) {
    SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  /* Création de la fenêtre de droite */
  window_2 = SDL_CreateWindow(
      "Fenêtre à droite",                    // codage en utf8, donc accents possibles
      100, 100,                                // à droite de la fenêtre de gauche
      200, 200,                              // largeur = 500, hauteur = 300
      0);

  if (window_2 == NULL) {
    /* L'init de la SDL : OK
       fenêtre 1 :OK
       fenêtre 2 : échec */
    SDL_Log("Error : SDL window 2 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre 
    SDL_DestroyWindow(window_1);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

  window_2 = SDL_CreateWindow(
      "Fenêtre à droite",                    
      100, 100,                                
      200, 200,                             
      0);

  if (window_2 == NULL) {
    /* L'init de la SDL : OK
       fenêtre 1 :OK
       fenêtre 2 : échec */
    SDL_Log("Error : SDL window 2 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre 
    SDL_DestroyWindow(window_1);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }



  /* Normalement, on devrait ici remplir les fenêtres... */
  SDL_Delay(2000);                           // Pause exprimée  en ms

  /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
  SDL_DestroyWindow(window_2);
  SDL_DestroyWindow(window_1);

  SDL_Quit();
  return 0;
}
