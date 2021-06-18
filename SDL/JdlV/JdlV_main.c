#include "JdlV_text.h"
#include "JdlV_graphique.h"

void jouer(SDL_Window *win, SDL_Renderer *renderer, 
    int grille1[LARGEUR][LONGUEUR], int grille2[LARGEUR][LONGUEUR], int play);
void initForme(int grille1[LARGEUR][LONGUEUR]);

int main(){

    int grille1[LARGEUR][LONGUEUR];
    int grille2[LARGEUR][LONGUEUR];
    //int i,j;
    int coord[2];

    initTableau(grille1);
    initTableau(grille2);
    initForme(grille1);

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

    int cpt=0;
    SDL_bool program_on = SDL_TRUE,                          // Booléen pour dire que le programme doit continuer
            paused = SDL_FALSE;                              // Booléen pour dire que le programme est en pause
    while (program_on) {                                     // La boucle des évènements
        SDL_Event event;                                     // Evènement à traiter
        if(cpt%20==0){
            //initForme(grille1); 
        }
        cpt++;
        while (program_on && SDL_PollEvent(&event)) {       // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas                                                     
                                                            // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type) {                           // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:                                  // Un évènement simple, on a cliqué sur la x de la // fenêtre
                program_on = SDL_FALSE;                     // Il est temps d'arrêter le programme
                break;

            case SDL_KEYDOWN:                               // Le type de event est : une touche appuyée
                                                            // comme la valeur du type est SDL_Keydown, dans la pratie 'union' de
                                                            // l'event, plusieurs champs deviennent pertinents   
                switch (event.key.keysym.sym) {             // la touche appuyée est ...
                case SDLK_p:                                // 'p'
                case SDLK_SPACE:                            // 'SPC'
                    paused = !paused;                       // basculement pause/unpause
                    break;
                case SDLK_ESCAPE:                           // 'ESCAPE'  
                case SDLK_q:                                // 'q'
                    program_on = SDL_FALSE;                 // 'escape' ou 'q', d'autres façons de quitter le programme                                     
                    break;
                case SDLK_RETURN:
                    initTableau(grille1);
                    initForme(grille1);                     // Redemarrer le planneur 
                    break;
                default:                                    // Une touche appuyée qu'on ne traite pas
                    break;
                }
                break;
            
            case SDL_MOUSEBUTTONDOWN:                       // Click souris   
                coord[0]=event.button.x/10;                 // Recupere la coordonnée en X du pixel où se trouve la souris
                coord[1]=event.button.y/10;                 // Et en Y
                grille2[coord[1]][coord[0]]+=1%2;           //1->0 et 0->1
                jouer(win,renderer,grille1,grille2,0);
                break;
            default:                                        // Les évènements qu'on n'a pas envisagé
                break;
            }

        }

        
        if (!paused) {                                      // Si on n'est pas en pause
            jouer(win,renderer,grille1,grille2,1);          // la vie continue... 
        }
        SDL_Delay(100);                                      // Petite pause
    }

    return 0;
}

void jouer(SDL_Window *win, SDL_Renderer *renderer, int grille1[LARGEUR][LONGUEUR], int grille2[LARGEUR][LONGUEUR], int play){
    int i,j;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);
    for(i=0;i<LARGEUR;++i){
        for(j=0;j<LONGUEUR;++j){
            
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

void initForme(int grille1[LARGEUR][LONGUEUR]){
    /* initialisation planeur */
    //initTableau(grille1);
    
    grille1[1][0]=1;
    grille1[2][1]=1;
    grille1[2][2]=1;
    grille1[1][2]=1;
    grille1[0][2]=1;
    
}



