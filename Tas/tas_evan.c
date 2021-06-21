#include <stdio.h>
#include <stdlib.h>
#include <math.h>



void verifTas(int tas[], int taille);
int parent(int indice);
int droite(int indice);
int gauche(int indice);
void inserTas(int tas[],int taille, int val);
int supprTas(int tas[],int taille);


int taille=9;

/*void initTas(int list[taille]){
    int tas[taille]={};
    while tas[taille]!=
}*/

/* floor*/


void verifTas(int tas[], int taille){
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
            printf("a");           
        }
        if (tas[petit]>tas[d] && droite(i)<(taille-1) ){
            petit=d;
            printf("b");
        }
        if (petit!=i){
            temp=tas[i];
            tas[i]=tas[petit];
            tas[petit]=temp;
            i=petit;   // ici il y a l'implémentation
        }
    }
        



/*    while((tas[i]>tas[gauche(i)] || tas[i]>tas[droite(i)] && (arret!=0))){  
        printf("a ");
        if (gauche(i)>(taille-1)&&(droite(i)>(taille-1))){
            printf("d");
            arret=0;
        }
        if(tas[gauche(i)]<tas[i]){
            printf("b ");

            for(i=0;i<(taille+1);i++){
            printf("%d ",tas[i]);
            }
            printf("\n ");
            
            temp=tas[gauche(i)];
            tas[gauche(i)]=tas[i];
            tas[i]=temp;
            i=gauche(i);
        }
        if(tas[droite(i)]<tas[i]){
            printf("c");

            for(i=0;i<(taille+1);i++){
            printf("%d ",tas[i]);
            }
            printf("\n ");
            temp=tas[droite(i)];
            tas[droite(i)]=tas[i];
            tas[i]=temp;
            i=droite(i);
        }
    }*/
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
    verifTas(tas,taille);
    taille=taille-1; 
    printf("La valeur supprimée est %d \n ",temp);
    return taille;

}




int main(){
    taille=9;
    int liste[]={1,2,3,17,19,36,7,25,100};
    int i=0;
    int tas[taille];
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