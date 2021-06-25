CC=gcc 
OPT= -c -g -Wall -Wextra

dij : dij.o 
	$(CC) -o dij dij.o 
dij.o : dij.c 
	$(CC) $(OPT) dij.c
clear : 
	rm dij.o
proper : 
	rm dij
	