#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define L 150
#define H 100
#define D (900/L)
#define NAR ((L-1)*H+(H-1)*L) //Nb aretes

typedef struct Triple{
    int depart;
    int arrivee;
    int val;
}triple;

int init_aretes(triple* aretes);
void afficher_aretes(triple* aretes);
void graphviz(triple* aretes, int taille);
void graphviz_chemin(triple* aretes, int taille);
int calcul_composantes(triple* aretes, triple* chemin, int liste[]);
void fusion(int liste[],int i, int val);
void afficherListe(int liste[], int taille);
void creer(triple* aretes ,int liste[], int taille);
void init_poids(triple* aretes, int poids[], int taille);
void graph_list(triple *list);
void melanger_aretes(triple* aretes);
int numero_sprite(int murs);
void nombre_murs(triple* chemin, int lab[H][L]);
void afficher_matrice(int lab[H][L]);
void voisins(int lab[H][L], int dist[H][L], int i, int j, int p);
