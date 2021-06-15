#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define LARGEUR 400
#define LONGEUR 400
#define TAILLE 20


SDL_Window   *window;
SDL_Renderer *renderer;

int Init_Window()
{

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        fprintf(stderr,"Erreur d'initialisation de la SDL : %s \n",SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("SDL Jeu de la vie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
            LARGEUR, LONGEUR, 
            SDL_WINDOW_RESIZABLE); 
    
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
    return(0);
}

void affichage(int color, int X, int Y, int taille)
{
    SDL_Rect rect;
    int R,V, B;
    switch (color)
           {
           case 0 :
               R=255;
               V=255;
               B=255;
               break;
           case 1 :
               R=10;
               V=10;
               B=10;
               break;
           default:
               break;
           }
    SDL_SetRenderDrawColor(renderer, R, V, B, 0);
    rect.x = X;
    rect.y = Y;
    rect.w = rect.h = taille;
    SDL_RenderFillRect(renderer, &rect );
     
}

void Init_Tab(int tab[TAILLE][TAILLE])
{
	int j,i;
    srand(time(NULL));

    for(j=0;j<TAILLE; ++j) 
	{
  		for(i=0; i<TAILLE; ++i)
      		tab[j][i] = 0 ; 
    }
    tab[1][0]=1;
    tab[1][2]=1;
    tab[2][1]=1;
    tab[2][2]=1;
    tab[0][2]=1;
}

void affi_Tex(int tab[TAILLE][TAILLE])
{
	int i,j;

    printf(" ------------------------------------");
    printf("\n"); 
	for(i=0;i<TAILLE; ++i) 
	{
        printf("|");
  		for(j=0; j<TAILLE; ++j) 
        {    
           switch (tab[i][j])
           {
           case 0 :
               printf("\033[1;47m %d \033[0;0m", tab[i][j]);
               break;
           case 1 :
               printf("\033[1;40m %d \033[0;0m", tab[i][j]);
               break;
           default:
               break;
           }   
        } 
        printf("|");
  		printf("\n");
	}
    printf(" ------------------------------------");
    printf("\n"); 
}

void affi_Gra(int tab[TAILLE][TAILLE])
{
    int i,j;

    for(i=0;i<TAILLE; ++i) 
	{
  		for(j=0; j<TAILLE; ++j) 
        {
            affichage(tab[i][j],j*20,i*20,20);
        }
    }
    /* afficher à l'ecran */
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
}

int Nb_voisin(int tab[TAILLE][TAILLE], int i, int j)
{
    int nb=0;
    nb=tab[(i-1 + TAILLE)%TAILLE][(j-1 + TAILLE)%TAILLE] 
       + tab[(i-1 + TAILLE)%TAILLE][(j + TAILLE)%TAILLE] 
       + tab[(i-1 + TAILLE)%TAILLE][(j+1 + TAILLE)%TAILLE] 
                + tab[(i + TAILLE)%TAILLE][(j-1 + TAILLE)%TAILLE] 
                + tab[(i + TAILLE)%TAILLE][(j+1 + TAILLE)%TAILLE] 
                + tab[(i+1 + TAILLE)%TAILLE][(j-1 + TAILLE)%TAILLE] 
                + tab[(i+1 + TAILLE)%TAILLE][(j + TAILLE)%TAILLE] 
                + tab[(i+1 + TAILLE)%TAILLE][(j+1 + TAILLE)%TAILLE];
    return nb;
}

void Grillsuiv(int tab[TAILLE][TAILLE])
{
    int voisin=0;
    int vivant[9]={0,0,1,1,0,0,0,0,0};
    int mort[9]={0,0,0,1,0,0,0,0,0};

    int Grille2 [TAILLE] [TAILLE];

        for(int i=0; i<TAILLE; ++i) 
	    {
  		    for(int j=0;j<TAILLE; ++j)
            {
                voisin=Nb_voisin(tab,i,j);
                if(tab[i][j]==1)
                {
                    Grille2[i][j]=vivant[voisin];
                }
                else
                {
                    Grille2[i][j]=mort[voisin];
                }
            }
        }

    for(int i=0; i<TAILLE; ++i) 
	    {
  		    for(int j=0;j<TAILLE; ++j)
            {  
                    tab[i][j]=Grille2[i][j];
            }
        }

} 

int main()
{
    Init_Window();
    int Grille [TAILLE] [TAILLE];
    Init_Tab(Grille);


    affi_Tex(Grille);
    affi_Gra(Grille);

    int running = 1;
    SDL_Event event;

    while (running) 
    {
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_WINDOWEVENT:
                    //printf("window event\n");
                    switch (event.window.event)  
                    {
                        case SDL_WINDOWEVENT_CLOSE:  
                            printf("appui sur la croix\n");	
                            break;
                        default:
                            break;
                    }   
                    break;
                case SDL_QUIT : 
                    //printf("on quitte\n");
                       SDL_DestroyRenderer(renderer); 
                       SDL_DestroyWindow(window);
                    running = 0;
            }
        }	
	    SDL_Delay(1); //  delai minimal


        Grillsuiv(Grille);
        affi_Tex(Grille);
        affi_Gra(Grille);


    }

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return(0);
}

