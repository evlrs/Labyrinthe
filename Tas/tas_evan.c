#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void initTas(int list[],int taille);
void verifTas(int tas[], int taille);
int parent(int indice);
int droite(int indice);
int gauche(int indice);
void inserTas(int tas[],int taille, int val);
int supprTas(int tas[],int taille);

void initTas(int list[],int taille){
    int i=0;
    int tas[taille];
    /*for(int i=0;i<taille;++i){
        tas[i]=0;
    }*/
    for(int i=0;i<taille;++i){
        tas[i]
        //inserTas(tas,taille,list[i]);
    }

    
}

/* floor*/

void verifTas(int tas[],int taille, int i){
    int temp;
    int em=i;
    int g=gauche[i];
    int d=droite[i];
    if (g<(taille-1)&& tas[g]<tas[i]){
        i=g;
    }
    if (d<(taille-1)&& tas[d]<tas[i]){
        i=d;
    }
    if (em!=i){
        temp=tas[i];
        tas[i]=tas[em];
        tas[em]=temp;
        verifTas(tas,taille,em);

    }



}


void verifTas2(int tas[], int taille){
    int i=0;
    int temp;
    int petit;
    int g;
    int d;
    while((tas[i]>tas[gauche(i)]||tas[i]>tas[droite(i)])&&(droite(i)<(taille-1))){
        
        g=gauche(i);
        d=droite(i);
        petit=i;
        if (tas[i]>=tas[g] && gauche(i)<(taille-1)){
            petit=g;         
        }
        if (tas[petit]>tas[d] && droite(i)<(taille-1) ){
            petit=d;
        }
        if (petit!=i){
            temp=tas[i];
            tas[i]=tas[petit];
            tas[petit]=temp;
            i=petit;   // ici il y a l'implémentation
        }
    }
}


int parent(int indice){
    return (indice-1)/2;
}


int gauche(int indice){
    return 2*indice+1;
}

int droite(int indice){
    return  2*indice+2;
}



void inserTas(int tas[],int taille, int val){
    taille+=1;
    int i=taille-1;
    int temp=0;
    tas[i]=val;
    
    while(tas[i]<tas[parent(i)]){
        
        temp=tas[parent(i)];
        tas[parent(i)]=tas[i];
        tas[i]=temp;
        i=parent(i);

    }
    
}

/*on supprime la racine (la valeur en position 0)*/

int supprTas(int tas[],int taille){
    int temp=tas[0];
    tas[0]=tas[taille-1];
    //tas[taille-1]=temp;
    taille=taille-1; 
    verifTas(tas,taille);
    printf("La valeur supprimée est %d \n ",temp);
    return taille;

}






int main(){
    int taille=9;
    int i;
    int tas[taille];
    //int liste[]={0,1,2,3,4,5,6,7,8,9};
    //initTas(liste,taille);
    int liste[]={1,2,3,17,19,36,7,25,100};
    //int i=0;
    //int tas[taille];
    for(int i=0;i<taille;++i){
        tas[i]=liste[i];
    }
    


    for(i=0;i<(taille);i++){
        printf("%d ",tas[i]);
    }
    printf("\n");

    inserTas(tas,taille,4);
    for(i=0;i<(taille);i++){
        printf("%d ",tas[i]);
    }
    printf("\n");

    taille=supprTas(tas,taille);
    i=0;
    for(i=0;i<(taille);i++){
        printf("%d ",tas[i]);
    }
    printf("\n");


    return 0;
}