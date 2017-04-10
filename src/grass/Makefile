grass_api.o: grass_api.c grass_api.h
	gcc -c grass_api.c -o grass_api.o -lglut -lGLU -lGL -lm
procedural_grass: procedural_grass.c grass_api.o
	gcc procedural_grass.c grass_api.o -o grass -lglut -lGLU -lGL -lm	