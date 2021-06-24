#ifndef GRAPH_ARETE_H
#define GRAPH_ARETE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define N 5 //nombre de noeud
/* il y a donc n(n-1)/2 nimbre d'arete maximum*/

#define maxAretes N*(N-1)/2


typedef struct aretes{
    int depart;
    int arrivee;
    int value;
}aretes;


void afficheAretes(aretes* listptr, int nbAretes);
void initAretes(aretes *p0);

#endif 