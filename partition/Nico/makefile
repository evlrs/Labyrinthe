CC=gcc 
OPT= -c -g -Wall -Wextra
main_part_nico : main_part_nico.o partition_nico.o 
	$(CC) -o main_part_nico main_part_nico.o partition_nico.o
partition_nico.o : partition_nico.c partition_nico.h
	$(CC) $(OPT) partition_nico.c 
main_part_nico.o : main_part_nico.c 
	$(CC) $(OPT) main_part_nico.c
clear : 
	rm partition_nico.o main_part_nico.o
proper : 
	rm main_part_nico
	