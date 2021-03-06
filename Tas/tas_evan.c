#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void initTas(int list[],int tas[],int taille);
void initTas2(int list[],int tas[],int taille);
void verifTas(int tas[],int taille, int i);
void verifTas2(int tas[], int taille,int i);
int parent(int indice);
int droite(int indice);
int gauche(int indice);
void inserTas(int tas[],int taille, int val);
int supprTas(int tas[],int taille);



int main(){
    int i=0;
    int taille=10;
    int tas[taille];
    int liste[]={10,9,8,7,6,5,4,3,2,1,0};
    //int liste[]={1,2,3,17,19,36,7,25,100,5};
    initTas(liste,tas,taille);
    //int tas[taille];
    /*for(int i=0;i<taille;++i){
        tas[i]=liste[i];
    }
    
    */

    for(i=0;i<(taille);i++){
        printf("%d ",tas[i]);
    }
    printf("\n");

    /*inserTas(tas,taille,4);
    for(i=0;i<(taille+1);i++){
        printf("%d ",tas[i]);
    }
    printf("\n");*/

    /*taille=supprTas(tas,taille);
    i=0;
    for(i=0;i<(taille);i++){
        printf("%d ",tas[i]);
    }
    printf("\n");

    */
    return 0;
}

void initTas(int list[],int tas[],int taille){
    int i=0;
    /*for(int i=0;i<taille;++i){
        tas[i]=0;
    }*/
    for(int i=0;i<taille;++i){
        tas[i]=list[i];
        //inserTas(tas,taille,list[i]);
    }
    for (i=taille/2;i>=0;i--){
        verifTas(tas,taille,i);    
    }

}
void initTas2(int list[],int tas[],int taille){
    int i=0;
    for(int i=0;i<taille;++i){
        inserTas(tas,taille,list[i]);
    }
}


void verifTas(int tas[],int taille, int i){
    int temp;
    int em=i;
    int g=gauche(i);
    int d=droite(i);
    if (g<(taille-1)&& tas[g]<tas[i]){
        em=g;
    }
    if (d<(taille-1)&& tas[d]<tas[i]){
        em=d;
    }
    if (em!=i){
        temp=tas[i];
        tas[i]=tas[em];
        tas[em]=temp;
        verifTas(tas,taille,em);

    }
}


void verifTas2(int tas[], int taille,int i){
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
            i=petit;
            verifTas2(tas,taille,0);   
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
    verifTas(tas,taille,0);
    verifTas2(tas,taille,0);
    printf("La valeur supprim??e est %d \n ",temp);
    return taille;

}






