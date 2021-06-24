CC=gcc
OPT= -c -g -Wall -Wextra
SDLOP = -lSDL2 -lSDL2_image -lSDL2_ttf

Main : kru.o texture_laby.o 
	$(CC) -o main kru.o texture_laby.o $(SDLOP)
kru.o : kru.c kru.h texture_laby.c texture_laby.h
	$(CC) $(OPT) kru.c
texture_laby.o : texture_laby.c texture_laby.h
	$(CC) $(OPT) texture_laby.c

clear : rm
	kru.o texture_laby.o
propr : clear
	rm main