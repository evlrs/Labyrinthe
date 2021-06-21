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

/* Enumere les elements de la classe demandee */
void lister_classe(int liste[], int taille, int classe){
    int cpt=0;
    for(int i=0;i<taille;++i){
        if(liste[i]==classe){
            printf("%d ",i);
            cpt++;
        }
    }
    printf("\n");
    if(cpt==0){
        printf("Cette classe est vide !\n");
    }
}

/* Enumere toutes les partitions en fonction de leur classe */
void lister_partition(part *p0, int liste[], int taille){
    init_partition(p0,taille);
    for(int i=0;i<taille;++i){
        elmt* val = (elmt*) malloc(sizeof(elmt));
        val->pos=i;
        val->suivant=p0->base[liste[i]];
        p0->base[liste[i]]=val;
    }
    elmt* ptrCour=NULL;
    for(int i=0;i<taille;++i){
        ptrCour=p0->base[i];
        printf("%d : ",i);
        while(ptrCour!=NULL){
            printf("%d ",ptrCour->pos);
            ptrCour=ptrCour->suivant;
        }
        
        printf("\n");
    }
}

/* Initialisation de structure */
void init_partition(part *p0, int taille){
    if(p0==NULL){
        printf("Erreur structure ...\n");
    }else{
        p0->taille=taille;
        p0->base = (elmt**) malloc(taille*sizeof(elmt*));
    }
}



/* Crée et afficher le graph */
void graphviz(FILE * fic, int tas[], int taille){
    int g,d;
    fic=fopen("graph_partition_nico.dot","w");
    if(fic!=NULL){
        
        fputs("graph {\n",fic);

        for(int i=0;i<taille;++i){
            fprintf(fic,"    %d--%d;\n",tas[i],i);
        }
        fputs("}\n",fic);
        fclose(fic);  
        system("dot -Tjpg graph_partition_nico.dot -o graph_partition_nico.jpg");
        system("sleep 1");
    }
}