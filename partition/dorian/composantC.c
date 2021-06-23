#include "Matrice.h"

int main()
{
    int ** matrice; 
    int taille = 10;

    matrice = gen_matrice(taille,taille);
   

   free_matrice(matrice,taille);
   return 0;
}