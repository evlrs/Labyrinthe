#include "graph_matrice.h"




int main(){
    FILE *fic = NULL;
    FILE *fic2 = NULL;
    int mat[N][N];
    initMat(mat);
    afficherMat(mat);
    randomMat(mat);
    afficherMat(mat);
    graphviz(fic,mat);
    comp_connexe(mat);
    graphviz(fic,mat);

    return 1;
}

void initMat(int mat[][N]){
    for(int i=0;i<N;++i){
        for(int j=i;j<N;++j){
            if (i==j){
                mat[i][j]=0;
            }
            else{
                mat[i][j]=0;
                mat[j][i]=0;
            }
        }
    }
}

void afficherMat(int mat[][N]){
    printf("\n");
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            printf(" %d |",mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void randomMat(int mat[][N]){
    int l;
    srand(time( NULL ) );
    for(int i=0;i<N;++i){
        for(int j=i;j<N;++j){
            if (i!=j){
                l=rand()%2;
                mat[i][j]=l;
                mat[j][i]=l;
            }
        }
    }
}



void graphviz(FILE * fic, int mat[][N]){
    int g,d;
    fic=fopen("graph_mat_evan.dot","w");
    if(fic!=NULL){
        
        fputs("graph {\n",fic);
        for(int i=0;i<N;++i){
            for(int j=i;j<N;++j){
                if (mat[i][j]==1){
                    fprintf(fic,"    %d--%d;\n",i,j);
                }            
            }
        }
   

        fputs("}\n",fic);
        fclose(fic);  
        system("dot -Tjpg graph_mat_evan.dot -o graph_mat_evan.jpg");
        system("sleep 1");
    }
}


void fusion(int liste[], int k, int j){
    int retour=0;
    int val1=liste[k];
    int val2=liste[j];
    if (val1!=val2){
        for(int i=0;i<N;++i){
            if(liste[i]==val1) liste[i]=val2;
        }
    }

}


void comp_connexe(int mat[][N]){
    int list[N];
    for (int i=0;i<N;i++){
        list[i]=i;
    }

    for(int i=0;i<N;++i){
        for(int j=i;j<N;++j){
            if (mat[i][j]==1){
                fusion(list,i,j);
            }
            
        }
    }
    for (int i=0;i<N;i++){
        printf(" %d |",list[i]);
    }
    printf("\n");

}

/*void graphviz2(FILE * fic2, int mat[][N]){
    int g,d;
    fic2=fopen("sous_graph.dot","w");
    if(fic2!=NULL){
        
        fputs("graph {\n",fic);
        for (int i=0;i<N;i++){
        printf(" %d |",list[i]);
        }
        for(int i=0;i<N;++i){
            for(int j=i;j<N;++j){
                if (mat[i][j]==1){
                    fprintf(fic2,"    %d--%d;\n",i,j);
                }            
            }
        }
   

        fputs("}\n",fic2);
        fclose(fic2);  
        system("dot -Tjpg sous_graph.dot -o sous_graph.jpg");
        system("sleep 1");
    }
}
*/









