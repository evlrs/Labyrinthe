all: compC_mat

CC=gcc
OPT= -c -g -Wall -Wextra

compC_mat : compC_mat.o Matrice.o PartitionArb.o
	$(CC) -o compC_mat compC_mat.o Matrice.o PartitionArb.o

Matrice.o : Matrice.c compC_mat.h Matrice.h
	$(CC) $(OPT) Matrice.c 

PartitionArb.o : PartitionArb.c compC_mat.h Partition.h
	$(CC) $(OPT) PartitionArb.c 

compC_mat.o : compC_mat.c compC_mat.h Matrice.h Partition.h
	$(CC) $(OPT) compC_mat.c 

clean : 
	rm -rf *.o

rmproper: clean
	rm -f compC_mat

