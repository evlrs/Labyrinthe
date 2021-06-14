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
    
    int i,j;
    for(j=0;j<3;++j){
        for(i=0;i<80;++i){

            SDL_Rect rect;
            /* couleur de fond */
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderClear(renderer);
            /* dessiner en blanc */
            SDL_SetRenderDrawColor(renderer, 0, 200, 100, 0);
            rect.x = 100+5*i;
            rect.y = 150;
            rect.w = 20;
            rect.h = 5;
            SDL_RenderFillRect(renderer, &rect );

            /* afficher à l'ecran */
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }
        for(i=0;i<30;++i){

            SDL_Rect rect;
            /* couleur de fond */
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderClear(renderer);
            /* dessiner en blanc */
            SDL_SetRenderDrawColor(renderer, 0, 200, 100, 0);
            rect.x = 500;
            rect.y = 150-5*i;
            rect.w = 5;
            rect.h = 20;
            SDL_RenderFillRect(renderer, &rect );

            /* afficher à l'ecran */
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }    
        for(i=0;i<80;++i){

            SDL_Rect rect;
            /* couleur de fond */
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderClear(renderer);
            /* dessiner en blanc */
            SDL_SetRenderDrawColor(renderer, 0, 200, 100, 0);
            rect.x = 500-5*i;
            rect.y = 0;
            rect.w = 20;
            rect.h = 5;
            SDL_RenderFillRect(renderer, &rect );

            /* afficher à l'ecran */
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }
        for(i=0;i<30;++i){

            SDL_Rect rect;
            /* couleur de fond */
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderClear(renderer);
            /* dessiner en blanc */
            SDL_SetRenderDrawColor(renderer, 0, 200, 100, 0);
            rect.x = 100;
            rect.y = 0+5*i;
            rect.w = 5;
            rect.h = 20;
            SDL_RenderFillRect(renderer, &rect );

            /* afficher à l'ecran */
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        } 
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
}
