#include "graph_aretes.h"



int main(){
    FILE *fic = NULL;
    int nbAretes;

    
    triple* aretes;
    aretes= malloc(maxAretes*sizeof(triple));
    srand(time(NULL));


    nbAretes=init_aretes(aretes);
    
    afficher_aretes(aretes,nbAretes);
    graphviz(fic,aretes,nbAretes);

    int liste[nbNoeud];
    int poids[nbNoeud];
    creer(liste,nbNoeud);
    init_poids(aretes,poids,nbNoeud);
    calcul_composantes(aretes,liste,poids,nbAretes);
    afficherListe(liste,nbNoeud);
    afficherListe(poids,nbNoeud);
    free(aretes);
}

int init_aretes(triple* aretes){
    int seuil=5; //pourcentage qu'une arete soit cree
    int nbAretes=0;
    for(int i=0;i<nbNoeud;++i){
        for(int j=0;j<i;++j){
            if((rand()%100<seuil) && i!=j){
                aretes[nbAretes].depart=i;
                aretes[nbAretes].arrivee=j;
                aretes[nbAretes].val=rand()%10;
                ++nbAretes;
            }
        }
    }
    return nbAretes;
}

void afficher_aretes(triple* aretes, int nbAretes){
    int d,a;
    if(nbAretes<=maxAretes){
        for(int i=0;i<nbAretes;++i){
            d=(aretes[i]).depart;
            a=(aretes[i]).arrivee;
            printf("%d -- %d\n",d,a);
        }
    }
}

void graphviz(FILE *fic,triple* aretes, int nbAretes){
    int d,a,v;

    fic=fopen("graph_aretes_nico.dot","w");
    if(fic!=NULL){
        
        fputs("graph {\n",fic);
        if(nbAretes<=maxAretes){
            for(int i=0;i<nbAretes;++i){
                d=aretes[i].depart;
                a=aretes[i].arrivee;
                v=aretes[i].val;
                fprintf(fic,"    %d -- %d [label= %d];\n",d,a,v);
            }
        }
        fputs("}\n",fic);
        fclose(fic);  
        system("dot -Tjpg graph_aretes_nico.dot -o graph_aretes_nico.jpg");
        //system("sleep 0.5");
    }
}

/* Calcule des composantes connexes */
void calcul_composantes(triple* aretes, int liste[], int poids[], int nbAretes){
    
    
    for(int i=0;i<nbAretes;++i){
        fusion2(liste,poids,aretes[i].depart,aretes[i].arrivee,aretes[i].val);  

    }
}

/* Fusionne pour faire des arbres */
void fusion2(int liste[], int poids[], int i, int j, int pd){
    int val=liste[j];
    int sommePd=0;
    for(int k=0;k<nbNoeud;++k){
        if(liste[k]==val){
            liste[k]=liste[i];
            sommePd+=poids[k];
        }
    }

    for(int k=0;k<nbNoeud;++k){
        if(liste[k]==val){
            poids[k]=sommePd;
        }
    }
}

/* Affiche la liste du tas */
void afficherListe(int liste[], int taille){
    for(int i=0;i<taille;++i){
        printf("%d ",liste[i]);
    }
    printf("\n");
}

/* Crée une liste la valeur égale à l'indice */
void creer(int liste[], int taille){
    for(int i=0;i<taille;++i){
        liste[i]=i;
    }
}

void init_poids(triple* aretes, int poids[], int taille){
    for(int i=0;i<taille;++i){
        poids[i]=aretes[i].val;
    }
}