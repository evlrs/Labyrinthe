#include "partition_nico.h"
#include "graph_connex_nico.h"



int main(){
    int taille=N;
    int liste[taille];
    int hauteur[taille];
    int racine[taille];
    part *p0= (part*) malloc(sizeof(part));
    FILE *fic = NULL;
    
    
    creer(liste,taille);
    creer(racine,taille);
    initTabArbre(hauteur,taille);
    /*
    fusion(liste,racine,hauteur,taille,0,1);
    fusion(liste,racine,hauteur,taille,2,3);
    fusion(liste,racine,hauteur,taille,10,3);
    fusion(liste,racine,hauteur,taille,5,9);
    fusion(liste,racine,hauteur,taille,4,6);
    fusion(liste,racine,hauteur,taille,8,7);
    fusion(liste,racine,hauteur,taille,9,7);
    fusion(liste,racine,hauteur,taille,6,7);
    
    afficherListe(liste,taille);
    afficherListe(racine,taille);
    afficherListe(hauteur,taille);
    */
    //lister_classe(liste,taille,1);

    //lister_partition(p0,liste,taille);

    //graphviz_partition(fic,liste,taille);


    creerMat();
    random1();
    afficherMat();

    graphviz_gconnex(fic);
    calcul_composantes(liste);
    afficherListe(liste,taille);

    free(p0);
    return 0;
}