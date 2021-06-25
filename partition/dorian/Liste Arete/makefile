all: compC_list

CC=gcc
OPT= -c -g -Wall -Wextra

compC_list : compC_list.o PartitionArb.o
	$(CC) -o compC_list compC_list.o  PartitionArb.o


PartitionArb.o : PartitionArb.c compC_list.h Partition.h
	$(CC) $(OPT) PartitionArb.c 

compC_list.o : compC_list.c compC_list.h Partition.h
	$(CC) $(OPT) compC_list.c 

clean : 
	rm -rf *.o

rmproper: clean
	rm -f compC_list

