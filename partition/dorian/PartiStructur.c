#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct SClas
{
    int nb_elm;
    int * val;
}SClas;

typedef struct SPart
{
    int taille;
    SClas * Class;
}SPart;

SPart * Init_Partition(int size)
{
    SPart * part = NULL;  

    part = (SPart *) malloc(sizeof(SPart));
    part->taille = size;
    part->Class = (SClas *) malloc(size*sizeof(SClas));        
        for (int i = 0; i < size; i++)
        {
            part->Class[i].nb_elm=1;
            part->Class[i].val=(int *) malloc(size*sizeof(int));
            part->Class[i].val[0]=i;
        }
    return part;
}


void Aff_Partition(SPart * Parti)
{
    printf("Part:");
    for (int i = 0; i < Parti->taille; i++)
    {
         printf("{");
        for (int j = 0; j < Parti->Class[i].nb_elm; j++)
        {
            printf("%i",Parti->Class[i].val[j]);
        }
         printf("}");
    }
    printf("\n");
}
/*
void Fusion(SPart * Parti,int X, int Y)
{
    for (int i = 0; i < Parti->taille;i++)
    {
        if (Parti[i]==Parti[Y])
            Parti[i]=Parti[X];
    }
    
}

int * L_Class(int Parti[],int taille ,int Clas)
{
    int * elm_class;
    int nb=0;

    for (int i = 0; i < taille;i++)
    {
        if (Parti[i]==Clas)
        {
            elm_class[i]=Parti[i];
            nb++;
        }
    }
    return elm_class[nb];
}*/


int main()
{
    int taille =11;
    SPart * Parti=NULL;

    Parti= Init_Partition(taille);
    Aff_Partition(Parti);
    
/*
    Fusion(Parti,taille,0,1);
    Aff_Partition(Parti,taille);
    Fusion(Parti,taille,3,2);
    Aff_Partition(Parti,taille);
    Fusion(Parti,taille,5,6);
    Aff_Partition(Parti,taille);
    Fusion(Parti,taille,6,7);
    Aff_Partition(Parti,taille);
    Fusion(Parti,taille,6,8);
    Aff_Partition(Parti,taille);
    Fusion(Parti,taille,3,10);
    Aff_Partition(Parti,taille);
    Fusion(Parti,taille,5,4);
    Aff_Partition(Parti,taille);
    Fusion(Parti,taille,7,9);

    int clas[]=L_Class(Parti,taille,5);
    int T_clas=sizeof(clas)/sizeof(clas[0]);


    Aff_Partition(Parti,taille);
*/

    return 0;
}