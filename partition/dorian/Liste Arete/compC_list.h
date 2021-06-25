#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Elem
{
   int str;
   int fin;
   int val;
} Elem;

void Init_Aret(Elem *tab, int m);

void aff_liste(Elem *list);

void graph_list(Elem *list);

void Part_creat(int Part[], int Level[], Elem * list);