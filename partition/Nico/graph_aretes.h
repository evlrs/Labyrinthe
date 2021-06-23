#include <stdio.h>
#include <stdlib.h>

#define maxAretes 50 

typedef struct Triple{
    int depart;
    int arrivee;
}triple;

void afficher_aretes(triple* aretes, int nbAretes);
void graphviz(FILE *fic,triple* aretes, int nbAretes);