#include "JdlV_text.h"

int main(){

    int grille1[LARGEUR][LONGUEUR];
    int grille2[LARGEUR][LONGUEUR];
    int i,j,k;

    initTableau(grille1);
    initTableau(grille2);

    /* initialisation planeur */
    grille1[1][0]=1;
    grille1[2][1]=1;
    grille1[2][2]=1;
    grille1[1][2]=1;
    grille1[0][2]=1;
    afficheTableau(grille1);

    /* initialisation fenetre */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }
    
    SDL_Window *win = NULL;
    win = SDL_CreateWindow("Fenêtre", 0, 0, LARGEUR*10, LONGUEUR*10, 0);
 
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

    for(k=0;k<10;++k){
        for(i=0;i<LARGEUR;++i){
            for(j=0;j<LONGUEUR;++j){
                grille2[i][j]=etatFuturCellule(grille1,i,j);
            }
        }
        afficheTableau(grille2);
        copieTableau(grille1,grille2);
    }
    return 0;
}