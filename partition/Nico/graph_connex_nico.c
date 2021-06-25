#include "graph_connex_nico.h"
#include "partition_nico.h"

/* Init mat avec que des 0 */
void creerMat(){
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            mat[i][j]=0;
        }
    }
}

/* Affiche la matrice */
void afficherMat(){
    printf("\n");
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* Met nbde1 fois de 1 aléatoirement dans la mat inferieur */ 
void random1(){
    srand(time(NULL));
    int l,L;
    for(int k=0;k<NOEUDS;++k){
        l=rand()%N;
        L=rand()%N;
        if(l>L){
            if(mat[l][L]==1){
                k--;
            }else{
                mat[l][L]=1;
            }
        }else{
            if(mat[L][l]==1){
                k--;
            }else{
                mat[L][l]=1;
            }
        }
    }
}

/* Crée et afficher le graph connex */
void graphviz_gconnex(FILE* fic){
    fic=fopen("graph_connex_nico.dot","w");
    if(fic!=NULL){
        
        fputs("graph {\n",fic);

        for(int i=0;i<N;++i){
            for(int j=0;j<i;++j){
                if(mat[i][j]==1)    fprintf(fic,"    %d -- %d;\n",i,j);
            }
        }
        
        fputs("}\n",fic);
        fclose(fic);  
        system("dot -Tjpg graph_connex_nico.dot -o graph_connex_nico.jpg");
        system("sleep 0.5");
    }
}

/* Calcule des composantes connexes */
void calcul_composantes(int liste[]){
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            if(mat[i][j]==1){
                fusion2(liste,i,j);
            }  
        } 
    }
}

/* Fusionne pour faire des arbres */
void fusion2(int liste[],int i, int j){
    int val=liste[j];
    for(int k=0;k<N;++k){
        if(liste[k]==val){
            liste[k]=liste[i];
        }
        
    }
}
