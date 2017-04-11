grass_api.o: grass_api.c grass_api.h
	gcc -c grass_api.c -o grass_api.o -lglut -lGLU -lGL -lm
list.o: list.c list.h
	gcc -c list.c -o list.o
procedural_grass: procedural_grass.c grass_api.o list.o
	gcc procedural_grass.c grass_api.o list.o -o grass -lglut -lGLU -lGL -lm	