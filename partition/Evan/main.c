#include "partition.h"


int main(){
    int taille=11;
    int retour;
    int liste[taille];
    part *p0= (part*) malloc(sizeof(part));
    FILE *fic = NULL;

    creer(liste,taille);
    
    retour=fusion(liste,taille,0,1);
    graphviz(fic,liste,taille);
    retour=fusion(liste,taille,2,3);
    graphviz(fic,liste,taille);
    retour=fusion(liste,taille,10,3);
    graphviz(fic,liste,taille);
    /*retour=fusion(liste,taille,5,9);
    graphviz(fic,liste,taille);
    retour=fusion(liste,taille,4,6);
    graphviz(fic,liste,taille);
    retour=fusion(liste,taille,8,7);
    graphviz(fic,liste,taille);
    retour=fusion(liste,taille,9,7);
    graphviz(fic,liste,taille);
    retour=fusion(liste,taille,6,8);
    graphviz(fic,liste,taille);
    */

    afficherListe(liste,taille);

    lister_classe(liste,taille,2);

    lister_partition(p0,liste,taille);

    graphviz(fic,liste,taille);

    return 0;
}