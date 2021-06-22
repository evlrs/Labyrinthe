#ifndef partition__H
#define partition_H


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
void fusion(int liste[], int racine[], int hauteur[], int taille, int k, int j);
int recuperer_classe(int liste[], int taille, int i);
void lister_classe(int liste[], int taille, int classe);
void init_partition(part *p0, int taille);
void lister_partition(part *p0, int liste[], int taille);
void graphviz(FILE* fic,int liste[], int taille);
int mere(int liste[], int k);
void initTabArbre(int hauteur[], int taille);
int grandArbre(int liste[], int hauteur[], int a, int b);
int haut(int liste[], int hauteur[], int i);
void changRacine(int racine[], int taille, int ancienne, int nouvelle);

#endif