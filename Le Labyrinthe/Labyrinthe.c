#include "Labyrinthe.h"
#include "Gene_Laby.h"

int main()
{
   int Grille[LIGNE][COLONE];
   Gene_matrice(Grille);

   

   Init_Window("V0 : Labyrinthe", LARGEUR, HAUTEUR);

   SDL_Texture *Mur = NULL;
   Mur = Init_Texture("mur3.png");

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
            running = 0;
            break;

         case SDL_WINDOWEVENT:
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
               printf("appui sur la croix\n");
               break;
            }
            break;
         }
      }

      SDL_Delay(1); //  delai minimal

      affi_Gra(Grille, Mur, etat_mur, &dest_mur);
      SDL_RenderPresent(renderer);
      SDL_Delay(100);
   }

   SDL_DestroyRenderer(renderer);

   SDL_DestroyWindow(window);

   SDL_Quit();

   return (0);
}

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

   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
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

   for (int i = 0; i < (nb_images_murW * nb_images_murH); i++)
   {
      etat[i].x = (i % nb_images_murW) * set_x;
      etat[i].y = (i / nb_images_murH) * set_y;
      etat[i].w = set_x;
      etat[i].h = set_y;
   }
}

void affi_Gra(int tab[LIGNE][COLONE], SDL_Texture *Mur, SDL_Rect *source, SDL_Rect *dest)
{
   int i, j;
   int val = 20;
   SDL_RenderClear(renderer);

   for (i = 0; i < LIGNE; ++i)
   {
      for (j = 0; j < COLONE; ++j)
      {
         val = tab[i][j];
         dest->x = j * dest->w;
         dest->y = i * dest->h;
         SDL_RenderCopy(renderer, Mur, &source[val], dest);
      }
   }
}
