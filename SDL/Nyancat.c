#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

#define LARGEUR 1000
#define HAUTEUR 600

SDL_Window   *window =NULL;
SDL_Renderer *renderer= NULL;


int Init_Window()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        fprintf(stderr,"Erreur d'initialisation de la SDL : %s \n",SDL_GetError());
        return EXIT_FAILURE;
    }
    window = SDL_CreateWindow("SDL Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR, HAUTEUR,SDL_WINDOW_RESIZABLE); 
        if (window == 0) 
        {
            fprintf(stderr,"Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
        }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED ); /*  SDL_RENDERER_SOFTWARE */
        if (renderer == 0) 
        {
            fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
            SDL_DestroyWindow(window); 
        }
        
        /* couleur de fond */
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(5); 
    return(0);
}

void Init_Texture(SDL_Texture * Texture, char * img)
{
    SDL_Surface * Image = NULL;

    Image = IMG_Load(img);
    if (Image == 0) 
    {
        fprintf(stderr, "Erreur chargement image : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer); 
    }
    Texture = SDL_CreateTextureFromSurface(renderer,Image);
    if (Image == 0) 
    {
        fprintf(stderr, "Erreur chargement texture : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer); 
    }
    SDL_FreeSurface(Image);
}

void Aff_textu_full(SDL_Texture * Texture)
{

    SDL_Rect dest={0};
    SDL_Rect window_dim={0};
    SDL_Rect source={0};

    SDL_GetWindowSize(window, &window_dim.w,&window_dim.h);                    
    SDL_QueryTexture(Texture, NULL, NULL, &source.w, &source.h);       

    dest = window_dim;              
  
    SDL_RenderCopy(renderer, Texture,&source,&dest);

}

void animation(SDL_Texture * Texture)
{
    SDL_Rect dest={0};
    SDL_Rect window_dim={0};
    SDL_Rect source={0};
    SDL_Rect etat={0};


    SDL_GetWindowSize(window, &window_dim.w,&window_dim.h);                    
    SDL_QueryTexture(Texture, NULL, NULL, &source.w, &source.h);       

    dest = window_dim; 
    int nb_images = 5;                     
    float zoom = 4;                        
    int offset_x = source.w / nb_images,
        offset_y = source.h;           

        printf("%i\n",source.w);
       etat.x = 0 ;                          
       etat.y = 0;                
       etat.w = offset_x;                    
       etat.h = offset_y;                   

       dest.w = offset_x * zoom;
       dest.h = offset_y * zoom;    

       dest.y =(window_dim.h - dest.h) /2;
       dest.x =(window_dim.w - dest.w) /2;

       int speed = 9;

       for (int x = 0; x < window_dim.w - dest.w; x += speed) 
       {
        dest.x = x;
         etat.x += offset_x;                 // On passe à la vignette suivante dans l'image
         etat.x %= source.w;                 // La vignette qui suit celle de fin de ligne est
                                              // celle de début de ligne

         SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
         SDL_RenderCopy(renderer, Texture, // Préparation de l'affichage
                        &etat,
                        &dest);  
         SDL_RenderPresent(renderer);         // Affichage
         SDL_Delay(80);                       // Pause en ms
       }
       SDL_RenderClear(renderer);             // Effacer la fenêtre avant de rendre la main
}         

int main ()
{
    SDL_Texture * CAT = NULL;
    SDL_Texture * Fond = NULL;

    Init_Window();

    Init_Texture(Fond,"./Image/fond_Cat.jpg");

    Aff_textu_full(Fond);

    Init_Texture(CAT,"./Image/CAT.png");
    animation(CAT);

    SDL_RenderPresent(renderer);
    SDL_Delay(5);

    SDL_Delay(50);

    SDL_DestroyRenderer(renderer);

    SDL_DestroyTexture(CAT);
    SDL_DestroyTexture(Fond);


    SDL_DestroyWindow(window);

    IMG_Quit();

    SDL_Quit();

    return(0);
}