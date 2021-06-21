#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



#define MTAILLE 30

typedef struct Do_Tas
{
    int taille;
    int * tab;
}STas;


void Mise_Tas(STas * Tas,int i)
{
    int g=2*i+1;
    int d=2*i+2;
    int Em = i;

    if (g<Tas->taille && Tas->tab[g]<Tas->tab[Em])
        Em=g;
    if (d<Tas->taille && Tas->tab[d]<Tas->tab[Em])
        Em=d;
    if (Em!=i)
    {
        int tmp = Tas->tab[i];
        Tas->tab[i]=Tas->tab[Em];
        Tas->tab[Em] = tmp;
        Mise_Tas(Tas,Em);
    }
    
}

void Add_Noeud(STas * Tas, int X)
{
    int i= Tas->taille;

    while (Tas->tab[((i-1)/2)]>X)
    {
        Tas->tab[i]=Tas->tab[((i-1)/2)];
        i=((i-1)/2);
    }
    Tas->tab[i]=X;
    Tas->taille++;
}

void Aff_Ltas(STas * Tas)
{
    printf("TAS:");
    for (int i = 0; i < Tas->taille; i++)
    {
        printf("%i | ",Tas->tab[i]);
    }
    printf("\n");
}

STas * Init_Tas(int val[],int nb)
{
    STas * TasB=NULL;
    
    TasB = (STas *) malloc(sizeof(STas));
        if ( TasB != NULL )    
        {
            TasB->taille = 0;

            TasB->tab = (int *) malloc(nb*sizeof(int));

            for (int i = 0; i <nb ; i++)
            {
                TasB->tab[i]=val[i];
                TasB->taille++;
            }
            for (int i = TasB->taille/2; i>=0 ; i--)
            {
                //Aff_Ltas(TasB);
                Mise_Tas(TasB,i);    
            }
        }
        else
        {
            free (TasB);
	        TasB=NULL;
        }
   return TasB;

}

void Aug_Noeud(STas *Tas, int pos, int add)
{
    Tas->tab[pos]+=add;
    int i = pos;


    if (add<0)
    {   
        while (Tas->tab[i]<Tas->tab[(i-1)/2])
        {
            int tmp = Tas->tab[i];
            Tas->tab[i]=Tas->tab[((i-1)/2)];
            Tas->tab[((i-1)/2)] = tmp;
            i=((i-1)/2);
        }
    }
    else
    {
        while (Tas->tab[i]>Tas->tab[(2*i+1)]||Tas->tab[i]>Tas->tab[(2*i +2)])
        {
            int tmp = Tas->tab[i];
            if (Tas->tab[(2*i+1)]<Tas->tab[(2*i+2)])
            {
                Tas->tab[i]=Tas->tab[(2*i+1)];
                Tas->tab[(2*i+1)]= tmp;
                i=(2*i+1);
            }
            else
            {
                Tas->tab[i]=Tas->tab[(2*i+2)];
                Tas->tab[(2*i+2)]= tmp;
                i=(2*i+2);
            }
        }
    }
}

void graphviz(FILE * file, STas * Tas){
    int g,d;
    file=fopen("graph_do.dot","w");
    if(file!=NULL){
        
        fputs("graph {\n",file);

        for(int i=0;i<Tas->taille;++i)
        {
            g=2*i+1;
            d=2*i+2;

            if(g<=Tas->taille-1)
                fprintf(file,"\t%d.%d -- %d.%d;\n",i,Tas->tab[i],g,Tas->tab[g]);
            if(d<=Tas->taille-1)
                fprintf(file,"\t%d.%d -- %d.%d;\n",i,Tas->tab[i], d, Tas->tab[d]);
        }
        fputs("}\n",file);
        fclose(file);  
        system("dot -Tjpg graph_do.dot -o graph_do.jpg");
    }
}

int Supp_Noeud(STas * Tas)
{
    int tmp=Tas->tab[0];
    Tas->tab[0]=Tas->tab[Tas->taille-1];
    Tas->taille--;
    Mise_Tas(Tas,0);
    return tmp;
}


int main()
{
    STas * Tas=NULL;

    int list[]={10,9,8,7,6,5,4,3,2,1,0};
    
    FILE * file=NULL;

    int nb = sizeof(list)/sizeof(int);
    
    printf("LIST:");
    for (int i = 0; i < nb; i++)
        printf("%i | ",list[i]);

    printf("\n");

    Tas = Init_Tas(list,nb);

    graphviz(file,Tas);
  
    Aff_Ltas(Tas);
    //Add_Noeud(Tas,3);
    //Aff_Ltas(Tas);
    //Aug_Noeud(Tas,6,-2);
    //Aff_Ltas(Tas);


    for (int i = 0; i < nb; i++)
    {
        list[i]=Supp_Noeud(Tas);
        //Aff_Ltas(Tas);    
    }
    printf("LIST:");
    for (int i = 0; i < nb; i++)
    {
        printf("%i | ",list[i]);
    }
    printf("\n");
    //Aff_Ltas(Tas);

    //graphviz(file,Tas);


    free(Tas->tab);
    free(Tas);

    return(0);
}