#include "JdlV_text.h"
#include "JdlV_graphique.h"

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

    /* initialisation fenetre */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }

    SDL_Window *win = NULL;
    win = SDL_CreateWindow("Fenêtre", 0, 0, LONGUEUR*10, LARGEUR*10, 0);

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


    /*
    for(k=0;k<100;++k){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);
        for(i=0;i<LARGEUR;++i){
            for(j=0;j<LONGUEUR;++j){
                if(grille1[i][j]==1)    pixelNoir(win, renderer, j, i);
                grille2[i][j]=etatFuturCellule(grille1,i,j);
            }
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        copieTableau(grille1,grille2);
    }
    SDL_DestroyRenderer(renderer);
    SDL_Delay(1000);
    SDL_DestroyWindow(win);
    */
    SDL_bool program_on = SDL_TRUE,                          // Booléen pour dire que le programme doit continuer
            paused = SDL_FALSE;                             // Booléen pour dire que le programme est en pause
    while (program_on) {                              // La boucle des évènements
        SDL_Event event;                                // Evènement à traiter

        while (program_on && SDL_PollEvent(&event)) {   // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
                                                        // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type) {                         // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:                                // Un évènement simple, on a cliqué sur la x de la // fenêtre
            program_on = SDL_FALSE;                     // Il est temps d'arrêter le programme
            break;
            case SDL_KEYDOWN:                             // Le type de event est : une touche appuyée
                                                        // comme la valeur du type est SDL_Keydown, dans la pratie 'union' de
                                                        // l'event, plusieurs champs deviennent pertinents   
                switch (event.key.keysym.sym) {             // la touche appuyée est ...
                    case SDLK_p:                                // 'p'
                    case SDLK_SPACE:                            // 'SPC'
                        paused = !paused;                         // basculement pause/unpause
                        break;
                    case SDLK_ESCAPE:                           // 'ESCAPE'  
                    case SDLK_q:                                // 'q'
                        program_on = 0;                           // 'escape' ou 'q', d'autres façons de quitter le programme                                     
                        break;
                    default:                                    // Une touche appuyée qu'on ne traite pas
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:                     // Click souris   
                if (SDL_GetMouseState(NULL, NULL) & 
                        SDL_BUTTON(SDL_BUTTON_LEFT) ) {         // Si c'est un click gauche
                    //change_state(state, 1, window);           // Fonction à éxécuter lors d'un click gauche
                } else if (SDL_GetMouseState(NULL, NULL) & 
                            SDL_BUTTON(SDL_BUTTON_RIGHT) ) { // Si c'est un click droit
                    //change_state(state, 2, window);           // Fonction à éxécuter lors d'un click droit
                }
                break;
            default:                                      // Les évènements qu'on n'a pas envisagé
                break;
            }
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderClear(renderer);
            for(i=0;i<LARGEUR;++i){
                for(j=0;j<LONGUEUR;++j){
                    if(grille1[i][j]==1)    pixelNoir(win, renderer, j, i);
                    grille2[i][j]=etatFuturCellule(grille1,i,j);
                }
            }
        
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
            copieTableau(grille1,grille2);
        }
        //draw(state, &color, renderer, window);          // On redessine
        if (!paused) {                                  // Si on n'est pas en pause
            //next_state(state, survive, born);             // la vie continue... 
        }
        SDL_Delay(50);                                  // Petite pause
    }

    return 0;
}