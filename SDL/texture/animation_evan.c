#include <SDL2/SDL_image.h>               // Nécessaire pour la fonction IMG_Load
                                            // Penser au flag -lsdl2_image
#include <math.h>
#include <stdio.h>
#include <string.h>

#define M_PI 3.14159265358979323846

void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window,
                         SDL_Renderer *renderer) {
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
  SDL_RenderPresent(renderer);                  // Affichage
  SDL_Delay(60);                              // Pause en ms

  //SDL_RenderClear(renderer);                    // Effacer la fenêtre
}


void play_with_texture_2(SDL_Texture* my_texture,
                            SDL_Window* window,
                            SDL_Renderer* renderer) {
     SDL_Rect 
           source = {0},                      // Rectangle définissant la zone de la texture à récupérer
           window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
           destination = {0};                 // Rectangle définissant où la zone_source doit être déposée dans le renderer

     SDL_GetWindowSize(
         window, &window_dimensions.w,
         &window_dimensions.h);               // Récupération des dimensions de la fenêtre
     SDL_QueryTexture(my_texture, NULL, NULL,
                      &source.w, &source.h);  // Récupération des dimensions de l'image

     float zoom = 9;                        // Facteur de zoom à appliquer    
     destination.w = source.w * zoom;         // La destination est un zoom de la source
     destination.h = source.h * zoom;         // La destination est un zoom de la source
     destination.x =
       (window_dimensions.w - destination.w) /2;     // La destination est au milieu de la largeur de la fenêtre
     destination.y =
         (window_dimensions.h - destination.h) / 2;  // La destination est au milieu de la hauteur de la fenêtre

     SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                    &source,
                    &destination);            
     SDL_RenderPresent(renderer);             
     SDL_Delay(1000);                         

     SDL_RenderClear(renderer);               // Effacer la fenêtre
}

void play_with_texture_3(SDL_Texture* my_texture,
                         SDL_Window* window,
                         SDL_Renderer* renderer) {
  SDL_Rect 
        source = {0},                             // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},                  // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(                                
      window, &window_dimensions.w,                 
      &window_dimensions.h);                      // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(my_texture, NULL, NULL,         
                   &source.w,                       
                   &source.h);                    // Récupération des dimensions de l'image

  /* On décide de déplacer dans la fenêtre         cette image */
  float zoom = 0.75;                              // Facteur de zoom entre l'image source et l'image affichée

  int nb_it = 200;                                // Nombre d'images de l'animation
  destination.w = source.w * zoom;                // On applique le zoom sur la largeur
  destination.h = source.h * zoom;                // On applique le zoom sur la hauteur
  destination.x =                                   
      (window_dimensions.w - destination.w) / 2;  // On centre en largeur
  float h = window_dimensions.h - destination.h;  // hauteur du déplacement à effectuer

  for (int i = 0; i < nb_it; ++i) {
    destination.y =
        h * (1 - exp(-5.0 * i / nb_it) / 2 *
                     (1 + 0.25*cos(57.0 * i / nb_it * 2 *
                              M_PI)));            // hauteur en fonction du numéro d'image

    SDL_RenderClear(renderer);                    // Effacer l'image précédente

    SDL_SetTextureAlphaMod(my_texture,(0.5-1*i/nb_it)*255);      // L'opacité va passer de 255 à 0 au fil de l'animation
    SDL_RenderCopy(renderer, my_texture, &source, &destination);   // Préparation de l'affichage
    SDL_RenderPresent(renderer);                  // Affichage de la nouvelle image
    SDL_Delay(50);                                // Pause en ms
  }                                                 
  SDL_RenderClear(renderer);                      // Effacer la fenêtre une fois le travail terminé
}

