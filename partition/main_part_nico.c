#include "partition_nico.h"


int main(){
    int taille=12;
    int liste[taille];
    part *p0= (part*) malloc(sizeof(part));

    creer(liste,taille);
    afficherListe(liste,taille);
    fusion(liste,taille,6,2);
    afficherListe(liste,taille);
    fusion(liste,taille,2,7);
    afficherListe(liste,taille);

    return 0;
}