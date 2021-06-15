#include <stdio.h>

#define LONGUEUR 12
#define LARGEUR 8

void initTableau(int tab[LARGEUR][LONGUEUR]);                
void afficheTableau(int tab[LARGEUR][LONGUEUR]);             
void copieTableau(int tab1[LARGEUR][LONGUEUR], int tab2[LARGEUR][LONGUEUR]);
int voisinsVivants(int tab[LARGEUR][LONGUEUR],int i, int j); 
int etatCellule(int tab[LARGEUR][LONGUEUR], int i, int j);
int etatFuturCellule(int tab[LARGEUR][LONGUEUR], int i, int j);

int main(){

    int grille1[LARGEUR][LONGUEUR];
    int grille2[LARGEUR][LONGUEUR];
    int i,j,k;

    initTableau(grille1);
    initTableau(grille2);
    grille1[1][0]=1;
    grille1[2][1]=1;
    grille1[2][2]=1;
    grille1[1][2]=1;
    grille1[0][2]=1;
    afficheTableau(grille1);
    //printf("%d\n",voisinsVivant(grille1,5,5));
    //printf("%d\n",grille1[LARGEUR-1][0]);
    //printf("%d\n",voisinsVivants(grille1,LARGEUR-1,0));
    //printf("%d\n",etatFuturCellule(grille1,LARGEUR-1,0));
  
    for(k=0;k<10;++k){
        for(i=0;i<LARGEUR;++i){
            for(j=0;j<LONGUEUR;++j){
                grille2[i][j]=etatFuturCellule(grille1,i,j);
            }
        }
        afficheTableau(grille2);
        copieTableau(grille1,grille2);
    }
    return 0;
}

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
    int etatCell = etatCellule(tab,i,j);       // etat de la cellule  a l instant t
    int etatFutur = etatCell;
    int voisins = voisinsVivants(tab,i,j);  // voisins = nombres de voisins vivant
    if(etatCell==0 && voisins==3){
        etatFutur=1;
    }
    if(etatCell==1){
        if(voisins==3 || voisins==2){
            etatFutur=1;
        }
        else{
            etatFutur=0;
        }
    }
    return etatFutur;
}