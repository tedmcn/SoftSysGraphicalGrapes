/*Ted McNulty
 *2/27/17
 *ENGR 2535

 *Header for planeobject
 *
*/

#ifndef planeobject_h
#define planeobject_h

#include <GL/glut.h>
#include <stdlib.h> 
#include <stdio.h>

#include "gameobject.h"


class Planeobject : public Gameobject{

public:
	
	Planeobject(float* n, float* s, float* r);
	~Planeobject();

	//Draw the plane
	void draw();

	//check for intersections
	bool intersect();

	//Set the normal vector
	void setN(float* normal);

	//Read the normal vector
	Vectorobject getN();

protected:

	//Scale stores how large the plane is
	GLfloat *scale;

	//rotate stores how much its rotated
	float *rotate;

	//normal store the normal vector
	Vectorobject normal;
};

#endif