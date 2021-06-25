#include "Partition.h"
#include "compC_list.h"

void Init_Partition(int Parti[], int Level[], int taille)
{
   for (int i = 0; i < taille; i++)
   {
      Parti[i] = i;
      Level[i] = 0;
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

void Fusion(int Parti[], int Level[], int X, int Y)
{     

   while (Parti[Y]!=Y)
      Y=Parti[Y];

   while (Parti[X]!=X)
      X=Parti[X];


   if(Level[X]>=Level[Y])
   {
      Parti[Y] = Parti[X];
      if(Level[X]==Level[Y])Level[X]++;
   }
   else
   {  
      Parti[X] = Parti[Y];
      //Level[X]++;
   }

}

void graph_part(int Parti[], int taille)
{

   FILE *file = NULL;

   file = fopen("graph_part.dot", "w");
   if (file != NULL)
   {

      fputs("graph {\n", file);

      for (int i = 0; i < taille; ++i)
      {
         fprintf(file, "\t %d -- %d;\n", i, Parti[i]);
      }
      fputs("}\n", file);
      fclose(file);
      system("dot -Tjpg graph_part.dot -o graph_part.jpg");
   }
}

/*int main()
{
   int taille = 11;
   int Parti[taille];
   int Level[taille];

   Init_Partition(Parti, Level, taille);
   Aff_Partition(Parti, taille);

   Fusion(Parti, Level, 0, 1);
   Fusion(Parti, Level, 2, 3);
   Fusion(Parti, Level, 3, 10);
   Fusion(Parti, Level, 5, 9);
   Fusion(Parti, Level, 4, 6);
   Fusion(Parti, Level, 8, 7);
   Fusion(Parti, Level, 9, 7);
   Fusion(Parti, Level,6,7);
  // Fusion(Parti, Level, 0, 7);
   Aff_Partition(Parti, taille);
   Aff_Partition(Level, taille);
   graph_part(Parti, taille);
   return 0;
}*/