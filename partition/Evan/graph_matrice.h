#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 8

void afficherMat(int mat[][N]);
void initMat(int mat[][N]);
void randomMat(int mat[][N]);
void graphviz(FILE * fic, int mat[][N]);
void fusion(int liste[], int k, int j);
void comp_connexe(int mat[][N]);



