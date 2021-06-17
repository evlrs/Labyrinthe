#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>

void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer);

void main(){

     SDL_Window *window = NULL;
     window = SDL_CreateWindow("Fenêtre", 0, 0, 700, 700, 0);
 
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
    font = TTF_OpenFont("./fonts/Pacifico.ttf", 65);                     // La police à charger, la taille désirée
    if (font == NULL) end_sdl(0, "Can't load font", window, renderer);

    TTF_SetFontStyle(font, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);           // en italique, gras
    int scoreTab[2]={0,0};
    char a[3];
    a[0]=1+'0';
    a[1]=2+'0';
    a[2]='\0';
    //char scoreChar=("%d - %d", scoreTab[0], scoreTab[1]);
    //printf("%c\n",scoreChar[0]);
    SDL_Color color = {200, 0, 40, 255};                                  // la couleur du texte
    SDL_Surface* text_surface = NULL;                                     // la surface  (uniquement transitoire)

    text_surface = TTF_RenderText_Blended(font, a, color);               // création du texte dans la surface 
    if (text_surface == NULL) end_sdl(0, "Can't create text surface", window, renderer);

    SDL_Texture* text_texture = NULL;                                    // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL) end_sdl(0, "Can't create texture from surface", window, renderer);
    SDL_FreeSurface(text_surface);                                       // la texture ne sert plus à rien

    SDL_Rect pos = {0, 0, 0, 0};                                         // rectangle où le texte va être prositionné
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);          // récupération de la taille (w, h) du texte 
    SDL_RenderCopy(renderer, text_texture, NULL, &pos);                  // Ecriture du texte dans le renderer   
    SDL_DestroyTexture(text_texture);                                    // On n'a plus besoin de la texture avec le texte

    SDL_RenderPresent(renderer);                                         // Affichage 
    SDL_Delay(5000);
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