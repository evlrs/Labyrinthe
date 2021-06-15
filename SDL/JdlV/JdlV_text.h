#ifndef JdlV_H
#define JdlV_H

#include <stdio.h>
#include <stdlib.h>

#define LONGUEUR 150
#define LARGEUR 90

void initTableau(int tab[LARGEUR][LONGUEUR]);                
void afficheTableau(int tab[LARGEUR][LONGUEUR]);             
void copieTableau(int tab1[LARGEUR][LONGUEUR], int tab2[LARGEUR][LONGUEUR]);
int voisinsVivants(int tab[LARGEUR][LONGUEUR],int i, int j); 
int etatCellule(int tab[LARGEUR][LONGUEUR], int i, int j);
int etatFuturCellule(int tab[LARGEUR][LONGUEUR], int i, int j);


#endif