void play_with_texture_4(SDL_Texture* my_texture,
                         SDL_Window* window,
                         SDL_Renderer* renderer) {
    SDL_Rect 
            source = {0},                    // Rectangle définissant la zone totale de la planche
            window_dimensions = {0},         // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
            destination = {0},               // Rectangle définissant où la zone_source doit être déposée dans le renderer
            state = {0};                     // Rectangle de la vignette en cours dans la planche 

    SDL_GetWindowSize(window,              // Récupération des dimensions de la fenêtre
                        &window_dimensions.w,
                        &window_dimensions.h);
    SDL_QueryTexture(my_texture,           // Récupération des dimensions de l'image
                    NULL, NULL,
                    &source.w, &source.h);

    /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

    int nb_images = 8;                     // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
    float zoom = 2;                        // zoom, car ces images sont un peu petites
    int offset_x = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
        offset_y = source.h / 4;           // La hauteur d'une vignette de l'image, marche car la planche est bien réglée


    state.x = 0 ;                          // La première vignette est en début de ligne
    state.y = 0 * offset_y;                // On s'intéresse à la 4ème ligne, le bonhomme qui court
    state.w = offset_x;                    // Largeur de la vignette
    state.h = offset_y;                    // Hauteur de la vignette

    destination.w = offset_x * zoom;       // Largeur du sprite à l'écran
    destination.h = offset_y * zoom;       // Hauteur du sprite à l'écran

    destination.y =                        // La course se fait en milieu d'écran (en vertical)
        (window_dimensions.h - destination.h) /2;

    int speed = 9;
    for (int x = 0; x < window_dimensions.w - destination.w; x += speed) {
        destination.x = x;                   // Position en x pour l'affichage du sprite
        state.x += offset_x;                 // On passe à la vignette suivante dans l'image
        state.x %= source.w;                 // La vignette qui suit celle de fin de ligne est
                                            // celle de début de ligne
        SDL_RenderClear(renderer); 
        
        SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                        &state,
                        &destination);  
        SDL_Delay(20);
        SDL_RenderPresent(renderer);         // Affichage
        SDL_Delay(60);
                               // Pause en ms
    }
    SDL_RenderClear(renderer);             // Effacer la fenêtre avant de rendre la main
}


void play_with_texture_5(SDL_Texture *bg_texture,
                           SDL_Texture *my_texture,
                           SDL_Window *window,
                           SDL_Renderer *renderer) {
    SDL_Rect
    source = {0},                             // Rectangle définissant la zone de la texture à récupérer
    window_dimensions = {0},                  // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
    destination = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(window,                   // Récupération des dimensions de la fenêtre
                    &window_dimensions.w, 
                    &window_dimensions.h); 
    SDL_QueryTexture(my_texture, NULL, NULL,    // Récupération des dimensions de l'image
                    &source.w, &source.h); 

    int nb_images = 40;                         //  Il y a 8 vignette dans la ligne qui nous intéresse
    int nb_images_animation = 1 * nb_images;    // 
    float zoom = 2;                             // zoom, car ces images sont un peu petites
    int offset_x = source.w / 4,                // La largeur d'une vignette de l'image
        offset_y = source.h / 5;                // La hauteur d'une vignette de l'image
    SDL_Rect state[40];                         // Tableau qui stocke les vignettes dans le bon ordre pour l'animation

    /* construction des différents rectangles autour de chacune des vignettes de la planche */
    int i = 0;                                   
    for (int y = 0; y < source.h ; y += offset_y) {
        for (int x = 0; x < source.w; x += offset_x) {
            state[i].x = x;
            state[i].y = y;
            state[i].w = offset_x;
            state[i].h = offset_y;
            ++i;
        }
    }
    state[14] = state[13];                      // state[14 à 16] la même image, le monstre ne bouge pas   
    state[15] = state[16];                         
    for(; i< nb_images ; ++i){                  // reprise du début de l'animation en sens inverse  
    state[i] = state[39-i];
    SDL_Delay(15); 
    }

    destination.w = offset_x * zoom;            // Largeur du sprite à l'écran
    destination.h = offset_y * zoom;            // Hauteur du sprite à l'écran
    destination.x = window_dimensions.w * 0.75; // Position en x pour l'affichage du sprite
    destination.y = window_dimensions.h * 0.7;  // Position en y pour l'affichage du sprite

    i = 0;
    for (int cpt = 0; cpt < nb_images_animation ; ++cpt) {
    play_with_texture_1(bg_texture,         // identique à play_with_texture_1, où on a enlevé l'affichage et la pause
                            window, renderer); 
    SDL_RenderCopy(renderer,                  // Préparation de l'affichage
                    my_texture, &state[i], &destination);
    i = (i + 1) % nb_images;                  // Passage à l'image suivante, le modulo car l'animation est cyclique 
    SDL_RenderPresent(renderer);              // Affichage
    SDL_Delay(60);                           // Pause en ms
    }IMG_Quit();
    
    
    SDL_DestroyWindow(window);
    SDL_RenderClear(renderer);                  // Effacer la fenêtre avant de rendre la main
}

