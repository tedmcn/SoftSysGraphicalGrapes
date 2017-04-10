#include "playerobject.h"

//Constructor
Playerobject::Playerobject(){

}
//Deconstructor
Playerobject::~Playerobject(){

}

void Playerobject::look(){
	// printf("%f - %f - %f ",getP()[0],getP()[1],getP()[2]);
	//			//position					//where you are looking															//normal
    gluLookAt(getP()[0],getP()[1],getP()[2],getP()[0]+getD().get()[0],getP()[1]+getD().get()[1],getP()[2]+getD().get()[2],0.0,1.0,0.0);
}

bool Playerobject::checkForInput(){
	return false;
}

//***********************************************************************//
//VELOCITY
//***********************************************************************//


//Set the direction of the object
//
//direction : pointer to float array representing Velocity vector
void Playerobject::setD(float* direction){
	//Load the velocity into a vector object
	Vectorobject direction_vector = Vectorobject(direction);
	//Save it
	d = direction_vector;
}

//Read the velocity of the object
//
//Returns velocity
Vectorobject Playerobject::getD(){
	return d;
}