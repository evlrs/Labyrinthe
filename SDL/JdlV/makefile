CC=gcc 
OPT= -c -g -lSDL2 -Wall -Wextra  
JdlV_main : JdlV_main.o JdlV_text.o JdlV_graphique.o
	$(CC) -o JdlV_main JdlV_main.o JdlV_text.o JdlV_graphique.o -lSDL2 
JdlV_text.o : JdlV_text.c JdlV_text.h
	$(CC) $(OPT) JdlV_text.c
JdlV_graphique.o : JdlV_graphique.c JdlV_graphique.h
	$(CC) $(OPT) JdlV_graphique.c
JdlV_main.o : JdlV_main.c
	$(CC) $(OPT) JdlV_main.c
clear : rm
	JdlV_main.o JdlV_text.o JdlV_graphique.o
propr : clear
	rm JdlV_main