maze_api.o: maze_api.c maze_api.h
	gcc -c maze_api.c -o maze_api.o -lglut -lGLU -lGL -lm
procedural_maze: procedural_maze.c maze_api.o
	gcc procedural_maze.c maze_api.o -o maze -lglut -lGLU -lGL -lm	