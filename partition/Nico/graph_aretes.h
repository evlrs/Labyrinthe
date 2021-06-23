#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define maxAretes 50 
#define nbNoeud 20

typedef struct Triple{
    int depart;
    int arrivee;
    int val;
}triple;

int init_aretes(triple* aretes);
void afficher_aretes(triple* aretes, int nbAretes);
void graphviz(FILE *fic,triple* aretes, int nbAretes);
void calcul_composantes(triple* aretes, int liste[], int poids[], int nbAretes);
void fusion2(int liste[], int poids[],int i, int j, int val);
void afficherListe(int liste[], int taille);
void creer(int liste[], int taille);
void init_poids(triple* aretes, int poids[], int taille);