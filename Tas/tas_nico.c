#include <stdio.h>
#include <stdlib.h>


void afficherListe(int liste[], int taille);
//void creation(int tas[], int taille);
int parent(int i);
int gauche(int i);
int droite(int i);
void verif_tas(int tas[],int taille);
void ajouer(int tas[], int valeur,int taille);

int main(){
    int liste[]={15,5,8,2,13,4,3,11};
    int taille=sizeof(liste)/sizeof(liste[0]);
    int tas[taille];
    for(int i=0;i<taille;++i){
        tas[i]=liste[i];
    }
    verif_tas(tas,taille);

    return 0;
}

int parent(int i){
    int s=((i-1)/2);
    return s;
}
int gauche(int i){
    return 2*i+1;
}
int droite(int i){
    return 2*i+2;
}

void afficherListe(int liste[], int taille){
    for(int i=0;i<taille;++i){
        printf("%d ",liste[i]);
    }
}
/*
void afficherTas(int tas[], int taille){
    //aza
}*/
/*
void creation(int tas[], int taille){
    int g,d,petit;

    for(int i=0;i<taille;++i){
        g=gauche(i);
        d=droite(i);

        if(g<=taille && tas[g]<tas[i]){
            petit=g;
        }else{
            petit=i;
        }
        if(d<=taille && tas[d]<tas[petit]){
            petit=d;
        }
    }

}*/

void ajouer(int tas[], int valeur,int taille){
    taille++;
    tas[taille]=valeur;
}

void verif_tas(int tas[],int taille){
    int erreur=-1;
    int g,d,petit,val;
    while(erreur<taille){
        erreur=taille;
        for(int i=0;i<taille;++i){
            g=gauche(i);
            d=droite(i);
            
            if(g<=taille-1 && tas[g]<tas[i]){
                petit=g;
            }else{
                petit=i;
            }
            if(d<=taille-1 && tas[d]<tas[petit]){
                petit=d;
            }
            if(petit!=i){
                val=tas[i];
                tas[i]=tas[petit];
                tas[petit]=val;
                erreur--;
            }
             afficherListe(tas,taille);
             printf("\n");
        }
    }
}

void supprimer(){
    //
}

void changerValeur(){
    //
}

void graphviz(FILE * fic, int tas[]){
    int g,d;
    fic=fopen("graph.txt","w");
    if(fichier!=NULL){
        
        fputs("{\n",fic);
        for(int i=0;i<taille;++i){
            g=gauche(i);
            d=droite(i);
            if(g<=taille-1){
                fputs("    %d--%d\n",tas[i],tas[g)],fic);
            }
            
        }
        fputs("{\n",fic);
        fclose(fic);
    }
}