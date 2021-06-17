#include "JdlV_graphique.h"



void pixelNoir(SDL_Window *win, SDL_Renderer *renderer, int x, int y){
    SDL_Rect rect;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    rect.x = (x)*10;
    rect.y = (y)*10;
    rect.w = rect.h = 10;
    SDL_RenderFillRect(renderer, &rect );
    
}