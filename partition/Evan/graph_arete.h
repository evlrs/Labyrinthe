#ifndef GRAPH_ARETE_H
#define GRAPH_ARETE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define N 8


typedef struct noeud{
    int numnoeud;
    int nbnoeud;
    int aretes[N];
    struct noeud *suivant;
}noeud;



void initNoeuds(noeud *n0,int val);

#endif 