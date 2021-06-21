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
        while (Tas->tab[i]>Tas->tab[(2*i)]||Tas->tab[i]>Tas->tab[(2*i +1)])
        {
            int tmp = Tas->tab[i];
            if (Tas->tab[(2*i)]<Tas->tab[(2*i+1)])
            {
                Tas->tab[i]=Tas->tab[(2*i)];
                Tas->tab[(2*i)]= tmp;
                i=(2*i);
            }
            else
            {
                Tas->tab[i]=Tas->tab[(2*i+1)];
                Tas->tab[(2*i+1)]= tmp;
                i=(2*i+1);
            }
        }
    }
}

void Aff_Ltas(STas * Tas)
{
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

            TasB->tab = (int *) malloc(MTAILLE*sizeof(int));

            for (int i = 0; i <nb ; i++)
            {
                Add_Noeud(TasB,val[i]);
            }
        }
        else
        {
            free (TasB);
	        TasB=NULL;
        }
   return TasB;

}

void graphviz(FILE * file, STas * Tas){
    int g,d;
    file=fopen("graph_do.txt","w");
    if(file!=NULL){
        
        fputs("graph {\n",file);
        for(int i=0;i<Tas->taille;++i){
            g=gauche(i);
            d=droite(i);
            if(g<=Tas->taille-1){
                fprintf(file,"    %d--%d;\n",Tas->tab[i],Tas->tab[g]);
            }
            if(d<=Tas->taille-1){
                fprintf(file,"    %d--%d;\n",Tas->tab[i],Tas->tab[d]);
            }         
        }
        fputs("}\n",file);
        fclose(file);  
        system("dot -Tjpg graph_do.txt -o graph_do.jpg");
    }
}


int main()
{
    STas * Tas=NULL;

    int list[]={0,4,4,7,9,5,4,8,10,11,12,7,6,5};

    FILE * file=NULL;

    int nb = sizeof(list)/sizeof(int);
    Tas = Init_Tas(list,nb);

    Aff_Ltas(Tas);
    Add_Noeud(Tas,3);
    //Add_Noeud(Tas,2);
    Aff_Ltas(Tas);

    Aug_Noeud(Tas,6,-2);
    Aff_Ltas(Tas);
    
    graphviz(file,Tas);
    

    free(Tas->tab);
    free(Tas);

    return(0);
}