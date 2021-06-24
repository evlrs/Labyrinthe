#include "kru.h"



int main(){
    srand(time(NULL));
    
    int nbAretes;
    triple* aretes;
    triple* chemin;
    aretes= malloc(NAR*sizeof(triple));
    chemin= malloc(NAR*sizeof(triple));
    if(aretes == NULL) {
        fprintf(stderr, "allocation error\n");
        return 1;
    }

    nbAretes=init_aretes(aretes);
    if(nbAretes!=NAR){
        printf("Initialisation aretes pas bonnes : %d != %d \n",nbAretes,NAR);
    }

    //graphviz(aretes,NAR);
    melanger_aretes(aretes);
    //graphviz(aretes,NAR);
    
    int liste[NAR];
    int nbChe;
    int lab[H][L];
    creer(aretes,liste,NAR);
    nbChe=calcul_composantes(aretes,chemin,liste);
    //graphviz_chemin(chemin,nbChe);

    nombre_murs(chemin,lab);
    //afficher_matrice(lab);
    
    /* SDL */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      
        exit(EXIT_FAILURE);
    }

    SDL_Window *win = NULL;
    win = SDL_CreateWindow("Fenêtre", 0, 0, L*D, H*D, 0);

    if (win == NULL) {
        SDL_Log("Error : SDL window creation - %s\n", SDL_GetError());   
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    
    /* initialisation renderer */
    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == 0) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    }

    SDL_Texture *my_texture = NULL; 
    my_texture = IMG_LoadTexture(renderer,"./mur.png");

    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0}, state = {0}; 
    SDL_GetWindowSize(win, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);

 

    int n=0;
    int offset_x = source.w/4, offset_y = source.h/4; 
    int zoom=1;
    state.w = offset_x; 
    state.h = offset_y;
    destination.w = window_dimensions.w/L*zoom;
    destination.h = window_dimensions.h/H*zoom;
    destination.x = 0;
    destination.y = 0;
    state.x = 0;
    state.y = 0;
  

    SDL_bool program_on = SDL_TRUE;
    while (program_on) {                                     // La boucle des évènements
        SDL_Event event;                                     // Evènement à traiter

        while (program_on && SDL_PollEvent(&event)) {       // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas                                                     
                                                            // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type) {                           // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:                                  // Un évènement simple, on a cliqué sur la x de la // fenêtre
                program_on = SDL_FALSE;                     // Il est temps d'arrêter le programme
                break;

            case SDL_KEYDOWN:                               // Le type de event est : une touche appuyée
                                                            // comme la valeur du type est SDL_Keydown, dans la pratie 'union' de
                                                            // l'event, plusieurs champs deviennent pertinents   
                switch (event.key.keysym.sym) {             // la touche appuyée est ...
                case SDLK_ESCAPE:                           // 'ESCAPE'  
                case SDLK_q:                                // 'q'
                    program_on = SDL_FALSE;                 // 'escape' ou 'q', d'autres façons de quitter le programme                                     
                    break;
                default:                                    // Une touche appuyée qu'on ne traite pas
                    break;
                }
                break;
            default:                                        // Les évènements qu'on n'a pas envisagé
                break;
            }
        }
        
        for(int k=0;k<L*H;++k){

            n=lab[k/L][k%L];
            destination.x = destination.w*(k%L);
            destination.y = destination.h*(k/L);    
            state.x = offset_x*(numero_sprite(n)%4);
            state.y = offset_y*(numero_sprite(n)/4);
            SDL_RenderCopy(renderer, my_texture, &state, &destination); 
        
        }

        SDL_RenderPresent(renderer);       
        SDL_Delay(100);                     
        SDL_RenderClear(renderer);
    }
    
    SDL_DestroyTexture(my_texture);
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();  
    SDL_Quit(); 
    free(aretes);
    free(chemin);
}

/* Crée toutes les arretes possible */
int init_aretes(triple* aretes){
    int nbAretes=0;

    for(int j=0;j<H;++j){
        for(int i=0;i<L;++i){
            if(j<(H-1)){
                aretes[nbAretes].depart=j*L+i;
                aretes[nbAretes].arrivee=(j+1)*L+i;
                aretes[nbAretes].val=nbAretes;
                nbAretes++;
            }
            if(i<(L-1)){
                aretes[nbAretes].depart=j*L+i;
                aretes[nbAretes].arrivee=j*L+i+1;
                aretes[nbAretes].val=nbAretes;
                nbAretes++;
            }
        }
    }
    
    return nbAretes;
}

/* Affiche les arretes sur le terminal */
void afficher_aretes(triple* aretes){
    int d,a,nb,k;
    for(int i=0;i<NAR;++i){
        k=aretes[i].val;
        nb=aretes[k].val;
        d=aretes[k].depart;
        a=aretes[k].arrivee;
        printf("%d : %d -- %d\n",nb,d,a);
    }
    
}

