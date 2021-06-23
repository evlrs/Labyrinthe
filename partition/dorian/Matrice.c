#include "Matrice.h"

/* -------------------------------------------------------------------- */
/* aff_matrice       fonction d'affciahge d'une matrice                 */
/*                                                                      */
/* En entrée: matrice, m:nb ligne , n:nb colonne                        */
/* -------------------------------------------------------------------- */
void aff_matrice(int ** matrice, int m, int n)
{
    int     i,j;            // variables incrementations 

    for(i=0; i < m; i++)    //parcour de la matrice
    {
        for(j = 0; j < n; j++)
        {
            printf("%d ",matrice[i][j]); 
        }
        printf("\n");
    }

}

/* -------------------------------------------------------------------- */
/* gen_matrice          fonction de creation d'une matrice              */
/*                                                                      */
/* En entrée: fichier, m:nb ligne , n:nb colonne                        */
/*                                                                      */                          
/* En sortie: la matrice                                                */
/* -------------------------------------------------------------------- */
int ** gen_matrice(int m,int n) 
{
    int     i,j;        // variables incrementations 
    int     val;        // variable valeur du fichier 
    int     ** matrice; 

    matrice = (int **) malloc(m*sizeof(int *));
    
    for(i=0;i<m;i++)
    {
    	matrice[i] = (int *) malloc(n*sizeof(int));
        for(j=0;j<n;j++)
        {
            matrice[i][j]=0;          
        }
    }

    return matrice;
}

/* ---------------------------------------------------------------------- */
/* libere_matrice        fonction de liberation memoire d'une matrice     */
/*                                                                        */
/* En entrée: matrice, m:nb ligne , n:nb colonne                          */
/* ---------------------------------------------------------------------- */
void free_matrice(int **matrice,int m)
{
    int     i; // variable incrementation

    for(i=0;i<m;i++)
    {
        free(matrice[i]);
    }
    free(matrice);
}