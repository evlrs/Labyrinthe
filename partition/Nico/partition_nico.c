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

/* Fusionne pour faire des arbres */
void fusion(int liste[], int racine[], int hauteur[], int taille, int k, int j){

    int hk=haut(liste,hauteur,k);
    int hj=haut(liste,hauteur,j);
    int rk=racine[k];
    int rj=racine[j];

    if(hk<hj){
        liste[rk]=rj;
        changRacine(racine,taille,racine[k],racine[j]);
        hauteur[k]=0;   
    }
    if(hk>hj){
        liste[racine[j]]=racine[k];
        changRacine(racine,taille,racine[j],racine[k]);
        hauteur[rj]=0;
    }
    if(hk==hj){
        liste[racine[j]]=racine[k];
        changRacine(racine,taille,racine[j],racine[k]);
        hauteur[rj]=0;
        hauteur[rk]++;        
    }
    
}

/* Enumere les elements de la classe demandee */
void lister_classe(int liste[], int taille, int classe){
    int cpt=0;
    printf("\nLa classe de %d est : ",classe);
    for(int i=0;i<taille;++i){
        if(liste[i]==classe){
            printf("%d ",i);
            cpt++;
        }
    }
    if(cpt==0){
        printf("vide !");
    }
    printf("\n\n");
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

/* Renvoie la mere de k */
int mere(int liste[], int k){
    return liste[k];
}

/* Init tableau grandeur arbre */
void initTabArbre(int hauteur[], int taille){
    for(int i=0;i<taille;++i){
        hauteur[i]=1;
    }
}

/* Retourne la hauteur de l'arbre */
int haut(int liste[], int hauteur[], int i){
    while(liste[i]!=i)  i=liste[i];
    return hauteur[i];
}

/* Retourne le sous arbre le plus grand */
int grandArbre(int liste[], int hauteur[], int a, int b){
    int ha = haut(liste,hauteur,a);
    int hb = haut(liste,hauteur,b);
    int h=a;
    if(ha<hb)    h=b;
    return h;
}

/* Crée et afficher le graph */
void graphviz(FILE* fic, int liste[], int taille){
    fic=fopen("graph_partition_nico.dot","w");
    if(fic!=NULL){
        
        fputs("digraph {\n",fic);

        for(int i=0;i<taille;++i){
            fprintf(fic,"    %d -> %d;\n",i,liste[i]);
        }
        
        fputs("}\n",fic);
        fclose(fic);  
        system("dot -Tjpg graph_partition_nico.dot -o graph_partition_nico.jpg");
        system("sleep 0.5");
    }
}

/* Change la racine de l'arbre */
void changRacine(int racine[], int taille, int ancienne, int nouvelle){
    for(int i=0;i<taille;++i){
        if(racine[i]==ancienne) racine[i]=nouvelle;
    }
}