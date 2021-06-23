all: composantC

CC=gcc
OPT= -c -g -Wall -Wextra

composantC : composantC.o Matrice.o PartitionArb.o
	$(CC) -o composantC composantC.o Matrice.o PartitionArb.o

Matrice.o : Matrice.c composantC.h Matrice.h
	$(CC) $(OPT) Matrice.c 

PartitionArb.o : PartitionArb.c composantC.h Partition.h
	$(CC) $(OPT) PartitionArb.c 

composantC.o : composantC.c composantC.h Matrice.h Partition.h
	$(CC) $(OPT) composantC.c 

clean : 
	rm -rf *.o

rmproper: clean
	rm -f composantC

