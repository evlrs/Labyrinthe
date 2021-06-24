#include "kru.h"



int main(){
    
    int nbAretes;

    triple* aretes;
    aretes= malloc(NAR*sizeof(triple));
    if(aretes == NULL) {
        fprintf(stderr, "allocation error\n");
        return 1;
    }

    srand(time(NULL));


    nbAretes=init_aretes(aretes);
    if(nbAretes!=NAR){
        printf("Initialisation aretes pas bonnes : %d != %d \n",nbAretes,NAR);
    }

    afficher_aretes(aretes);
    graphviz(aretes);
    melanger_aretes(aretes);
    afficher_aretes(aretes);
    graphviz(aretes);
    
    int liste[NAR];
    creer(liste,NAR);
    calcul_composantes(aretes,liste);
    afficherListe(liste,NAR);
    
    free(aretes);
}

int init_aretes(triple* aretes){
    int nbAretes=0;
    for(int i=0;i<L;++i){
        for(int j=0;j<H;++j){
            if(i<(L-1)){
                aretes[nbAretes].depart=i*L+j;
                aretes[nbAretes].arrivee=i*L+j+1;
                aretes[nbAretes].val=nbAretes;
                nbAretes++;
            }
            if(j<(H-1)){
                aretes[nbAretes].depart=i*L+j;
                aretes[nbAretes].arrivee=(i+1)*L+j;
                aretes[nbAretes].val=nbAretes;
                nbAretes++;
            }
        }
    }
    
    return nbAretes;
}


void afficher_aretes(triple* aretes){
    int d,a,nb,k;
    for(int i=0;i<NAR;++i){
        k=aretes[i].val;
        nb=aretes[k].val;
        d=aretes[k].depart;
        a=aretes[k].arrivee;
        printf("%d : %d -- %d\n",nb,d,a);
    }
    
}


void graphviz(triple* aretes){
    int d,a,v;
    FILE * fic = NULL;
    
    fic=fopen("kru_nico.dot","w");

    if(fic!=NULL){
        
        fputs("graph {\n",fic);
        for(int i=0;i<NAR;++i){
            
            d=aretes[i].depart;
            a=aretes[i].arrivee;
            v=aretes[i].val;
            fprintf(fic,"    %d -- %d [label= %d];\n",d,a,v);
        }
        
        fputs("}\n",fic);
        fclose(fic);  
        system("dot -Tjpg kru_nico.dot -o kru_nico.jpg");
        system("sleep 1");
    }
}

void melanger_aretes(triple* aretes){
    int x;
    int k;
    for(int i=0;i<(NAR-1);++i){
        k=i+rand()%(NAR-i);
        /*
        x=aretes[i].depart;
        aretes[i].depart=aretes[k].depart;
        aretes[k].depart=x;
        x=aretes[i].arrivee;
        aretes[i].arrivee=aretes[k].arrivee;
        aretes[k].arrivee=x;
        */
        x=aretes[i].val;
        aretes[i].val=aretes[k].val;
        aretes[k].val=x;
    }
}



/* Calcule des composantes connexes */
void calcul_composantes(triple* aretes, int liste[]){
    
    for(int i=0;i<NAR;++i){
        fusion2(liste,aretes[i].depart,aretes[i].arrivee,aretes[i].val);  

    }
}

/* Fusionne pour faire des arbres */
void fusion2(int liste[], int i, int j, int val){

    for(int k=0;k<NAR;++k){
        if(liste[k]==val){
            liste[k]=liste[i];
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