void animation(SDL_Texture *bg_texture,
                           SDL_Texture *my_texture,
                           SDL_Window *window,
                           SDL_Renderer *renderer) {
                               SDL_Rect
    source = {0},                             // Rectangle définissant la zone de la texture à récupérer
    window_dimensions = {0},                  // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
    destination = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(window,                   // Récupération des dimensions de la fenêtre
                    &window_dimensions.w, 
                    &window_dimensions.h); 
    SDL_QueryTexture(my_texture, NULL, NULL,    // Récupération des dimensions de l'image
                    &source.w, &source.h); 

    int nb_images = 9;                         //  Il y a 15 vignette dans la ligne qui nous intéresse
    int nb_images_animation =  * nb_images;    // 
    float zoom = 0;                             // zoom, car ces images sont un peu petites
    int offset_x = 140,                // La largeur d'une vignette de l'image
        offset_y = 190;                // La hauteur d'une vignette de l'image
    SDL_Rect state1[36];                         // Tableau qui stocke les vignettes dans le bon ordre pour l'animation
    

    /* construction des différents rectangles autour de chacune des vignettes de la planche */
    int i = 0;                                   
    for (int y = 0; y < (3*190) ; y += offset_y) {
        for (int x = 0; x < (5*140); x += offset_x) {
            state1[i].x = x;
            state1[i].y = y;
            state1[i].w = offset_x;
            state1[i].h = offset_y;
            ++i;
            
        }
    }


    
    //destination.w = offset_x * zoom;            // Largeur du sprite à l'écran
    //destination.h = offset_y * zoom;            // Hauteur du sprite à l'écran
    //destination.x = window_dimensions.w * 0.60; // Position en x pour l'affichage du sprite
    //destination.y = window_dimensions.h * 0.28;  // Position en y pour l'affichage du sprite

    i = 0;
    for (int cpt = 0; cpt < nb_images_animation ; ++cpt) {
        zoom=1+(sin(0.5*i))/3;
        destination.w = offset_x * zoom;            // Largeur du sprite à l'écran
        destination.h = offset_y * zoom;            // Hauteur du sprite à l'écran
        destination.x = window_dimensions.w * 0.50; // Position en x pour l'affichage du sprite
        destination.y = window_dimensions.h * 0.28;  // Position en y pour l'affichage du sprite
        play_with_texture_1(bg_texture,         // identique à play_with_texture_1, où on a enlevé l'affichage et la pause
                                window, renderer); 
        SDL_RenderCopy(renderer,                  // Préparation de l'affichage
                        my_texture, &state1[i], &destination);
        i = (i + 1) % nb_images;                  // Passage à l'image suivante, le modulo car l'animation est cyclique 
        SDL_RenderPresent(renderer);              // Affichage
        SDL_Delay(100);                           // Pause en ms
    }
    

    int nb_images2 = 28;                         //  Il y a 28 vignette dans la ligne qui nous intéresse
    int nb_images_animation2 = 1 * nb_images;    // 
                                // zoom, car ces images sont un peu petites
                   // La hauteur d'une vignette de l'image
    SDL_Rect state2[57];                         // Tableau qui stocke les vignettes dans le bon ordre pour l'animation

    /* construction des différents rectangles autour de chacune des vignettes de la planche */
    int j = 0;                                   
    for (int y = (3*190); y < (10*190) ; y += offset_y) {
        for (int x = 0; x < (4*140); x += offset_x) {
            state2[j].x = x;
            state2[j].y = y;
            state2[j].w = offset_x;
            state2[j].h = offset_y;
            ++j;
            
        }
    }
    

    //destination.w = offset_x * zoom;            // Largeur du sprite à l'écran
    //destination.h = offset_y * zoom;            // Hauteur du sprite à l'écran
    //destination.x = window_dimensions.w * 0.275; // Position en x pour l'affichage du sprite
    //destination.y = window_dimensions.h * 0.275;  // Position en y pour l'affichage du sprite

    j = 0;
    for (int cpt2 = 0; cpt2 < nb_images_animation2 ; ++cpt2) {
        zoom=1+cos(0.5*j))/3;
        destination.w = offset_x * zoom;            // Largeur du sprite à l'écran
        destination.h = offset_y * zoom;            // Hauteur du sprite à l'écran
        destination.x = window_dimensions.w * 0.48; // Position en x pour l'affichage du sprite
        destination.y = window_dimensions.h * 0.28;  // Position en y pour l'affichage du sprite
        play_with_texture_1(bg_texture,         // identique à play_with_texture_1, où on a enlevé l'affichage et la pause
                                window, renderer); 
        SDL_RenderCopy(renderer,                  // Préparation de l'affichage
                        my_texture, &state2[j], &destination);
        j = (j + 1) % nb_images;                  // Passage à l'image suivante, le modulo car l'animation est cyclique 
        SDL_RenderPresent(renderer);              // Affichage
        SDL_Delay(100);                           // Pause en ms
    }
    
    IMG_Quit();
    
    
    SDL_DestroyWindow(window);
    
    
    SDL_RenderClear(renderer);                  // Effacer la fenêtre avant de rendre la main
}                            






