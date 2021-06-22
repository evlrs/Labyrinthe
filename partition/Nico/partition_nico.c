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
void fusion(FILE* fic, int liste[], int taille, int k, int j){
    int valk=liste[k];
    int valj=liste[j];
    int t;
    //fprintf(fic,"    %d -> %d;\n",j,k);
    int cptj=0;
    int cptk=0;

    for(int i=0;i<taille;++i){
        if(liste[i]==valk){
            cptk++;
        }
        if(liste[i]==valj){
            cptj++;
        }
    }

    for(int i=0;i<taille;++i){
        if(liste[i]==valj){
            if(cptk==1){
                if(cptj==1){
                    liste[i]=valk;
                    fprintf(fic,"    %d -> %d;\n",j,k);
                }else{
                    //
                }
            }else{
                if(cptj==1){
                    liste[i]=valk;
                    fprintf(fic,"    %d -> %d;\n",j,k);
                }else{
                    t=i;
                    while(t!=liste[t]){
                        t=liste[t];
                    }                
                    fprintf(fic,"    %d -> %d;\n",t,valk);
                    liste[t]=valk;
                }
            }
        }
        if(liste[i]==valk){
            if(cptk==1){
                if(cptj==1){
                    liste[i]=valk;
                    
                }else{
                    liste[i]=valj;
                    fprintf(fic,"    %d -> %d;\n",k,valj);
                }
            }else{
                if(cptj==1){
                    //liste[i]=valk;
                    //fprintf(fic,"    %d -> %d;\n",j,k);
                }else{
                    t=i;
                    while(t!=liste[t]){
                        t=liste[t];
                    }                
                    //fprintf(fic,"    %d -> %d;\n",valk,t);
                    //liste[i]=valk;
                }
            }
        }
    }
    //afficherListe(liste,taille);
    /*
    for(int i=0;i<taille;++i){
        if(liste[i]==valk){
            if(cptk==1){
                if(cptj!=1){
                    liste[i]=valj;
                    fprintf(fic,"    %d -> %d;\n",k,valj);
                }else{
                    liste[i]=valk;
                }
            }else{
                if(cptj==1){
                    //liste[i]=valk;
                    //fprintf(fic,"    %d -> %d;\n",j,k);
                }else{
                    t=i;
                    while(t!=liste[t]){
                        t=liste[t];
                    }                
                    //fprintf(fic,"    %d -> %d;\n",valk,t);
                    //liste[i]=valk;
                }
            }
        }
    }*/
    afficherListe(liste,taille);
    printf("\n");
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

/* Retourne le sous arbre le plus grand */
void grandArbre(int liste[], int taille, int a, int b){
    int i=0;
    while(i){
        
    }
}

/* Crée et afficher le graph */
void graphviz(FILE* fic, int liste[], int taille){
    //fic=fopen("graph_partition_nico.dot","w");
    if(fic!=NULL){
        
        //fputs("digraph {\n",fic);

        for(int i=0;i<taille;++i){
            if(i==liste[i])  fprintf(fic,"    %d -> %d;\n",i,i);
        }
        /*
        fputs("}\n",fic);
        fclose(fic);  
        system("dot -Tjpg graph_partition_nico.dot -o graph_partition_nico.jpg");
        system("sleep 0.5");*/
    }
}