#include "character.h"


SDL_Window * window=NULL;
SDL_Renderer * renderer=NULL;


int main ()
{
        
    SDL_Texture * character1 = NULL;
    SDL_Texture * Fond = NULL;

    window =SDL_CreateWindow("Character",1,1,LARGEUR,HAUTEUR,0);
    
    Init_Window("Character");
    Fond = Init_Texture("./image/Labyrinthe3.png");
    character1=Init_Texture("./image/perso1.png");
    
    Aff_textu_full(Fond);
    SDL_RenderPresent(renderer);
    SDL_Delay(100);

    
    int running = 1;
    SDL_Event event;

    SDL_Rect dest={0};
    SDL_Rect window_dim={0};
    SDL_Rect source={0};
    SDL_Rect destination;
    //SDL_Rect state = {0}
    SDL_Rect etat[36];

    
    SDL_GetWindowSize(window, &window_dim.w,&window_dim.h);                    
    SDL_QueryTexture(character1, NULL, NULL, &source.w, &source.h);       

    dest = window_dim; 
    int nb_images = 9;
    int nb_lignes= 4;  
    int nb_im_tot=nb_lignes*nb_images;            
    float zoom = 0.5;                        
    int offset_x = source.w / nb_images,
        offset_y = source.h / nb_lignes;           

       dest.w = offset_x * zoom;
       dest.h = offset_y * zoom;    

       dest.y =(window_dim.h - dest.h) /2;  //window_dim taille du sprite mur

       dest.x = (window_dim.w - dest.w) /2; 
    
    for (int i =0; i < nb_im_tot; ++i) {
        etat[i].w = offset_x;                    
        etat[i].h = offset_y;
        etat[i].x=offset_x*i%9;
        etat[i].y=offset_y*i/9;
    
    } 

  


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
                            running=0;	
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
                        deplacement(0,character1,etat,Fond,&dest,&destination);
                        break;
                    case SDLK_DOWN:
                        deplacement(2,character1,etat,Fond,&dest,&destination);
                        break;
                    case SDLK_RIGHT:
                        deplacement(3,character1,etat,Fond,&dest,&destination);
                        break;
                    case SDLK_LEFT:
                        deplacement(1,character1,etat,Fond,&dest,&destination);
                        break;    
                    default:
                        break;
                    }
                break;

                
            }
        }
        
         
       


    }
    //animation(character1,Fond);

    //SDL_RenderPresent(renderer);
    //SDL_Delay(5);

    //SDL_Delay(50);

    SDL_DestroyRenderer(renderer);

    SDL_DestroyTexture(character1);
    SDL_DestroyTexture(Fond);


    SDL_DestroyWindow(window);

    IMG_Quit();

    SDL_Quit();

    return(0);
}


void deplacement(int i,SDL_Texture * character1, SDL_Rect etat[],SDL_Texture* Fond,SDL_Rect * dest,SDL_Rect * destination){
    int L=120; //Longueur d'une case du labyrinthe
    destination->x=1;
    destination->y=1;
    for (int k=0; k<9; k++){
        if (i==0) dest->y-=L/9;  //nord
        if (i==1) dest->x-=L/9;  // ouest
        if (i==2) dest->y+=L/9; //sud
        if (i==3) dest->x+=L/9;   //est
        
        
        SDL_RenderCopy(renderer, Fond,&source,&dest);
        SDL_RenderCopy(renderer, character1, // Préparation de l'affichage
                        &etat[i*(9+k)],
                        &dest);
        
        SDL_RenderPresent(renderer);         // Affichage
                 
        
        SDL_RenderPresent(renderer);         
        SDL_Delay(100);
        SDL_RenderClear(renderer);
    }

}

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
