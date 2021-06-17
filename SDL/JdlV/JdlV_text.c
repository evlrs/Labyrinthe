#include "JdlV_text.h"


/* remplie la matrice de 0*/
void initTableau(int tab[LARGEUR][LONGUEUR]){
    int i,j;

    for(i=0;i<LARGEUR;++i){
        for(j=0;j<LONGUEUR;++j){
            tab[i][j]=0;
        }
    }
}
/* affiche la matrice */
void afficheTableau(int tab[LARGEUR][LONGUEUR]){
    int i,j;
    
    for(i=0;i<LONGUEUR+1;++i){
        printf("--");
    }
    printf("\n");
    for(i=0;i<LARGEUR;++i){
        printf("| ");
        for(j=0;j<LONGUEUR;++j){
            printf("%d ",tab[i][j]);
        }
        printf("| \n");
    } 
    for(i=0;i<LONGUEUR+1;++i){
        printf("--");
    }   
    printf("\n");
}
/*copie le tableau 2 dans le tableau 1 */
void copieTableau(int tab1[LARGEUR][LONGUEUR], int tab2[LARGEUR][LONGUEUR]){
    int i,j;
    for(i=0;i<LARGEUR;++i){
        for(j=0;j<LONGUEUR;++j){
           tab1[i][j]=tab2[i][j];
        }
    } 
}
/* compte le nombre de voisins vivants */
int voisinsVivants(int tab[LARGEUR][LONGUEUR], int i, int j){
    int somme = tab[(i-1 + LARGEUR)%LARGEUR][(j-1 + LONGUEUR)%LONGUEUR] 
                + tab[(i-1 + LARGEUR)%LARGEUR][(j + LONGUEUR)%LONGUEUR] 
                + tab[(i-1 + LARGEUR)%LARGEUR][(j+1 + LONGUEUR)%LONGUEUR] 
                + tab[(i + LARGEUR)%LARGEUR][(j-1 + LONGUEUR)%LONGUEUR] 
                + tab[(i + LARGEUR)%LARGEUR][(j+1 + LONGUEUR)%LONGUEUR] 
                + tab[(i+1 + LARGEUR)%LARGEUR][(j-1 + LONGUEUR)%LONGUEUR] 
                + tab[(i+1 + LARGEUR)%LARGEUR][(j + LONGUEUR)%LONGUEUR] 
                + tab[(i+1 + LARGEUR)%LARGEUR][(j+1 + LONGUEUR)%LONGUEUR];
    
    
    return somme;
} 
/* retourne 1 si la cellule est vivante et 0 si elle est morte */
int etatCellule(int tab[LARGEUR][LONGUEUR], int i, int j){
    return tab[i][j];
}
/* retourne 1 si la cellule sera vivante et 0 si elle sera morte e l instant t+1*/
int etatFuturCellule(int tab[LARGEUR][LONGUEUR], int i, int j){
    int vivante[]={0,0,1,1,0,0,0,0,0};          // vivante a l instant t
    int morte[]={0,0,0,1,0,0,0,0,0};            // morte a l instant t
    int etatCell = etatCellule(tab,i,j);        // etat de la cellule  a l instant t
    int etatFutur = etatCell;
    int voisins = voisinsVivants(tab,i,j);      // voisins = nombres de voisins vivant
    if(etatCell==0){
        etatFutur=morte[voisins];
    }else{
        etatFutur=vivante[voisins];
    }
    return etatFutur;
}

void InOne(int tab[LARGEUR][LONGUEUR], int i, int j){
    tab[i][j]=1;
}