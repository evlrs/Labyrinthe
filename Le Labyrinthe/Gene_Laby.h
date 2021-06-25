#include "Labyrinthe.h"

#define D (1900 / COLONE)
#define NAR ((COLONE - 1) * LIGNE + (LIGNE - 1) * COLONE) //Nb aretes

typedef struct Triple
{
    int depart;
    int arrivee;
    int val;
} triple;

void Gene_matrice(int lab[LIGNE][COLONE]);

int init_aretes(triple *aretes);

void melanger_aretes(triple *aretes);

void calcul_composantes(triple *aretes, triple *chemin, int liste[]);

void fusion(int liste[], int i, int val);

void creer(triple *aretes, int liste[], int taille);

void nombre_murs(triple *chemin, int lab[LIGNE][COLONE]);

void afficher_matrice(int lab[LIGNE][COLONE]);

int Init_Dist(int lab[LIGNE][COLONE],int dist[LIGNE][COLONE]);

int voisins(int lab[LIGNE][COLONE], int dist[LIGNE][COLONE], int i, int j, int p);
