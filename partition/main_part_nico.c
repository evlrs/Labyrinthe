#include "partition_nico.h"


int main(){
    int taille=8;
    int liste[taille];
    part *p0= (part*) malloc(sizeof(part));

    creer(liste,taille);
    afficherListe(liste,taille);
    fusion(liste,taille,6,2);
    afficherListe(liste,taille);
    fusion(liste,taille,2,7);
    afficherListe(liste,taille);
    
    lister_classe(liste,taille,2);

    lister_partition(p0,liste,taille);
    return 0;
}