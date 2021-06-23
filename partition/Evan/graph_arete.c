#include "graph_arete.h"


int main(){
    noeud* n0=NULL;
    for (int j=0;j<N;j++){
        initNoeuds(n0,i);
    }
    


    /*FILE *fic = NULL;
    FILE *fic2 = NULL;
    int mat[N][N];
    initMat(mat);
    afficherMat(mat);
    randomMat(mat);
    afficherMat(mat);
    graphviz(fic,mat);
    comp_connexe(mat);
    graphviz(fic,mat);

    return 1;*/
}


void randominit(){
    noeud* n0=NULL;
    for (int j=0;j<N;j++){
        initNoeuds(n0,i);
    }

}
void initNoeuds(noeud *n0,int val,int nbnoeud1, int list){
    
    if(n0==NULL){
        printf("Erreur\n");
        }
    else{
        n0->numnoeud=val;
        n0->nbnoeud=nbnoeud1;
        for (int i=0;i<N;i++){
            if 
            n0->aretes[i]=-1;
        }
        n0->suivant = (noeud*) malloc(sizeof(noeud));
    }
}



void afficherPart(int mat[][N]){
    printf("\n");
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            printf(" %d |",mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

