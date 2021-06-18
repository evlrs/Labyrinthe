#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

#define LARGEUR 1200
#define HAUTEUR 600

SDL_Window * window=NULL;
SDL_Renderer * renderer=NULL;


int Init_Window(char * titre)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stdin,"Erreur d'initialisation de la SDL : %s \n",SDL_GetError());
        return EXIT_FAILURE;
    }
    window = SDL_CreateWindow(titre, 0, 0, LARGEUR, HAUTEUR,SDL_WINDOW_RESIZABLE); 
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

TTF_Font* Init_Font(char * text) 
{
    if (TTF_Init() < 0)
    {
        fprintf(stdin, "Erreur d'initialisation de la TTF: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer); 
    } 

    TTF_Font* font = NULL; 
                                                 
    font = TTF_OpenFont(text, 30);                     
    if (font == NULL) 
    {
        fprintf(stdin, "Erreur chargement font : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer); 
    }

    
 
   TTF_SetFontStyle(font, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
    return font;
}

int main ()
{
        
    SDL_Texture * CAT = NULL;
    SDL_Texture * Fond = NULL;
    SDL_Texture * Planet = NULL;
    TTF_Font * Txt = NULL;
    

    Init_Window("Nyancat");
    Fond = Init_Texture("./Image/fond_Cat.jpg");
    CAT=Init_Texture("./Image/CAT.png");
    Planet = Init_Texture("./Image/planet2.png");

    Txt= Init_Font("./fonts/slkscr.ttf");

    Aff_textu_full(Fond);
    SDL_RenderPresent(renderer);
    SDL_Delay(10);

    char score_t[]="Le score est de : 00";
    int nscore_t=strlen(score_t);
    char lettre[]="i";
    int Score = 0;

    
    int running = 1;
    SDL_Event event;
    SDL_Rect window_dim={0};
    
    
    SDL_Rect dest_cat={0};
    SDL_Rect source_cat={0};
    SDL_Rect etat_cat={0};
    
    SDL_Rect dest_plan={0};
    SDL_Rect source_plan={0};

    SDL_Rect pos = {0};                                        
    SDL_Color color = {0,0,0,255};

    srand(time(NULL));
    int coli=0;

    SDL_GetWindowSize(window, &window_dim.w,&window_dim.h);                    
    SDL_QueryTexture(CAT, NULL, NULL, &source_cat.w, &source_cat.h);
    SDL_QueryTexture(Planet,NULL, NULL, &source_plan.w, &source_plan.h);      

    dest_cat = window_dim;

    int vit_plan=10;
    int vit_cat=10;
    int nb_images_cat = 5;                     
    float zoom_cat = 4; 
    float zoom_plan= 0.12;                       
    int offset_x = source_cat.w / nb_images_cat,
        offset_y = source_cat.h;           

       etat_cat.x = 0 ;                          
       etat_cat.y = 0 ;                
       etat_cat.w = offset_x;                    
       etat_cat.h = offset_y;                   

       dest_cat.w = offset_x * zoom_cat;
       dest_cat.h = offset_y * zoom_cat;    

       dest_cat.y = (window_dim.h - dest_cat.h) /2;
       dest_cat.x = 0;

       source_plan.x=0;
       source_plan.y=0;
      
       dest_plan.w = source_plan.w*zoom_plan;
       dest_plan.h = source_plan.w*zoom_plan;
       dest_plan.x= window_dim.w-dest_plan.w/2;
       dest_plan.y = 50+(rand()%((window_dim.h - dest_plan.h-50)));


    while (running) 
    {
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT : 
                    //printf("on quitte\n");
                       //SDL_DestroyRenderer(renderer); 
                       //SDL_DestroyWindow(window);
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
                        dest_cat.y -= 50;
                        dest_cat.y -= dest_cat.h/vit_cat-window_dim.h+50;
                        dest_cat.y %= window_dim.h-50;
                        dest_cat.y += 50;
                        break;
                    case SDLK_DOWN:
                        dest_cat.y -= 50;
                        dest_cat.y += dest_cat.h/vit_cat;
                        dest_cat.y %= window_dim.h-50;
                        dest_cat.y += 50;
                        break;
                    default:
                        break;
                    }
                break;
            }
        }


        if(coli==0)
        {
            SDL_RenderClear(renderer);
            Aff_textu_full(Fond);

            pos.x=0;
            for(int k=0;k<(nscore_t);++k)
            {
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
                
                lettre[0]=score_t[k];
                SDL_Surface* text_surface = NULL;                                    
                SDL_Texture* text_texture = NULL;                              
                
                text_surface = TTF_RenderText_Blended(Txt, lettre, color);               
                

                text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); 
                SDL_FreeSurface(text_surface); 


                SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);          
                
                SDL_RenderCopy(renderer, text_texture, NULL, &pos);
                SDL_DestroyTexture(text_texture);                                   
                                                    
                pos.x+=pos.w;
            }

            etat_cat.x += offset_x;
            etat_cat.x %= source_cat.w;   

            if (dest_plan.x <= -dest_plan.w)
            {
                dest_plan.x= window_dim.w-dest_plan.w;
                dest_plan.y = rand()%((window_dim.h - dest_plan.h));
                //vit_plan -= 0.1;
                Score++;
                score_t[nscore_t-2]=Score/10+'0';
                score_t[nscore_t-1]=Score%10+'0';
            }
            else
            {
                dest_plan.x -= dest_plan.w/vit_plan;
            }
            
            coli=SDL_HasIntersection(&dest_cat,&dest_plan);

            SDL_RenderCopy(renderer, CAT, &etat_cat,&dest_cat); 
            SDL_RenderCopy(renderer, Planet, &source_plan,&dest_plan);
        }
        else
        {
            SDL_RenderClear(renderer);
            Aff_textu_full(Fond);

            pos.x=(window_dim.w-(nscore_t*pos.w))/2;
            pos.y=(window_dim.h-pos.h)/2;
            for(int k=0;k<(nscore_t);++k)
            {
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
                
                lettre[0]=score_t[k];
                SDL_Surface* text_surface = NULL;                                     
                SDL_Texture* text_texture = NULL;                                    
                
                text_surface = TTF_RenderText_Blended(Txt, lettre, color);               

                text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); 

                SDL_FreeSurface(text_surface); 

                SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);          
                SDL_RenderCopy(renderer, text_texture, NULL, &pos);
                SDL_DestroyTexture(text_texture);                                    
                                                   
                pos.x+=pos.w;
            }
        }    
        SDL_RenderPresent(renderer);         
        SDL_Delay(80);
    }

    TTF_CloseFont(Txt);

    SDL_DestroyTexture(CAT);
    SDL_DestroyTexture(Fond);
    SDL_DestroyTexture(Planet);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return(0);
}