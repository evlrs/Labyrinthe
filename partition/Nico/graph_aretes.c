#include "graph_aretes.h"



int main(){
    FILE *fic = NULL;
    int nbAretes=10;
    triple* aretes;
    aretes= malloc(maxAretes*sizeof(triple));
    printf("1\n");
    for(int i=0;i<nbAretes;++i){
        aretes[i].depart=i*3%6;
        aretes[i].arrivee=i*8%3;
    }
    printf("aff\n");
    afficher_aretes(aretes,nbAretes);
    graphviz(fic,aretes,nbAretes);
}

void afficher_aretes(triple* aretes, int nbAretes){
    int d,a;
    printf("a\n");
    if(nbAretes<=maxAretes){
        for(int i=0;i<nbAretes;++i){
            d=(aretes[i]).depart;
            a=(aretes[i]).arrivee;
            printf("%d -- %d\n",d,a);
        }
    }
}
void graphviz(FILE *fic,triple* aretes, int nbAretes){
    int d,a;

    fic=fopen("graph_aretes_nico.dot","w");
    if(fic!=NULL){
        
        fputs("graph {\n",fic);
        if(nbAretes<=maxAretes){
            for(int i=0;i<nbAretes;++i){
                d=(aretes[i]).depart;
                a=(aretes[i]).arrivee;
                fprintf(fic,"    %d -> %d;\n",d,a);
            }
        }
        fputs("}\n",fic);
        fclose(fic);  
        system("dot -Tjpg graph_aretes_nico.dot -o graph_aretes_nico.jpg");
        system("sleep 0.5");
    }
}
