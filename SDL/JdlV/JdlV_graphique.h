#ifndef JdlV_graphique_H
#define JdlV_graphique_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

void initGrille(SDL_Window *win, SDL_Renderer *renderer);
void pixelNoir(SDL_Window *win, SDL_Renderer *renderer, int x, int y);

#endif