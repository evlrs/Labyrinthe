#include "partition_nico.h"



int main(){
    int taille=11;
    int liste[taille];
    part *p0= (part*) malloc(sizeof(part));
    FILE *fic = NULL;
    fic=fopen("graph_partition_nico.dot","w");
    fputs("digraph {\n",fic);
    
    creer(liste,taille);

    fusion(fic,liste,taille,0,1);
    fusion(fic,liste,taille,2,3);
    fusion(fic,liste,taille,10,3);
    fusion(fic,liste,taille,5,9);
    fusion(fic,liste,taille,4,6);
    fusion(fic,liste,taille,8,7);
    fusion(fic,liste,taille,9,7);
    fusion(fic,liste,taille,6,8);

    //afficherListe(liste,taille);

    lister_classe(liste,taille,1);

    lister_partition(p0,liste,taille);

    graphviz(fic,liste,taille);
    fputs("}\n",fic);
    fclose(fic);  
    system("dot -Tjpg graph_partition_nico.dot -o graph_partition_nico.jpg");
    system("sleep 0.5");

    return 0;
}