/* Crée l'image du graph de toutes les aretes */
void graphviz(triple* aretes, int taille){
    int d,a,v;
    FILE * fic = NULL;
    
    fic=fopen("kru_nico.dot","w");

    if(fic!=NULL){
        
        fputs("graph {\n",fic);
        for(int i=0;i<taille;++i){
            
            d=aretes[i].depart;
            a=aretes[i].arrivee;
            v=aretes[i].val;
            fprintf(fic,"    %d -- %d [label= %d];\n",d,a,v);
        }
        
        fputs("}\n",fic);
        fclose(fic);  
        system("dot -Tjpg kru_nico.dot -o kru_nico.jpg");
        //system("sleep 1");
    }
}

/* Crée l'image du graph des chemins possible */
void graphviz_chemin(triple* aretes, int taille){
    int d,a,v;
    FILE * fic = NULL;
    
    fic=fopen("chemin_nico.dot","w");

    if(fic!=NULL){
        
        fputs("graph {\n",fic);
        for(int i=0;i<taille;++i){
            
            d=aretes[i].depart;
            a=aretes[i].arrivee;
            v=aretes[i].val;
            fprintf(fic,"    %d -- %d [label= %d];\n",d,a,v);
        }
        
        fputs("}\n",fic);
        fclose(fic);  
        system("dot -Tjpg chemin_nico.dot -o chemin_nico.jpg");
        //system("sleep 0.1");
    }
}

/* Mélange les aretes */
void melanger_aretes(triple* aretes){
    int x;
    int k;
    for(int i=0;i<(NAR-1);++i){
        k=i+rand()%(NAR-i);

        x=aretes[i].val;
        aretes[i].val=aretes[k].val;
        aretes[k].val=x;
    }
}

/* Calcule des composantes connexes */
int calcul_composantes(triple* aretes, triple* chemin, int liste[]){
    int nbChe=0;
    int d,a,v,j;
    for(int i=0;i<NAR;++i){
        j=0;
        while(aretes[j].val!=i){
            ++j;
        }
        d=aretes[j].depart;
        a=aretes[j].arrivee;
        v=aretes[j].val;
        if(liste[d]!=liste[a]){
            fusion(liste,d,liste[a]); 
            chemin[nbChe].depart=d;
            chemin[nbChe].arrivee=a;
            chemin[nbChe].val=v;
            nbChe++;
            //graphviz_chemin(aretes,nbChe);
        } 
    }
    return nbChe;
}

/* Fusionne pour faire des arbres */
void fusion(int liste[], int i, int val){

    for(int k=0;k<NAR;++k){
        if(liste[k]==val){
            liste[k]=liste[i];
        }
    }
}

/* Affiche la liste de la liste*/
void afficherListe(int liste[], int taille){
    for(int i=0;i<taille;++i){
        printf("%d ",liste[i]);
    }
    printf("\n");
}

/* Crée une liste la valeur égale à l'indice */
void creer(triple* aretes ,int liste[], int taille){
    for(int i=0;i<taille;++i){
        liste[i]=aretes[i].val;
    }
}

void init_poids(triple* aretes, int poids[], int taille){
    for(int i=0;i<taille;++i){
        poids[i]=aretes[i].val;
    }
}

/* Donne le numero du sprite en fonction du nombre de murs */
int numero_sprite(int murs){
    int sprite=-1;
    switch(murs){
        case 0:
            sprite=14;
            break;
        case 1:
            sprite=5;
            break;
        case 2:
            sprite=6;
            break;
        case 3:
            sprite=2;
            break;
        case 4:
            sprite=7;
            break;
        case 5:
            sprite=12;
            break;
        case 6:
            sprite=3;
            break;
        case 7:
            sprite=8;
            break;
        case 8:
            sprite=4;
            break;
        case 9:
            sprite=1;
            break;
        case 10:
            sprite=13;
            break;
        case 11:
            sprite=11;
            break;
        case 12:
            sprite=0;
            break;
        case 13:
            sprite=10;
            break;
        case 14:
            sprite=9;
            break;
        case 15:
            sprite=15;
            break;
    }
    if(sprite==-1)  printf("ERREUR switch sprite\n");
    return sprite;
}

/* Calcul quel murs sont autour du noeud */
void nombre_murs(triple* chemin, int lab[H][L]){
    int d,a;
    int mur;
    for(int i=0;i<L*H;++i){
        mur=15;
        for(int j=0;j<NAR;++j){
            d=chemin[j].depart;
            a=chemin[j].arrivee;
            if(d==i){
                if(a==d+1)   mur-=2;
                if(a==d-1)   mur-=8;
                if(a==d+L)   mur-=4;
                if(a==d-L)   mur-=1;
            }
            if(a==i){
                if(d==a+1)   mur-=2;
                if(d==a-1)   mur-=8;
                if(d==a+L)   mur-=4;
                if(d==a-L)   mur-=1;                
            }
            lab[i/L][i%L]=mur;
        }
    }

}

/* Affiche la matrice des noeuds (avec les murs) */
void afficher_matrice(int lab[H][L]){
    for(int i=0;i<H;i++){
        for(int j=0;j<L;j++){
            printf("%d ",lab[i][j]);
        }
        printf("\n");
    }
}
