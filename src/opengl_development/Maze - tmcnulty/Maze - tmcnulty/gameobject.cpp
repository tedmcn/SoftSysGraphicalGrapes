/*Ted McNulty
 *2/27/17
 *ENGR 2535

 *Parent object for all objects that are added to the scene
 *
 *Mainly contains simple helper functions
*/

#include "gameobject.h"
#include "planeobject.h"

//Constructor
Gameobject::Gameobject(){
	//Gravity is constant for everything
	gravity=-9.8;
}

//Deconstructor
Gameobject::~Gameobject(){

}

//Different for every child class
//Put since this is the parent object there is nothing to draw
void Gameobject::draw(){
}


//Prints the current stats of the object
//Position
//Velocity
//Acceleration
//
//Used for diagnostics
void Gameobject::print(){
	float* temp_position= getP();
	float* temp_velocity = getV().get();
	float* temp_acceleration = getA().get();
	printf("\n");
	printf("position = %f - %f - %f\n", temp_position[0],temp_position[1],temp_position[2]);
	printf("velocity = %f - %f - %f\n", temp_velocity[0],temp_velocity[1],temp_velocity[2]);
	printf("acceleration = %f - %f - %f\n", temp_acceleration[0],temp_acceleration[1],temp_acceleration[2]);
	
	// printf("%p - %p - %p\n",&temp_position[0],&temp_velocity[0],&temp_acceleration[0]);
	// printf("%p - %p - %p\n",&temp_position[1],&temp_velocity[1],&temp_acceleration[1]);
	// printf("%p - %p - %p\n",&temp_position[2],&temp_velocity[2],&temp_acceleration[2]);

	printf("\n");
}

//***********************************************************************//
//POSITION
//***********************************************************************//

//Set the game objects main coordinates
//
//position : pointer to float array representing position
void Gameobject::setP(float* position){
	p[0]=position[0];
	p[1]=position[1];
	p[2]=position[2];
}

//Set the game objects main coordinates
//
//x : x coordinate
//y : y coordinate
//z : z coordinate
void Gameobject::setP(float x, float y, float z){
	p[0]=x;
	p[1]=y;
	p[2]=z;
}

//Read the game objects coordinates
//
//Returns position
float* Gameobject::getP(){
	return p;
}


//***********************************************************************//
//VELOCITY
//***********************************************************************//


//Set the velocity of the object
//
//velocity : pointer to float array representing Velocity vector
void Gameobject::setV(float* velocity){
	//Load the velocity into a vector object
	Vectorobject velocity_vector = Vectorobject(velocity);
	//Save it
	v = velocity_vector;
}

//Read the velocity of the object
//
//Returns velocity
Vectorobject Gameobject::getV(){
	return v;
}

//***********************************************************************//
//ACCELERATION
//***********************************************************************//


//Set the Direction of the object
//
//acceleration : pointer to a float array representing acceleration
void Gameobject::setA(float* acceleration){
	//Load the acceleration into a vector object
	Vectorobject acceleration_vector = Vectorobject(acceleration);
	//Save it
	a = acceleration_vector;
}

//Read the direction of the object
//
//Returns acceleration
Vectorobject Gameobject::getA(){
	return a;
}

//Apply gravity and collision detection
//This will be different for every object
void Gameobject::apply(Physics p){
}