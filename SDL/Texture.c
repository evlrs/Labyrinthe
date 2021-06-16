#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

#define LARGEUR 1000
#define LONGEUR 500




SDL_Window   *window =NULL;
SDL_Renderer *renderer= NULL;

SDL_Texture * Textur = NULL;

int Init_Window()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        fprintf(stderr,"Erreur d'initialisation de la SDL : %s \n",SDL_GetError());
        return EXIT_FAILURE;
    }
    window = SDL_CreateWindow("SDL Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR, LONGEUR,SDL_WINDOW_RESIZABLE); 
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

void Init_Texture()
{
    SDL_Surface * Image = NULL;

    Image = IMG_Load("./Image/cat.png");
    if (Image == 0) 
    {
        fprintf(stderr, "Erreur chargement image : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer); 
    }

    Textur = SDL_CreateTextureFromSurface(renderer,Image);
    if (Image == 0) 
    {
        fprintf(stderr, "Erreur chargement texture : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer); 

    }
    
    SDL_FreeSurface(Image);
}

void Aff_textu_full()
{

    SDL_Rect dest={0};
    SDL_Rect window_dim={0};
    SDL_Rect source={0};

    SDL_GetWindowSize(window, &window_dim.w,&window_dim.h);                    
    SDL_QueryTexture(Textur, NULL, NULL, &source.w, &source.h);       

    dest = window_dim;              
  
    SDL_RenderCopy(renderer, Textur,&source,&dest);

}

void Aff_textu_zoom()
{

    SDL_Rect dest={0};
    SDL_Rect window_dim={0};
    SDL_Rect source={0};

    SDL_GetWindowSize(window, &window_dim.w,&window_dim.h);                    
    SDL_QueryTexture(Textur, NULL, NULL, &source.w, &source.h);       

    dest = window_dim;    


    float zoom = 0.5;                            
     dest.w = source.w * zoom;         
     dest.h = source.h * zoom;         
     dest.x = (window_dim.w - dest.w) /2;     
     dest.y = (window_dim.h - dest.h) / 2;
          
  
    SDL_RenderCopy(renderer, Textur,&source,&dest);

}

void Aff_textu_anim()
{

    SDL_Rect dest={0};
    SDL_Rect window_dim={0};
    SDL_Rect source={0};

    SDL_GetWindowSize(window, &window_dim.w,&window_dim.h);                    
    SDL_QueryTexture(Textur, NULL, NULL, &source.w, &source.h);       

    dest = window_dim;    


    float zoom= 0.25;
    int nb_it = 200;                        
    dest.w = source.w * zoom;  
    dest.h = source.h * zoom;         
    dest.x =(window_dim.w - dest.w) / 2;  
    float h = window_dim.h - dest.h;  

    for (int i = 0; i < nb_it; ++i) {
        dest.y =
            h * (1 - exp(-5.0 * i / nb_it) / 2 *
                        (1 + cos(10.0 * i / nb_it * 2 *
                                M_PI)));            

        SDL_RenderClear(renderer);                  

        SDL_SetTextureAlphaMod(Textur,(1.0-1.0*i/nb_it)*255);      
        SDL_RenderCopy(renderer, Textur, &source, &dest);   
        SDL_RenderPresent(renderer);                 
        SDL_Delay(30);                                
    }                                                 
    SDL_RenderClear(renderer);

}

void Aff_textu_anim2()
{

    SDL_Rect dest={0};
    SDL_Rect window_dim={0};
    SDL_Rect source={0};
    SDL_Rect etat={0};


    SDL_GetWindowSize(window, &window_dim.w,&window_dim.h);                    
    SDL_QueryTexture(Textur, NULL, NULL, &source.w, &source.h);       

    dest = window_dim; 
    int nb_images = 5;                     
    float zoom = 4;                        
    int offset_x = source.w / nb_images,
        offset_y = source.h;           


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
         etat.x += offset_x;                 // On passe à la vignette suivante dans l'image
         etat.x %= source.w;                 // La vignette qui suit celle de fin de ligne est
                                              // celle de début de ligne

         SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
         SDL_RenderCopy(renderer, Textur, // Préparation de l'affichage
                        &etat,
                        &dest);  
         SDL_RenderPresent(renderer);         // Affichage
         SDL_Delay(80);                       // Pause en ms
       }
       SDL_RenderClear(renderer);             // Effacer la fenêtre avant de rendre la main
     }

int main ()
{
    Init_Window();

    Init_Texture();
    
    Aff_textu_anim2();

    SDL_RenderPresent(renderer);
    SDL_Delay(5);

    SDL_Delay(50);

    SDL_DestroyRenderer(renderer);

    SDL_DestroyTexture(Textur);

    SDL_DestroyWindow(window);

    IMG_Quit();

    SDL_Quit();

    return(0);
}