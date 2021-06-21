#include "partition_nico.h"


int main(){
    int taille=10;
    int liste[taille];
    part *p0= (part*) malloc(sizeof(part));
    FILE *fic = NULL;

    creer(liste,taille);
    
    fusion(liste,taille,6,2);
    graphviz(fic,liste,taille);
    fusion(liste,taille,2,7);
    graphviz(fic,liste,taille);
    fusion(liste,taille,7,6);
    graphviz(fic,liste,taille);
    fusion(liste,taille,9,3);
    graphviz(fic,liste,taille);
    fusion(liste,taille,2,5);
    graphviz(fic,liste,taille);
    fusion(liste,taille,6,1);
    graphviz(fic,liste,taille);

    afficherListe(liste,taille);

    lister_classe(liste,taille,2);

    lister_partition(p0,liste,taille);

    graphviz(fic,liste,taille);

    return 0;
}