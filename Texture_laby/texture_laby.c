#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define LARGEUR 400
#define HAUTEUR 400
#define LIGNE 20
#define COLONE 35

SDL_Window *window;
SDL_Renderer *renderer;

int Init_Window(char *titre, int larg, int longr)
{

   if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
   {
      fprintf(stderr, "Erreur d'initialisation de la SDL : %s \n", SDL_GetError());
      return EXIT_FAILURE;
   }

   window = SDL_CreateWindow(titre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                             larg, longr,
                             SDL_WINDOW_RESIZABLE);

   if (window == 0)
   {
      fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
   }

   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
   if (renderer == 0)
   {
      fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
      SDL_DestroyWindow(window);
   }

   /* couleur de fond */
   SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
   SDL_RenderClear(renderer);
   return (0);
}

void affichage(int color, int X, int Y, int W, int H)
{
   SDL_Rect rect;
   int R, V, B;
   switch (color)
   {
   case 0:
      R = 255;
      V = 255;
      B = 255;
      break;
   case 1:
      R = 10;
      V = 10;
      B = 10;
      break;
   default:
      break;
   }
   SDL_SetRenderDrawColor(renderer, R, V, B, 0);
   rect.x = X;
   rect.y = Y;
   rect.w = W;
   rect.h = H;
   SDL_RenderFillRect(renderer, &rect);
}

void Init_Tab(int tab[LIGNE][COLONE])
{
   int j, i;
   srand(time(NULL));

   for (i = 0; i < LIGNE; ++i)
   {
      for (j = 0; j < COLONE; ++j)
         tab[i][j] = rand() % 16;
   }
}

void affi_Tex(int tab[LIGNE][COLONE])
{
   int i, j;

   printf(" ------------------------------------");
   printf("\n");
   for (i = 0; i < LIGNE; ++i)
   {
      printf("|");
      for (j = 0; j < COLONE; ++j)
         printf(" %d ", tab[i][j]);

      printf("|");
      printf("\n");
   }
   printf(" ------------------------------------");
   printf("\n");
}

void affi_Gra(int tab[LIGNE][COLONE], int W, int H)
{
   int i, j;
   SDL_RenderClear(renderer);

   for (i = 0; i < LIGNE; ++i)
   {
      for (j = 0; j < COLONE; ++j)
      {
         affichage(tab[i][j], j * (W / COLONE), i * (H / LIGNE), W / COLONE, H / LIGNE);
      }
   }
   /* afficher à l'ecran */

   SDL_RenderPresent(renderer);
   SDL_Delay(1);
}

int Coordonne(int val, int x, int w, int h)
{
   float coef = 0;
   int convert = 0;

   if (x == 1)
   {
      coef = w / COLONE;
   }
   else
   {
      coef = h / LIGNE;
   }
   convert = val / coef;
   return convert;
}

int main()
{
   Init_Window("V0 : Labyrinthe", LARGEUR, HAUTEUR);
   int Grille[LIGNE][COLONE];
   Init_Tab(Grille);

   int larg = LARGEUR;
   int haut = HAUTEUR;

   affi_Tex(Grille);
   affi_Gra(Grille, larg, haut);

   int running = 1;
   int pause = 0;
   int cordX, cordY;
   SDL_Event event;

   while (running)
   {
      while (SDL_PollEvent(&event))
      {
         switch (event.type)
         {
         case SDL_QUIT:
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

            case SDL_WINDOWEVENT_SIZE_CHANGED:
               larg = event.window.data1;
               haut = event.window.data2;
               affi_Gra(Grille, larg, haut);
               break;
            default:
               break;
            }
            break;
         
         case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button)
            {

            case SDL_BUTTON_RIGHT:
               cordX = Coordonne(event.button.x, 1, larg, haut);
               cordY = Coordonne(event.button.y, 0, larg, haut);
               Grille[cordY][cordX] = 0;
               break;
            case SDL_BUTTON_LEFT:
               cordX = Coordonne(event.button.x, 1, larg, haut);
               cordY = Coordonne(event.button.y, 0, larg, haut);
               Grille[cordY][cordX] = 1;
               break;
            default:
               break;
            }
            printf("Appui :%d %d\n", event.button.x, event.button.y);
            printf("Appui :%d %d\n", cordX, cordY);
            break;

         case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_SPACE:
               pause = !(pause);
               break;
            case SDLK_p:
               running = 0;
               ;
               break;
            default:
               break;
            }
            break;
         }
      }

      SDL_Delay(1); //  delai minimal

      affi_Tex(Grille);
      affi_Gra(Grille, larg, haut);
      SDL_Delay(100);
   }

   SDL_DestroyRenderer(renderer);

   SDL_DestroyWindow(window);

   SDL_Quit();

   return (0);
}
