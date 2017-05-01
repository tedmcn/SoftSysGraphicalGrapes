all: buttons.o 2d_maze

buttons.o: buttons.c buttons.h
	gcc -c buttons.c -o buttons.o -lglut -lGLU -lGL -lm

2d_maze: cellular.c buttons.o
	gcc cellular.c buttons.o -o 2d_maze -lglut -lGLU -lGL -lm