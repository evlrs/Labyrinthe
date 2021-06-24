#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define L 5 
#define H 3 
#define NAR ((L-1)*H+(H-1)*L) //Nb aretes

typedef struct Triple{
    int depart;
    int arrivee;
    int val;
}triple;

int init_aretes(triple* aretes);
void afficher_aretes(triple* aretes);
void graphviz(triple* aretes);
void calcul_composantes(triple* aretes, int liste[]);
void fusion2(int liste[],int i, int j, int val);
void afficherListe(int liste[], int taille);
void creer(int liste[], int taille);
void init_poids(triple* aretes, int poids[], int taille);
void graph_list(triple *list);
void melanger_aretes(triple* aretes);