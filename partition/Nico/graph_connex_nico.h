#ifndef graph__H
#define graph_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define N 10        //nombre de noeuds potentiels
#define NOEUDS 25   //nombre de noeuds actifs

int mat[N][N];

void creerMat();
void afficherMat();
void random1();
void graphviz_gconnex(FILE* fic);
void calcul_composantes(int liste[]);
void fusion2(int liste[],int i, int j);


#endif