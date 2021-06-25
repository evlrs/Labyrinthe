#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

#define LARGEUR 1000
#define HAUTEUR 600

SDL_Window * window=NULL;
SDL_Renderer * renderer=NULL;


int Init_Window(char * titre)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        fprintf(stdin,"Erreur d'initialisation de la SDL : %s \n",SDL_GetError());
        return EXIT_FAILURE;
    }
    window = SDL_CreateWindow(titre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR, HAUTEUR,SDL_WINDOW_RESIZABLE); 
        if (window == 0) 
        {
            fprintf(stdin,"Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
        }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED ); /*  SDL_RENDERER_SOFTWARE */
        if (renderer == 0) 
        {
            fprintf(stdin, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
            SDL_DestroyWindow(window); 
        }
       
        /* couleur de fond */
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(5); 
        return(0);
}

SDL_Texture * Init_Texture( char * img)
{
    SDL_Surface * Image = NULL;
    SDL_Texture * Texture = NULL;

    Image = IMG_Load(img);
    if (Image == NULL) 
    {
        fprintf(stdin, "Erreur chargement image : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer); 
    }
    Texture = SDL_CreateTextureFromSurface(renderer,Image);
    if (Texture == 0) 
    {
        fprintf(stdin, "Erreur chargement texture : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer); 
    }
    SDL_FreeSurface(Image);

    return Texture;
}

void Aff_textu_full(SDL_Texture * Texture)
{
    SDL_Rect dest={0};
    SDL_Rect window_dim={0};
    SDL_Rect source={0};

    SDL_GetWindowSize(window, &window_dim.w,&window_dim.h);                    
    SDL_QueryTexture(Texture, NULL, NULL, &source.w, &source.h);       

    dest = window_dim; 
    if (Texture == NULL) 
    {
        fprintf(stdin, "Erreur chargement texture : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer); 
    }             
    SDL_RenderCopy(renderer, Texture,&source,&dest);

}

int main ()
{
        
    SDL_Texture * CAT = NULL;
    SDL_Texture * Fond = NULL;
    
    Init_Window("Character");
    Fond = Init_Texture("./image/Labyrinthe3.jpg");
    CAT=Init_Texture("./image/perso1.png");
    
    Aff_textu_full(Fond);
    SDL_RenderPresent(renderer);
    SDL_Delay(100);

    
    int running = 1;
    SDL_Event event;

    SDL_Rect dest={0};
    SDL_Rect window_dim={0};
    SDL_Rect source={0};
    SDL_Rect etat={0};


    SDL_GetWindowSize(window, &window_dim.w,&window_dim.h);                    
    SDL_QueryTexture(CAT, NULL, NULL, &source.w, &source.h);       

    dest = window_dim; 
    int nb_images = 9; 
    int nb_lignes = 4;                  
    float zoom = 2;                        
    int offset_x = source.w / nb_images,
        offset_y = source.h /nb_lignes;           

       etat.x = 0 ;                          
       etat.y = 0 ;                
       etat.w = offset_x;                    
       etat.h = offset_y;                   

       dest.w = offset_x * zoom;
       dest.h = offset_y * zoom;    

       dest.y =(window_dim.h - dest.h) /2;

       dest.x = 0;



    while (running) 
    {
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT : 
                    //printf("on quitte\n");
                       SDL_DestroyRenderer(renderer); 
                       SDL_DestroyWindow(window);
                    running = 0;
                    break;

                case SDL_WINDOWEVENT:
                    //printf("window event\n");
                    switch (event.window.event)  
                    {
                        case SDL_WINDOWEVENT_CLOSE:  
                            printf("appui sur la croix\n");	
                            break;
                        /*case SDL_WINDOWEVENT_SIZE_CHANGED:
                            larg = event.window.data1;
                            haut = event.window.data2;
                            affi_Gra(Grille,larg,haut);
                            break;*/
                        default:
                            break;
                    }   
                    break;


                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_UP:
                        dest.y -= dest.h/2;
                        break;
                    case SDLK_DOWN:
                        dest.y += dest.h/2;
                        break;
                    case SDLK_RIGHT: 
                        dest.x += dest.h/2;
                        break; 
                    case SDLK_LEFT: 
                        dest.x -= dest.h/2;
                        break;   
                    default:
                        break;
                    }
                break;
            }
        }


         etat.x += offset_x;                 
         etat.x %= source.w;    //Division par 0 possible ->core dumped             
                                             

         SDL_RenderClear(renderer);           
         Aff_textu_full(Fond);
         SDL_RenderCopy(renderer, CAT, &etat,&dest); 
         SDL_RenderPresent(renderer);         
        SDL_Delay(80);


    }

    //animation(CAT,Fond);

    //SDL_RenderPresent(renderer);

    //SDL_Delay(50);

    SDL_DestroyRenderer(renderer);

    SDL_DestroyTexture(CAT);
    SDL_DestroyTexture(Fond);


    SDL_DestroyWindow(window);

    IMG_Quit();

    SDL_Quit();

    return(0);
}