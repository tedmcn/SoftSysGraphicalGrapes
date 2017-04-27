all: grass_api.o buttons.o sliders.o list.o procedural_grass


grass_api.o: grass_api.c grass_api.h
	gcc -c grass_api.c -o grass_api.o -lglut -lGLU -lGL -lm

buttons.o: buttons.c buttons.h
	gcc -c buttons.c -o buttons.o -lglut -lGLU -lGL -lm

sliders.o: sliders.c sliders.h
	gcc -c sliders.c -o sliders.o -lglut -lGLU -lGL -lm

list.o: list.c list.h
	gcc -c list.c -o list.o

procedural_grass: procedural_grass.c grass_api.o buttons.o sliders.o list.o
	gcc procedural_grass.c grass_api.o buttons.o sliders.o list.o -o grass -lglut -lGLU -lGL -lm	