/*Ted McNulty
 *2/27/17
 *ENGR 2535

 *Header for sphereobject
*/

#ifndef sphereobject_h
#define sphereobject_h


#include <GL/glut.h>
#include <stdlib.h> 
#include <stdio.h>

#include "gameobject.h"
#include "planeobject.h"

class Sphereobject : public Gameobject{

public:
	
	Sphereobject(float r);
	~Sphereobject();

	//Apply the phyiscs and move the sphere
	void apply(Physics p, Planeobject plane);

	//Draw the sphere on the buffer
	void draw();

	//Check for intersection with a plane
	bool intersect(Planeobject plane);

protected:
	//Radius of the sphere
	float radius;

	//time since last frame
	float previous_diff;

};

#endif