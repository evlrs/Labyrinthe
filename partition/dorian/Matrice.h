#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void aff_matrice(int ** matrice, int m, int n);   //procedure d'affichage d'une matrice

int ** gen_matrice(int m,int n);       //fonction de creation d'une matrice

void free_matrice(int **matrice,int m);           //procedure de liberation memoire d'une matrice