3d_maze: 3d_maze.cpp gameobject.cpp gameobject.h physics.cpp physics.h planeobject.cpp planeobject.h sphereobject.cpp sphereobject.h vectorobject.cpp vectorobject.h playerobject.cpp playerobject.h
	g++ -o 3d_maze vectorobject.cpp physics.cpp planeobject.cpp gameobject.cpp sphereobject.cpp playerobject.cpp 3d_maze.cpp -lglut -lGLU -lGL -lm

# TODO 
# MAKE THIS BETTER

# CC = g++
# CFLAGS=-o
# PFLAGS=-lglut -lGLU -lGL -lm

# all:flat

# flat: sphereobject.o planeobject.o playerobject.o helpers.o gameobject.o
# 	$(CC) $(CFLAGS) sphereobject.o planeobject.o playerobject.o helpers.o gameobject.o $(PFLAGS)

# sphereobject.o: sphereobject.cpp planeobject.o
# 	$(CC) $(CFLAGS) sphereobject.cpp planeobject.o $(PFLAGS)

# planeobject.o: planeobject.cpp gameobject.o
# 	$(CC) $(CFLAGS) planeobject.cpp gameobject.o $(PFLAGS)

# playerobject.o: helpers.o playerobject.cpp gameobject.o
# 	$(CC) $(CFLAGS) helpers.o playerobject.cpp gameobject.o $(PFLAGS)

# helpers.o: vectorobject.cpp gameobject.cpp physics.cpp
# 	$(CC) $(CFLAGS) vectorobject.cpp gameobject.cpp physics.cpp $(PFLAGS)

# gameobject.o: gameobject.cpp
# 	$(CC) $(CFLAGS) gameobject.cpp $(PFLAGS)

clean:
	rm *o flat