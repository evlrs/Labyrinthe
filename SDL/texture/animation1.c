#include <SDL2/SDL_image.h>               // Nécessaire pour la fonction IMG_Load
                                            // Penser au flag -lsdl2_image
#include <math.h>
#include <stdio.h>
#include <string.h>

#define M_PI 3.14159265358979323846

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

void play_with_texture_1(SDL_Texture *my_texture) {
  SDL_Rect 
          source = {0},                         // Rectangle définissant la zone de la texture à récupérer
          window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
          destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(my_texture, NULL, NULL,
                   &source.w, &source.h);       // Récupération des dimensions de l'image

  destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

  /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

  SDL_RenderCopy(renderer, my_texture,
                 &source,
                 &destination);                 // Création de l'élément à afficher
  //SDL_RenderPresent(renderer);                  // Affichage
  //SDL_Delay(30);                              // Pause en ms

  //SDL_RenderClear(renderer);                    // Effacer la fenêtre
}

void play_with_texture(SDL_Texture* my_texture, SDL_Texture* bg_texture){
    SDL_Rect 
        source = {0},                    // Rectangle définissant la zone totale de la planche
        window_dimensions = {0},         // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};               // Rectangle définissant où la zone_source doit être déposée dans le renderer
        //state = {0};                     // Rectangle de la vignette en cours dans la planche 

    SDL_GetWindowSize(window,              // Récupération des dimensions de la fenêtre
                        &window_dimensions.w,
                        &window_dimensions.h);
    SDL_QueryTexture(my_texture,           // Récupération des dimensions de l'image
                    NULL, NULL,
                    &source.w, &source.h);
            
    
    float zoom = 2;                        // zoom, car ces images sont un peu petites
    int offset_x = 70,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
        offset_y = 99;           // La hauteur d'une vignette de l'image, marche car la planche est bien réglée
 
    SDL_Rect state[6];                     // Tableau qui stocke les vignettes dans le bon ordre pour l'animation

    destination.w = offset_x * zoom;       // Largeur du sprite à l'écran
    destination.h = offset_y * zoom;       // Hauteur du sprite à l'écran


    state[0].y= 0;
    state[1].y= 100;
    state[2].y= 195;
    state[3].y= 295; 
    state[4].y= state[2].y;
    state[5].y= state[1].y;
    state[0].h=offset_y;
    state[1].h=offset_y-2;
    state[2].h=offset_y;
    state[3].h=offset_y-6;
    state[4].h=state[2].h;
    state[5].h=state[1].h;

    int nb_it=120;
    for (int i = -nb_it; i < nb_it; ++i) {
        destination.x = 2*(i+nb_it) ;
        destination.y = 100 + 400*sin(i*0.2)/(i*0.2);
        state[(i+6*nb_it)%6].x=0;
        state[(i+6*nb_it)%6].w=offset_x-1;
    
        SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
        play_with_texture_1(bg_texture); 
        SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                        &state[(i+6*nb_it)%6],
                        &destination);
        
        SDL_RenderPresent(renderer);         // Affichage
        SDL_Delay(30);                       // Pause en ms
    }
    
 

    SDL_RenderClear(renderer);
}

int main(){
    //SDL_Window *window = NULL;
    //SDL_Renderer *renderer = NULL;
    SDL_Texture *my_texture = NULL; 
    SDL_Texture *bg_texture = NULL;

    window = SDL_CreateWindow("Fenêtre", 0, 0, 700, 700, 0);
    if (window == NULL) {
        SDL_Log("Error : SDL window creation - %s\n", SDL_GetError());   
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == 0) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    }

    my_texture = IMG_LoadTexture(renderer,"./image/alienBeige.png");
    //if (my_texture == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    bg_texture = IMG_LoadTexture(renderer,"./image/nasa-xFO2Xt33xgI-unsplash.jpg");
    //if (bg_texture == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);


    play_with_texture(my_texture,bg_texture);
    SDL_DestroyTexture(my_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();                                // Si on charge une librairie SDL, il faut penser à la décharger   
    
}