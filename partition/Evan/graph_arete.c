#include "graph_arete.h"


int main(){
    FILE *fic = NULL;
    int taille=N;

    //int maxAretes=taille*(taille-1)/2;
    aretes* listptr;
    printf("%d\n",maxAretes);
    //aretes* listptr[maxAretes];
    listptr=malloc(maxAretes*sizeof(aretes));

    srand(time( NULL ) );
    int nbAretes=rand()%maxAretes;

    afficheAretes(listptr,nbAretes);


    /*for (int j=0;j<nbAretes;j++){
        
        
    }

   */                

    free(listptr);
    
}


void modifAretes(aretes *listptr,int nbAretes){
    printf("%d",N);
    printf("%d",nbAretes);

    for (int j=0;j<nbAretes;j++){

        printf("%d",listptr[j].depart);

    }
    


}
    

void afficheAretes(aretes* listptr, int nbAretes){
    int a,d;
    printf("%d",nbAretes);
    printf("\n");
    if(nbAretes<=maxAretes){
        for(int i=0;i<nbAretes;++i){
            d=(listptr[i]).depart;
            a=(listptr[i]).arrivee;
            printf("%d--%d\n",d,a);
        }
    }
    
}






/*for (int j=0;j<N;j++){
    initNoeuds(n0,i);
}
list[2];
list[]={1,2}
printf("%d",list[3])
*/

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

/*for (int i=0;i<N;i++){
            p0->depart[i]=;
            p0->arrivee[i];
            p0->value[i];
        }
*/

/*void randominit(){
    noeud* n0=NULL;
    srand(time( NULL ) );


    for (int j=0;j<N;j++){
        val=rand()%N;
        initNoeuds(n0);
    }

}
*/




