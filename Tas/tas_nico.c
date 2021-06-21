#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void afficherListe(int liste[], int taille);
int parent(int i);
int gauche(int i);
int droite(int i);
void creation(int tas[], int taille);
void verif_tas(int tas[],int taille);
int ajouter(int tas[],int taille, int valeur);
void graphviz(FILE * fic, int tas[], int taille);
void changerValeur(int tas[], int position, int valeur);
int supprimer(int tas[], int taille, int position);
void creation2(int tas[], int taille);

int main(){
    int liste[]={15,5,8,2,13,4,3,11};
    int taille=sizeof(liste)/sizeof(liste[0]);
    int tas[taille];
    FILE *fic = NULL;
    /*
    for(int i=0;i<taille;++i){
        tas[i]=liste[i];
    }*/

    creation2(tas,taille);
    afficherListe(tas,taille);
    taille = ajouter(tas,taille,80);
    changerValeur(tas,3,21);
    taille = supprimer(tas,taille,5);
    afficherListe(tas,taille);

    
    graphviz( fic, tas, taille);

    return 0;
}

/* Retourne la position du parent       */
int parent(int i){
    int s=((i-1)/2);
    return s;
}
/* Retourne la position du fils gauche  */
int gauche(int i){
    return 2*i+1;
}
/* Retourne la position du fils droit   */
int droite(int i){
    return 2*i+2;
}

/* Affiche la liste du tas */
void afficherListe(int liste[], int taille){
    for(int i=0;i<taille;++i){
        printf("%d ",liste[i]);
    }
    printf("\n");
}

/* Creation du tas */
void creation(int tas[], int taille){
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
        }
    }

}

/* Concataine la valeur en fin de liste     */
/* Renvoie la nouvelle taille de la liste   */
int ajouter(int tas[], int taille, int valeur){
    taille++;
    tas[taille-1]=valeur;
    verif_tas(tas,taille);
    return taille;
}

/* Trie apres un ajout         */
/* Pas optimiser               */
/* i=taille/2 ? i->parent(i)   */
void verif_tas(int tas[],int taille){
    int g,d,petit,val;
    for(int i=taille;i>-1;--i){
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
        }
    }
    
}

/* Supprime l'element à une position donnée    */
/* Retourne la nouvelle taille                 */
int supprimer(int tas[], int taille, int position){
    /*for(int i=position;i<taille;++i){
        tas[i]=tas[i+1];
    }*/
    tas[position]=tas[taille-1];
    taille--;
    verif_tas(tas,taille);
    return taille;
}

/* Change laa valeur à une position donnée */
void changerValeur(int tas[], int position, int valeur){
    tas[position]=valeur;
}

/* Crée et afficher le graph */
void graphviz(FILE * fic, int tas[], int taille){
    int g,d;
    fic=fopen("graph_nico.dot","w");
    if(fic!=NULL){
        
        fputs("graph {\n",fic);

        for(int i=0;i<taille;++i){
            g=gauche(i);
            d=droite(i);
            if(g<=taille-1){
                fprintf(fic,"    %d--%d;\n",tas[i],tas[g]);
            }
            if(d<=taille-1){
                fprintf(fic,"    %d--%d;\n",tas[i],tas[d]);
            }         
        }
        fputs("}\n",fic);
        fclose(fic);  
        system("dot -Tjpg graph_nico.dot -o graph_nico.jpg");
    }
}

/* Creation random  */
void creation2(int tas[], int taille){
    srand(time(NULL));
    //srand(10);
    for(int i=0;i<taille;++i){
        tas[i]=rand()%100;
        verif_tas(tas,i);
        afficherListe(tas,i);
    }
}

