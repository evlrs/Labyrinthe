#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define LARGEUR 1200
#define HAUTEUR 600

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int Init_Window(char *titre)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stdin, "Erreur d'initialisation de la SDL : %s \n", SDL_GetError());
        return EXIT_FAILURE;
    }
    window = SDL_CreateWindow(titre, 0, 0, LARGEUR, HAUTEUR, SDL_WINDOW_RESIZABLE);
    if (window == 0)
    {
        fprintf(stdin, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
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

void Aff_textu_full(SDL_Texture *Texture)
{
    SDL_Rect dest = {0};
    SDL_Rect window_dim = {0};
    SDL_Rect source = {0};

    SDL_GetWindowSize(window, &window_dim.w, &window_dim.h);
    SDL_QueryTexture(Texture, NULL, NULL, &source.w, &source.h);

    dest = window_dim;
    if (Texture == NULL)
    {
        fprintf(stdin, "Erreur chargement texture : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
    }
    SDL_RenderCopy(renderer, Texture, &source, &dest);
}

TTF_Font *Init_Font(char *text)
{
    if (TTF_Init() < 0)
    {
        fprintf(stdin, "Erreur d'initialisation de la TTF: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
    }

    TTF_Font *font = NULL;

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

void Aff_Score(TTF_Font *Txt, SDL_Color color, SDL_Rect *pos, char *score_t, int nscore_t)
{
    char lettre[] = "i";

    for (int k = 0; k < (nscore_t); ++k)
    {
        switch (k % 7)
        {
        case (0):
            color.r = 240;
            color.g = 50;
            color.b = 255;
            break;
        case (1):
            color.r = 50;
            color.g = 90;
            color.b = 255;
            break;
        case (2):
            color.r = 50;
            color.g = 180;
            color.b = 255;
            break;
        case (3):
            color.r = 50;
            color.g = 255;
            color.b = 50;
            break;
        case (4):
            color.r = 255;
            color.g = 255;
            color.b = 50;
            break;
        case (5):
            color.r = 255;
            color.g = 200;
            color.b = 50;
            break;
        case (6):
            color.r = 255;
            color.g = 50;
            color.b = 50;
            break;
        }

        lettre[0] = score_t[k];
        SDL_Surface *text_surface = NULL;
        SDL_Texture *text_texture = NULL;

        text_surface = TTF_RenderText_Blended(Txt, lettre, color);

        text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

        SDL_FreeSurface(text_surface);

        SDL_QueryTexture(text_texture, NULL, NULL, &pos->w, &pos->h);
        SDL_RenderCopy(renderer, text_texture, NULL, pos);
        SDL_DestroyTexture(text_texture);

        pos->x += pos->w;
    }
}

/*--------------------------------------------------------------------------*/
/*        Code utile                                                        */
/* printf("x:%d y:%d w:%d h:%d\n",pos.x,pos.y,pos.w,pos.h);                 */
/* gcc Nyancat.c -o Nyancat -g -lSDL2 -lSDL2_image -lSDL2_ttf -Wall -Wextra */
/*--------------------------------------------------------------------------*/

int main()
{

    SDL_Texture *CAT = NULL;
    SDL_Texture *Fond = NULL;
    SDL_Texture *Planet = NULL;
    TTF_Font *Txt = NULL;

    Init_Window("Nyancat");
    Fond = Init_Texture("./Image/fond_Cat.jpg");
    CAT = Init_Texture("./Image/CAT.png");
    Planet = Init_Texture("./Image/planet3.png");

    Txt = Init_Font("./fonts/slkscr.ttf");

    Aff_textu_full(Fond);
    SDL_RenderPresent(renderer);
    SDL_Delay(10);

    char score_t[] = "Le score est de : 00";
    int nscore_t = strlen(score_t);
    int Score = 0;

    char level_t[] = "Niveau suivant: 1";
    int nlevel_t = strlen(level_t);
    int Level = 1;
    int cur_L = 0;

    int suivant = 0;

    int running = 1;
    SDL_Event event;
    SDL_Rect window_dim = {0};

    SDL_Rect dest_cat = {0};
    SDL_Rect source_cat = {0};
    SDL_Rect etat_cat = {0};

    SDL_Rect dest_plan[10] = {0};
    SDL_Rect source_plan = {0};
    SDL_Rect etat_plan = {0};

    SDL_Rect pos = {0};
    SDL_Color color = {0, 0, 0, 255};

    srand(time(NULL));
    int coli = 0;

    SDL_GetWindowSize(window, &window_dim.w, &window_dim.h);
    SDL_QueryTexture(CAT, NULL, NULL, &source_cat.w, &source_cat.h);
    SDL_QueryTexture(Planet, NULL, NULL, &source_plan.w, &source_plan.h);

    dest_cat = window_dim;

    int vit_plan = 10;
    float vit_cat = 10;
    int nb_images_cat = 5;
    int nb_images_plan = 10;
    float zoom_cat = 2.5;
    float zoom_plan = 0.1;
    int catset_x = source_cat.w / nb_images_cat,
        catset_y = source_cat.h;

    int planset_x = source_plan.w / nb_images_plan,
        planset_y = source_plan.h;

    etat_cat.x = 0;
    etat_cat.y = 0;
    etat_cat.w = catset_x;
    etat_cat.h = catset_y;

    etat_plan.x = 0;
    etat_plan.y = 0;
    etat_plan.w = planset_x;
    etat_plan.h = planset_y;

    dest_cat.w = catset_x * zoom_cat;
    dest_cat.h = catset_y * zoom_cat;

    dest_cat.y = (window_dim.h - dest_cat.h) / 2;
    dest_cat.x = 0;

    source_plan.x = 0;
    source_plan.y = 0;

    /*dest_plan[0].w = planset_x * zoom_plan;
    dest_plan[0].h = planset_y * zoom_plan;

    dest_plan[0].x = window_dim.w - dest_plan[0].w / 2;
    dest_plan[0].y = 50 + (rand() % ((window_dim.h - dest_plan[0].h - 50)));*/

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
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:
                    printf("appui sur la croix\n");
                    break;
                default:
                    break;
                }
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    dest_cat.y -= pos.h;
                    dest_cat.y -= dest_cat.h / vit_cat - window_dim.h + pos.h;
                    dest_cat.y %= window_dim.h - pos.h;
                    dest_cat.y += pos.h;
                    break;
                case SDLK_DOWN:
                    dest_cat.y -= pos.w;
                    dest_cat.y += dest_cat.h / vit_cat;
                    dest_cat.y %= window_dim.h - pos.w;
                    dest_cat.y += pos.w;
                    break;
                case SDLK_RETURN:
                    suivant = 1;
                    break;
                default:
                    break;
                }
                break;
            }
        }

        if (coli == 0)
        {

            SDL_RenderClear(renderer);
            Aff_textu_full(Fond);

            if (Level == cur_L && suivant == 1)
            {
                pos.x = 0;
                pos.y = 0;
                Aff_Score(Txt, color, &pos, score_t, nscore_t);

                etat_cat.x += catset_x;
                etat_cat.x %= source_cat.w;
                SDL_RenderCopy(renderer, CAT, &etat_cat, &dest_cat);

                etat_plan.x += planset_x;
                etat_plan.x %= source_plan.w;

                for (int i = 0; i < Level; i++)
                {

                    if (dest_plan[i].x <= -dest_plan[i].w)
                    {
                        dest_plan[i].w = planset_x * zoom_plan;
                        dest_plan[i].h = planset_y * zoom_plan;
                        dest_plan[i].x = window_dim.w + rand() % ((window_dim.w / 3) - dest_plan[i].w);
                        dest_plan[i].y = rand() % (window_dim.h - dest_plan[i].h);
                        dest_plan[i].y += pos.h;

                        if (i == 0)
                        {
                            vit_plan -= 0.5;
                            Score++;
                            score_t[nscore_t - 2] = Score / 10 + '0';
                            score_t[nscore_t - 1] = Score % 10 + '0';
                        }

                        if (vit_plan <= 0.5)
                        {
                            vit_plan = 10;
                            Level++;
                            level_t[nlevel_t - 1] = Level % 10 + '0';
                        }

                       /* Score++;
                        score_t[nscore_t - 2] = Score / 10 + '0';
                        score_t[nscore_t - 1] = Score % 10 + '0';*/
                    }
                    else
                    {
                        dest_plan[i].x -= dest_plan[i].w / vit_plan;
                    }

                    coli = SDL_HasIntersection(&dest_cat, &dest_plan[i]);

                    SDL_RenderCopy(renderer, Planet, &etat_plan, &dest_plan[i]);
                }
            }
            else
            {
                suivant = 0;
                pos.x = (window_dim.w - (nlevel_t * pos.w)) / 2;
                pos.y = (window_dim.h - pos.h) / 2;
                Aff_Score(Txt, color, &pos, level_t, nlevel_t);
                cur_L = Level;
            }
        }
        else
        {
            SDL_RenderClear(renderer);
            Aff_textu_full(Fond);

            pos.x = (window_dim.w - (nscore_t * pos.w)) / 2;
            pos.y = (window_dim.h - pos.h) / 2;
            Aff_Score(Txt, color, &pos, score_t, nscore_t);
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

    return (0);
}