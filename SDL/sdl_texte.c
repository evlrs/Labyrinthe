#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>

void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer);

void main(){

     SDL_Window *window = NULL;
     window = SDL_CreateWindow("Fenêtre", 0, 0, 1300, 700, 0);
 
    if (window == NULL) {
        SDL_Log("Error : SDL window creation - %s\n", SDL_GetError());   
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == 0) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    }
        
    if (TTF_Init() < 0) end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);

    TTF_Font* font = NULL;                                               // la variable 'police de caractère'
    font = TTF_OpenFont("./fonts/slkscr.ttf", 30);                     // La police à charger, la taille désirée
    if (font == NULL) end_sdl(0, "Can't load font", window, renderer);

    TTF_SetFontStyle(font, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);           // en italique, gras
    
    char score[]="Le score est de : 00";
    char scoreB[]="Le score est de : 00";
    int nScore=strlen(score);


    int nbobjet=99;
    char objets[]="         obj restant : 99";
    int nObjets=strlen(objets);
    char lettre[]="i";
    

    strcat(score,objets);

    SDL_Rect pos = {0, 0, 0, 0};                                         // rectangle où le texte va être prositionné
    SDL_Color color = {0,0,0,255};
    for(int i=0;i<15;++i){
        score[nScore-2]=i/10+'0';
        score[nScore-1]=i%10+'0';
        score[nObjets+nScore-2]=(9-i/10)+'0';
        score[nObjets+nScore-1]=(9-i%10)+'0';
        pos.x=50;
        for(int k=0;k<(nObjets+nScore);++k){
            
            switch(k%7){
                case(0):
                    color.r=240;
                    color.g=50;
                    color.b=255; 
                    break; 
                case(1):
                    color.r=50;
                    color.g=90;
                    color.b=255;
                    break;
                case(2):
                    color.r=50;
                    color.g=180;
                    color.b=255;
                    break;
                case(3):
                    color.r=50;
                    color.g=255;
                    color.b=50;
                    break;
                case(4):
                    color.r=255;
                    color.g=255;
                    color.b=50;
                    break;
                case(5):
                    color.r=255;
                    color.g=200;
                    color.b=50;
                    break;
                case(6):
                    color.r=255;
                    color.g=50;
                    color.b=50;
                    break;
            }
            
            lettre[0]=score[k];
            SDL_Surface* text_surface = NULL;                                     // la surface  (uniquement transitoire)
            SDL_Texture* text_texture = NULL;                                    // la texture qui contient le texte
            
            text_surface = TTF_RenderText_Blended(font, lettre, color);               // création du texte dans la surface 
            //if (text_surface == NULL) end_sdl(0, "Can't create text surface", window, renderer);

            text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
            //if (text_texture == NULL) end_sdl(0, "Can't create texture from surface", window, renderer);
            SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);          // récupération de la taille (w, h) du texte 
            SDL_RenderCopy(renderer, text_texture, NULL, &pos);                  // Ecriture du texte dans le renderer   

            
            SDL_DestroyTexture(text_texture);                                    // On n'a plus besoin de la texture avec le texte
            SDL_FreeSurface(text_surface);                                       // la texture ne sert plus à rien
            pos.x+=pos.w;
        }
        SDL_RenderPresent(renderer);                                         // Affichage 
        SDL_Delay(500);
        SDL_RenderClear(renderer);
    }
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    TTF_Quit();
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