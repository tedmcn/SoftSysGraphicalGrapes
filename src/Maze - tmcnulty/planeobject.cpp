/*Ted McNulty
 *2/27/17
 *ENGR 2535

 *Plane object
 *
 *Child of gameobject, this holds the necissary information to 
 *display a cube of any dimention on the screen.
*/

#include "planeobject.h"

//Constructor
//
//n : pointer to float array storing normal vector
//s : pointer to float array storing scale
//r : pointer to float array storing rotation
Planeobject::Planeobject(float* n, float* s, float* r){

	//Create int for counting
	int i;
	float temp[3];

	//Allocate memory for the new plane object
	scale = (float *)malloc(sizeof(GLfloat)*3);
	rotate = (float *)malloc(sizeof(float)*3);

	//Save all the values
	for(i=0;i<3;i++){
		scale[i]=s[i];
		temp[i]=n[i];
		rotate[i]=r[i];
	}

	//Write them onto the object
	Vectorobject norm = Vectorobject(temp);
	normal=norm;
}

//Deconstructor
Planeobject::~Planeobject(){

}

//Sets the normal vector of a plane
//
//n : pointer to a float array for normal vector
void Planeobject::setN(float* n){
	Vectorobject normal_vector = Vectorobject(n);
	//Save it
	normal = normal_vector;
}

//Read the normal vector
//
//Returns the normal vector
Vectorobject Planeobject::getN(){
	return normal;
}


//Draws the plane and adds it to the buffer
void Planeobject::draw(){

	//Add a spher0
    glPushMatrix();
    	glRotatef(45,rotate[0],rotate[1],rotate[2]);
    	glScalef(scale[0],scale[1],scale[2]);	//Scale it from a cube into a plane (size)
        glTranslatef(p[0],p[1],p[2]);			//Move it to where it needs to be
        glutSolidCube(1);						// Make the cube (size 1);
    glPopMatrix(); 
}


bool Planeobject::intersect(){
}