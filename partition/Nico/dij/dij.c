#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void afficher_mat(int tab[3][5]);
void voisins(int lab[3][5], int dist[3][5], int i, int j, int p);

int main(){
    srand(time(NULL));
    int lab[3][5];
    int dist[3][5];
    for(int i=0;i<3;++i){
        for(int j=0;j<5;++j){
            lab[i][j]=rand()%16;
            dist[i][j]=-1;
        }
    }
    afficher_mat(lab);
    afficher_mat(dist);
    voisins(lab,dist,0,0,0);

}

void afficher_mat(int tab[3][5]){
    for(int i=0;i<3;++i){
        for(int j=0;j<5;++j){
            printf("%d ",tab[i][j]);
        }
        printf("\n");
    }
}

/* Retourne les voisins (là où il n'y a pas de mur) */
void voisins(int lab[3][5], int dist[3][5], int i, int j, int p){
    int murs=lab[i][j];
    int h=0,d=0,b=0,g=0; //haut droit bas gauche
    
    afficher_mat(lab);
    afficher_mat(dist);
    
    if(dist[i][j]==-1){
        switch(murs){
            case 0:
                break;
            case 1:
                h=1;
                break;
            case 2:
                d=1;
                break;
            case 3:
                h=1;
                d=1;
                break;
            case 4:
                b=1;
                break;
            case 5:
                h=1;
                b=1;
                break;
            case 6:
                d=1;
                b=1;
                break;
            case 7:
                h=1;
                d=1;
                b=1;
                break;
            case 8:
                g=1;
                break;
            case 9:
                h=1;
                g=1;
                break;
            case 10:
                d=1;
                g=1;
                break;
            case 11:
                h=1;
                d=1;
                g=1;
                break;
            case 12:
                g=1;
                b=1;
                break;
            case 13:
                h=1;
                g=1;
                b=1;
                break;
            case 14:
                g=1;
                b=1;
                d=1;
                break;
            case 15:
                h=1;
                b=1;
                d=1;
                g=1;
                break;
        }
        dist[i][j]=p;
        ++p;
        if(h==1)    voisins(lab,dist,i-1,j,p);
        if(d==1)    voisins(lab,dist,i,j+1,p);
        if(b==1)    voisins(lab,dist,i+1,j,p);
        if(g==1)    voisins(lab,dist,i,j-1,p);
    }

}
