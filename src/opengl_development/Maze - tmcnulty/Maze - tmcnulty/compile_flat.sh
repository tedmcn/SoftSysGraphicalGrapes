#Ted McNulty
#2/27/17
#ENGR 2535
##
##Compiles and runs the flat simulation
##

#include each .cpp file in the line below

g++ -o flat vectorobject.cpp physics.cpp planeobject.cpp gameobject.cpp sphereobject.cpp flat.cpp -lglut -lGLU -lGL -lm && ./flat