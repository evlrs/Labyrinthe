#include "partition_nico.h"


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

/* Retourne la classe de l'element en position i    */
/* Retourne -1 si la position n'existe pas          */
int recuperer_classe(int liste[], int taille, int i){
    int val=-1;
    if(i<taille) val=liste[i];
    return val;
}

/* Toute la classe de j entre dans la classe de k */
void fusion(int liste[], int taille, int k, int j){
    int val1=liste[k];
    int val2=liste[j];
    for(int i=0;i<taille;++i){
        if(liste[i]==val2) liste[i]=val1;
    }
}

/*
void lister_classe(int liste[], int taille){
    for(int i=0;i<taille;++i){

    }
}*/

void lister_partition(){

}

void init_partition(part *p0, int taille){
    if(p0==NULL){
        printf("Erreur structure ...\n");
    }else{
        p0->
    }
}