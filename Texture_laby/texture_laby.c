#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define LARGEUR 400
#define HAUTEUR 400

#define LIGNE 5
#define COLONE 5

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

SDL_Texture *Init_Texture(char *img)
{
   SDL_Surface *Image = NULL;
   SDL_Texture *Texture = NULL;

   Image = IMG_Load(img);
   if (Image == NULL)
   {
      fprintf(stdin, "Erreur chargement image : %s\n", SDL_GetError());
      SDL_DestroyWindow(window);
      SDL_DestroyRenderer(renderer);
   }
   Texture = SDL_CreateTextureFromSurface(renderer, Image);
   if (Texture == 0)
   {
      fprintf(stdin, "Erreur chargement texture : %s\n", SDL_GetError());
      SDL_DestroyWindow(window);
      SDL_DestroyRenderer(renderer);
   }
   SDL_FreeSurface(Image);

   return Texture;
}

void Init_Rect_Mur(SDL_Rect *etat, SDL_Rect *source)
{
   int nb_images_murW = 4;
   int nb_images_murH = 4;

   int set_x = source->w / nb_images_murW,
       set_y = source->h / nb_images_murH;

       printf("%d, %d \n",set_x,set_y);

   for (int i = 0; i < 16; i++)
   {
      etat[i].x = (i % 4) * set_x ;
      etat[i].y = (i/ 4) * set_y ;
      etat[i].w = set_x;
      etat[i].h = set_y;

       printf("x:%d y:%d w:%d h:%d\n",etat[i].x,etat[i].y,etat[i].w,etat[i].h);
   }
}

void Init_Tab(int tab[LIGNE][COLONE])
{
   int j, i;
   srand(time(NULL));

   for (i = 0; i < LIGNE; ++i)
   {
      for (j = 0; j < COLONE; ++j)
         tab[i][j] = rand()%16;
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

void affi_Gra(int tab[LIGNE][COLONE], SDL_Texture *Mur, SDL_Rect *source, SDL_Rect *dest)
{
   int i, j;
   int val = 16;
   SDL_RenderClear(renderer);

   for (i = 0; i < LIGNE; ++i)
   {
      for (j = 0; j < COLONE; ++j)
      {
         val = tab[i][j];
         //val=15;
         dest->x = j * dest->w;
         dest->y = i * dest->h;
         //printf("x:%d y:%d w:%d h:%d\n",source[val].x,source[val].y,source[val].w,source[val].h);
         SDL_RenderCopy(renderer, Mur, &source[val], dest);
      }
   }
}

int main()
{
   int Grille[LIGNE][COLONE];
   Init_Tab(Grille);

   Init_Window("V0 : Labyrinthe", LARGEUR, HAUTEUR);

   SDL_Texture *Mur = NULL;
   Mur = Init_Texture("mur.png");

   affi_Tex(Grille);

   int running = 1;

   SDL_Event event;

   SDL_Rect window_dim = {0};

   SDL_Rect dest_mur = {0};
   SDL_Rect source_mur = {0};
   SDL_Rect etat_mur[16] = {0};

   SDL_GetWindowSize(window, &window_dim.w, &window_dim.h);
   SDL_QueryTexture(Mur, NULL, NULL, &source_mur.w, &source_mur.h);

   dest_mur = window_dim;

   Init_Rect_Mur(etat_mur, &source_mur);

   dest_mur.w = window_dim.w / COLONE;
   dest_mur.h = window_dim.h / LIGNE;
   dest_mur.y = 0;
   dest_mur.x = 0;

   while (running)
   {
      while (SDL_PollEvent(&event))
      {
         switch (event.type)
         {
         case SDL_QUIT:
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

               /*case SDL_MOUSEBUTTONDOWN:
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
            case SDLK_p:
               running = 0;
               break;
            default:
               break;*/
            }
            break;
         }
      }

      SDL_Delay(1); //  delai minimal

      // affi_Tex(Grille);

      affi_Gra(Grille, Mur, etat_mur, &dest_mur);
      SDL_RenderPresent(renderer);
      SDL_Delay(100);
   }

   SDL_DestroyRenderer(renderer);

   SDL_DestroyWindow(window);

   SDL_Quit();

   return (0);
}
