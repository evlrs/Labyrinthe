#include "Partition.h"
#include "compC_list.h"

void Init_Aret(Elem *tab, int m)
{
   int i, j;
   int b = 0;

   for (i = 0; i < m; i++)
   {
      for (j = 0; j < i; j++)
      {
         if (rand() / (float)__INT_MAX__ < 0.09)
         {
            tab[b].str = i;
            tab[b].fin = j;
            tab[b].val = 1;
            b++;
         }
      }
   }
}

void aff_liste(Elem *list)
{
   int i = 0;
   while (list[i].str != 0)
   {
      printf("%d %d %d", list[i].str, list[i].fin, list[i].val);
      i++;
      printf("\n");
   }
}

void graph_list(Elem *list)
{
   FILE *file = NULL;
   int i = 0; // variables incrementations
   file = fopen("graph_list.dot", "w");
   if (file != NULL)
   {
      fputs("graph {\n", file);
      while (list[i].str != 0)
      {
         fprintf(file, "\t %d -- %d [label = %d];\n", list[i].str, list[i].fin, list[i].val);
         i++;
      }
      fputs("}\n", file);
      fclose(file);
      system("dot -Tjpg graph_list.dot -o graph_list.jpg");
   }
}

void Part_creat(int Part[], int Level[], Elem * list)
{
   int i=0;
   while (list[i].str != 0)
      {
         Fusion(Part,Level,list[i].str, list[i].fin);
         i++;
      }
}

int main()
{
   int taille = 15;
   srand(time(NULL));

   int Part[taille];
   int Level[taille];

   Elem *Aret;

   Aret = malloc((taille * (taille - 1) / 2) * sizeof(Elem));

   Init_Aret(Aret, taille);

   aff_liste(Aret);

   graph_list(Aret);

   Init_Partition(Part,Level,taille);

   Part_creat(Part,Level,Aret);

   Aff_Partition(Part, taille);
   
   graph_part(Part, taille);


   free(Aret);

   return 0;
}