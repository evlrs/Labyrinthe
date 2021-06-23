#include "compC_mat.h"
#include "Matrice.h"
#include "Partition.h"

void graph_matrice(int **matrice,int m)
{

   FILE *file = NULL;
   int     i,j;            // variables incrementations 
   file = fopen("graph_mat.dot", "w");
   if (file != NULL)
   {
      fputs("graph {\n", file);
      for(i=0; i < m; i++)    //parcour de la matrice
      {
         
         for(j = 0; j <=i; j++)
         {
               if(matrice[i][j]==1)
                  fprintf(file, "\t %d -- %d;\n", i, j); 
         }
      }
      fputs("}\n", file);
      fclose(file);
      system("dot -Tjpg graph_mat.dot -o graph_mat.jpg");
   }
}

void Part_creat(int Part[],int Level[],int ** matrice,int m)
{
   int i,j;

   for(i=0; i < m; i++)    //parcour de la matrice
      {
         
         for(j = 0; j <=i; j++)
         {
               if(matrice[i][j]==1)
                  Fusion(Part,Level,i,j); 
         }
      }
}

int main()
{
   int ** matrice; 
   int taille = 10;
   int Part[taille];
   int Level[taille];

   matrice = gen_matrice(taille);
   
   aff_matrice(matrice,taille);
   graph_matrice(matrice,taille);

   Init_Partition(Part,Level,taille);
   Aff_Partition(Part,taille);

   Part_creat(Part,Level,matrice,taille);
   Aff_Partition(Part,taille);
   graph_part(Part,taille);

   free_matrice(matrice,taille);
   return 0;
}