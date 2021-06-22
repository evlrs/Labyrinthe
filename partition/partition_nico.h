#ifndef partition_nico_H
#define partition_nico_H


#include <stdio.h>
#include <stdlib.h>
typedef struct Elmt{
    int pos;
    struct Elmt *suivant;
}elmt;

typedef struct Part{
    int taille;
    elmt **base;
}part;



void afficherListe(int liste[], int taille);
void creer(int liste[], int taille);
void fusion(FILE* fic, int liste[], int taille, int k, int j);
int recuperer_classe(int liste[], int taille, int i);
void lister_classe(int liste[], int taille, int classe);
void init_partition(part *p0, int taille);
void lister_partition(part *p0, int liste[], int taille);
void graphviz(FILE* fic,int liste[], int taille);



#endif