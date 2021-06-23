#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct SClas
{
    int val;
    struct SClas *suiv;
} SClas;

void Init_Partition(int Parti[], int taille)
{
    for (int i = 0; i < taille; i++)
    {
        Parti[i] = i;
    }
}

void Aff_Partition(int Parti[], int taille)
{
    printf("Part:");
    for (int i = 0; i < taille; i++)
    {
        printf("%i | ", Parti[i]);
    }
    printf("\n");
}

void Fusion(int Parti[], int taille, int X, int Y)
{
    for (int i = 0; i < taille; i++)
    {
        if (Parti[i] == Parti[Y])
            Parti[i] = Parti[X];
    }
}

SClas *L_Class(int Parti[], int taille, int val)
{

    SClas *tete = malloc(sizeof(SClas));
    SClas *prec = malloc(sizeof(SClas));
    prec = tete;

    for (int i = 0; i < taille; i++)
    {
        if (Parti[i] == val)
        {
            SClas *Class = malloc(sizeof(SClas));
            Class->val = i;
            Class->suiv = prec->suiv;
            prec->suiv = Class;
            prec = Class;
        }
    }
    return tete;
}

void aff_liste(SClas *list)
{
    SClas *courant;       // pointeur de parcour de la liste
    courant = list->suiv; // utilisation element fictif
    while (courant != NULL)
    {
        printf("%d", courant->val);
        courant = courant->suiv; // element suivant
    }
}

void L_partition(int Parti[], int taille)
{
    int val_class = -1;
    for (int i = 0; i < taille; i++)
    {
        if (Parti[i] > val_class)
        {
            val_class = Parti[i];
            SClas *clas = L_Class(Parti, taille, val_class);
            printf("{");
            aff_liste(clas);
            printf("}");
        }
    }
}

int main()
{
    int taille = 11;
    int Parti[taille];

    Init_Partition(Parti, taille);
    Aff_Partition(Parti, taille);
    Fusion(Parti, taille, 0, 1);
    Aff_Partition(Parti, taille);
    Fusion(Parti, taille, 3, 2);
    Aff_Partition(Parti, taille);
    Fusion(Parti, taille, 5, 6);
    Aff_Partition(Parti, taille);
    Fusion(Parti, taille, 6, 7);
    Aff_Partition(Parti, taille);
    Fusion(Parti, taille, 6, 8);
    Aff_Partition(Parti, taille);
    Fusion(Parti, taille, 3, 10);
    Aff_Partition(Parti, taille);
    Fusion(Parti, taille, 5, 4);
    Aff_Partition(Parti, taille);
    Fusion(Parti, taille, 7, 9);
    Aff_Partition(Parti, taille);

    L_partition(Parti, taille);

    return 0;
}