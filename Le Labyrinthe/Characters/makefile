all = character
CC=gcc
OPT= -c -g -Wall -Wextra
SDLOP = -lSDL2 -lSDL2_image -lSDL2_ttf


character : character.o
	$(CC) -o character character.o $(SDLOP)

character.o : character.c character.h
	$(CC) $(OPT) character.c


#Labyrinthe : Labyrinthe.o Gene_Laby.o
#	$(CC) -o Labyrinthe Labyrinthe.o Gene_Laby.o $(SDLOP)

#Gene_Laby.o : Gene_Laby.c Gene_Laby.h Labyrinthe.h
#	$(CC) $(OPT) Gene_Laby.c

#Labyrinthe.o : Labyrinthe.c Labyrinthe.h Gene_Laby.h
#	$(CC) $(OPT) Labyrinthe.c

clean :
	rm -rf *.o

rmproper: clean
	rm -f character

