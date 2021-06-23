#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Elem
{
   int str;
   int fin;
   int val;
}Elem;

void Init_Aret(Elem * tab,int m)
{
   int i,j;
   int b=0;
   srand(time(NULL));

      for(i=0;i<m;i++)
         {
            for(j=0;j<i;j++)
            {
                  if(rand()%3==1)
                  { 
                     tab[b].str=i;
                     tab[b].fin=j;
                     tab[b].val=1;
                    
                     //printf("isok%d\n",b);
                     //printf("debut:%d fin:%d valeur:%d\n",tab[b].str,tab[b].fin,tab[b].val);
                     b++;
                  }  
            }
         }
}

void aff_liste(Elem * list)
{
   int i=0;
    while (list[i].str != 0)
    {
        printf("%d %d %d|",list[i].str,list[i].fin,list[i].val);
        i++;
        printf("\n");
    }
    printf("\n");
}

void graph_list(Elem * list)
{

   FILE *file = NULL;
   int     i=0;            // variables incrementations 
   file = fopen("graph_list.dot", "w");
   if (file != NULL)
   {
      fputs("graph {\n", file);
    while (list[i].str != 0)
    {
      fprintf(file, "\t %d -- %d [label = %d];\n",list[i].str,list[i].fin,list[i].val);
       i++;
    }
      fputs("}\n", file);
      fclose(file);
      system("dot -Tjpg graph_list.dot -o graph_list.jpg");
   }
}

int main()
{
   int taille = 10;

  // int Part[taille];
   //int Level[taille];

   Elem * Aret;
   
   Aret = malloc((taille*(taille-1)/2)*sizeof(Elem));

   Init_Aret(Aret, taille);

   aff_liste(Aret);

   graph_list(Aret);

   free(Aret);

   
   return 0;
}