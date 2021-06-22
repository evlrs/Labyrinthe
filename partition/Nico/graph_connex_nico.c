#include "graph_connex_nico.h"



void creerMat(int mat[][N]){
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            mat[i][j]=0;
        }
    }
}

void afficherMat(int mat[][N]){
    printf("\n");
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

