all: buttons.o maze_api.o 2d_maze

buttons.o: buttons.c buttons.h
	gcc -c buttons.c -o buttons.o -lglut -lGLU -lGL -lm

maze_api.o: maze_api.c maze_api.h
	gcc -c maze_api.c -o maze_api.o -lglut -lGLU -lGL -lm

2d_maze: cellular.c buttons.o maze_api.o
	gcc cellular.c buttons.o maze_api.o -o 2d_maze -lglut -lGLU -lGL -lm