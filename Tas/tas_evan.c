#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int taille=9;

/*void initTas(int list[taille]){
    int tas[taille]={};
    while tas[taille]!=
}*/


int parent(int indice){
    return floor((indice-1)/2);
}

int droite(int indice){
    return  2*indice-1;
}

int gauche(int indice){
    return 2*indice+1;
}

void inserTas(int tas[],int taille, int val){
    taille+=1;
    int i=taille;
    int temp=0;
    
    while(val>tas[parent(i)]){

        temp=tas[parent(i)];
        tas[parent(i)]=val;
        tas[i]=temp;
        i=parent(i);
    }

   
    
}


/*void supprTas(int tas[],int val){
    int i=0;
    while(tas[i]!=parent[indice]){
        i+=1;
    }
    if (tas[i]=='NULL'){
        tas[i-1]='NULL';
        tas[i+1]='NULL';
    }

}*/




void main(){
    taille=9;
    int tas[]={1,2,3,17,19,36,7,25,10};
    int i=0;
    inserTas(tas,taille,4);
    
    //supprTas(tas[9]);
    i=0;
    for(i=0;i<(taille+1);i++){
        printf("%d ",tas[i]);
    }
    printf("\n");
}