#include "playerobject.h"

//Constructor
Playerobject::Playerobject(){
	
}
//Deconstructor
Playerobject::~Playerobject(){

}

void Playerobject::look(){
	// printf("%f - %f - %f ",getP()[0],getP()[1],getP()[2]);
    gluLookAt(getP()[0],getP()[1],getP()[2],1,10,1,0.0,1.0,0.0);
}

bool Playerobject::checkForInput(){
	return false;
}