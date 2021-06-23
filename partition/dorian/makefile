all: composantC

CC=gcc
OPT= -c -g -Wall -Wextra

composantC : composantC.o Matrice.o 
	$(CC) -o composantC.o Matrice.o

Matrice.o : Matrice.c Matrice.h
	$(CC) $(OPT) Matrice.c 

composantC.o : composantC.c Matrice.h
	$(CC) $(OPT) composantC.c 

clean : 
	rm -rf *.o

rmproper: clean
	rm -f composantC

