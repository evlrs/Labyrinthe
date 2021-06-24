#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>



int main(){

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      
        exit(EXIT_FAILURE);
    }

    SDL_Window *win = NULL;
    win = SDL_CreateWindow("Fenêtre", 0, 0, L*10, H*10, 0);

    if (win == NULL) {
        SDL_Log("Error : SDL window creation - %s\n", SDL_GetError());   
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    
    /* initialisation renderer */
    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == 0) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    }

    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0}; 
    SDL_Rect state[16];
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);

    int offset_x = 10, offset_y = 10; 

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    rect.x = (x)*10;
    rect.y = (y)*10;
    rect.w = rect.h = 10;
    SDL_RenderFillRect(renderer, &rect );

    for(int i=0;i<16;i++){
        state[].w = 10; 
        state[].h = 10;
    }
    int n=0;
    for(int i=0;i<H;i++){
        for(int j=0;j<L;j++){
            n=lab[i][j]
            destination.x = offset_x*j;
            destination.y = offset_y*i;
            state[n].x = n%4
            state[n].y = n/4

        }
    }
    return 0;
}


void jouer(SDL_Window *win, SDL_Renderer *renderer, int grille1[L][H], int grille2[L][H]){
    int i,j;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);
    for(i=0;i<L;++i){
        for(j=0;j<H;++j){
            
            if(play==1){
                if(grille1[i][j]==1)    pixelNoir(win, renderer, j, i);
                grille2[i][j]=etatFuturCellule(grille1,i,j);
            }else{
                if(grille2[i][j]==1)    pixelNoir(win, renderer, j, i);
            }
        }
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(5);
    copieTableau(grille1,grille2);
    
}
