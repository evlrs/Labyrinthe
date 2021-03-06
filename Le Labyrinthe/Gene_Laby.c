#include "Gene_Laby.h"

void Gene_matrice(int lab[LIGNE][COLONE])
{
    srand(time(NULL));

    int nbAretes;
    triple *aretes;
    triple *chemin;
    aretes = malloc(NAR * sizeof(triple));
    chemin = malloc(NAR * sizeof(triple));

    if (aretes == NULL)
    {
        fprintf(stderr, "allocation error\n");
    }

    nbAretes = init_aretes(aretes);
    if (nbAretes != NAR)
    {
        printf("Initialisation aretes pas bonnes : %d != %d \n", nbAretes, NAR);
    }

    melanger_aretes(aretes);

    int liste[NAR];

    creer(aretes, liste, NAR);
    calcul_composantes(aretes, chemin, liste);

    nombre_murs(chemin, lab);
    //afficher_matrice(lab);

    free(aretes);
    free(chemin);
}

int Init_Dist(int lab[LIGNE][COLONE],int dist[LIGNE][COLONE])
{
    int max=0;
    for(int i=0;i<LIGNE;++i){
        for(int j=0;j<COLONE;++j){
            dist[i][j]=-1;
        }
    }

    max = voisins(lab,dist,0,0,0);
    return max;
}

/* Crée toutes les arretes possible */
int init_aretes(triple *aretes)
{
    int nbAretes = 0;

    for (int j = 0; j < LIGNE; ++j)
    {
        for (int i = 0; i < COLONE; ++i)
        {
            if (j < (LIGNE - 1))
            {
                aretes[nbAretes].depart = j * COLONE + i;
                aretes[nbAretes].arrivee = (j + 1) * COLONE + i;
                aretes[nbAretes].val = nbAretes;
                nbAretes++;
            }
            if (i < (COLONE - 1))
            {
                aretes[nbAretes].depart = j * COLONE + i;
                aretes[nbAretes].arrivee = j * COLONE + i + 1;
                aretes[nbAretes].val = nbAretes;
                nbAretes++;
            }
        }
    }

    return nbAretes;
}

/* Mélange les aretes */
void melanger_aretes(triple *aretes)
{
    //int x = 0;
    int k = 0;
    triple tmp = {0};
    for (int i = 0; i < (NAR - 1); ++i)
    {
        k = i + rand() % (NAR - i);

        tmp = aretes[i];
        aretes[i] = aretes[k];
        aretes[k] = tmp;
    }
}

/* Calcule des composantes connexes */
void calcul_composantes(triple *aretes, triple *chemin, int liste[])
{
    int nbChe = 0;
    int d = 0, a = 0, v = 0;

    for (int j = 0; j < NAR; ++j)
    {
        d = aretes[j].depart;
        a = aretes[j].arrivee;
        v = aretes[j].val;
        if (liste[d] != liste[a])
        {
            fusion(liste, d, liste[a]);
            chemin[nbChe].depart = d;
            chemin[nbChe].arrivee = a;
            chemin[nbChe].val = v;
            nbChe++;
            //graphviz_chemin(aretes,nbChe);
        }
    }
}

/* Fusionne pour faire des arbres */
void fusion(int liste[], int i, int val)
{
    for (int k = 0; k < NAR; ++k)
    {
        if (liste[k] == val)
        {
            liste[k] = liste[i];
        }
    }
}

/* Crée une liste la valeur égale à l'indice */
void creer(triple *aretes, int liste[], int taille)
{
    for (int i = 0; i < taille; ++i)
    {
        liste[i] = aretes[i].val;
    }
}

/* Calcul quel murs sont autour du noeud */
void nombre_murs(triple *chemin, int lab[LIGNE][COLONE])
{
    int d = 0, a = 0;
    int mur = 15;
    for (int i = 0; i < COLONE * LIGNE; ++i)
    {
        mur = 15;
        for (int j = 0; j < NAR; ++j)
        {
            d = chemin[j].depart;
            a = chemin[j].arrivee;
            if (d == i)
            {
                if (a == d + 1)
                    mur -= 2;
                if (a == d - 1)
                    mur -= 8;
                if (a == d + COLONE)
                    mur -= 4;
                if (a == d - COLONE)
                    mur -= 1;
            }
            if (a == i)
            {
                if (d == a + 1)
                    mur -= 2;
                if (d == a - 1)
                    mur -= 8;
                if (d == a + COLONE)
                    mur -= 4;
                if (d == a - COLONE)
                    mur -= 1;
            }
            lab[i / COLONE][i % COLONE] = mur;
        }
    }
}

void afficher_matrice(int lab[LIGNE][COLONE])
{
    for (int i = 0; i < LIGNE; i++)
    {
        for (int j = 0; j < COLONE; j++)
        {
            printf("%d ", lab[i][j]);
        }
        printf("\n");
    }
}

/* Retourne les voisins (là où il n'y a pas de mur) */
int voisins(int lab[LIGNE][COLONE], int dist[LIGNE][COLONE], int i, int j, int p){
    int murs=lab[i][j];
    int h=0,d=0,b=0,g=0; //haut droit bas gauche
    int max=p;

    if(dist[i][j]==-1){
        murs=15-murs;
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
        max=p;

        if(h==1)
        {
            int tmp = voisins(lab,dist,i-1,j,p);
            if (tmp>max)
                max=tmp;

        }    
        if(d==1)    
        {
            int tmp = voisins(lab,dist,i,j+1,p);
            if (tmp>max)
                max=tmp;
        }
        if(b==1)
        {
            int tmp = voisins(lab,dist,i+1,j,p);
            if (tmp>max)
                max=tmp;
        }
        if(g==1)
        {    
            int tmp = voisins(lab,dist,i,j-1,p);
            if (tmp>max)
                max=tmp;
        }
        

    }
    return max;
}