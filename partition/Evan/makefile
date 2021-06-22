CC=gcc 
OPT= -c -g -Wall -Wextra
main : main.o partition.o 
	$(CC) -o main main.o partition.o
partition.o : partition.c partition.h
	$(CC) $(OPT) partition.c 
main.o : main.c 
	$(CC) $(OPT) main.c
clear : 
	rm partition.o main.o
proper : 
	rm main