void end_sdl(char ok,                                                 // fin normale : ok = 0 ; anormale ok = 1
                 char const* msg,                                    // message à afficher
                    SDL_Window* window,                                 // fenêtre à fermer
                    SDL_Renderer* renderer) {                           // renderer à fermer
    char msg_formated[255];                                         
    int l;                                                          

    if (!ok) {                                                      
            strncpy(msg_formated, msg, 250);                                 
            l = strlen(msg_formated);                                        
            strcpy(msg_formated + l, " : %s\n");                     

            SDL_Log(msg_formated, SDL_GetError());                   
    }                                                               

    if (renderer != NULL) SDL_DestroyRenderer(renderer);                            
    if (window != NULL)   SDL_DestroyWindow(window);                                        

    SDL_Quit();                                                     

    if (!ok) {                                                      
        exit(EXIT_FAILURE);                                              
    }                                                               
} 

int main(){
    // ...
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    /*SDL_Texture *my_texture2 = NULL; */
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
    /*my_texture2 = IMG_LoadTexture(renderer,"./image/player-spritemap-v9-greenpants.png");
    if (my_texture2 == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);*/


    my_texture = IMG_LoadTexture(renderer,"./image/playingCards.png");
    if (my_texture == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    bg_texture = IMG_LoadTexture(renderer,"./image/fond-table-poker.png");
    if (bg_texture  == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    /*play_with_texture_4(my_texture5,window,renderer);*/
    /*play_with_texture_5(bg_texture,my_texture5,window,renderer);*/
    animation(bg_texture,my_texture,window,renderer);

    SDL_DestroyTexture(my_texture);
    SDL_DestroyTexture(bg_texture);
    IMG_Quit();                                // Si on charge une librairie SDL, il faut penser à la décharger   
    
}