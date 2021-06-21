#ifndef partition_nico_H
#define partition_nico_H


#include <stdio.h>
#include <stdlib.h>

void afficherListe(int liste[], int taille);
void creer(int liste[], int taille);
void fusion(int liste[], int taille, int k, int j);
int recuperer_classe(int liste[], int taille, int i);
void lister_classe(int liste[], int taille);

typedef int element_part;
typedef struct Part{
    int taille;
    element_part *base;
}part;

#endif