#include "JdlV_graphique.h"




void initGrille(SDL_Window *win, SDL_Renderer *renderer){
    
    SDL_Rect rect;
    /* couleur de fond */
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
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