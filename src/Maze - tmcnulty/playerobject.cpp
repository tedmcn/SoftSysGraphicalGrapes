#include "playerobject.h"


//Printing function for testing purposes
void Playerobject::print(){
	printf("acceleration");
    getA().print();
    printf("velocity");
    getV().print();
    printf("position\n%f | %f | %f\n",getP()[0],getP()[1],getP()[2]);
    printf("direction");
    getD().print();
}

//Constructor
Playerobject::Playerobject(){

}
//Deconstructor
Playerobject::~Playerobject(){

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


//Look
//
//Wrapper for GluLookAt Function which will read the playerobjects coordinates
//Direction it is looking and will calculate the normal of the two.
//
void Playerobject::look(){
	// printf("%f - %f - %f ",getP()[0],getP()[1],getP()[2]);
	//First set of 3 is position
	//Second set of 3 is direction
	//Third is normal
    gluLookAt(	getP()[0],					getP()[1],				getP()[2],
    			
    			getP()[0]+getD().get()[0],	getP()[1]+getD().get()[1],	
    			getP()[2]+getD().get()[2],
    			
    			0.0,						getP()[1]+1.0,			0.0);
}

//Apply the acceleration to the player to simulate movement
void Playerobject::move(char Key){
	//All cases are more or less the same, just rotated
	switch(Key){
		//Forward
        case 'w':
        	getA().add(getD().distribute());
            break;
        //Strafe left
        case 'a':
        	getA().add(getD().rotate_clockwise(-180).distribute());
            break;
        // Backward
        case 's': 
        	getA().add(getD().invert().distribute());       
        	break; 
       	//  Strafe Right
        case 'd':
            getA().add(getD().rotate_clockwise(180).distribute());
            break;
        default:
        	break;
    }
}

//Modifies the player's direction to rotate the camera
void Playerobject::rotateLeft(){
    setD(getD().rotate_clockwise(-.05).get());
    // getD().print();
}

//Modifies the player's direction to rotate the camera
void Playerobject::rotateRight(){
    setD(getD().rotate_clockwise(.05).get());
    // getD().print();
}

// Sets the player's Y velocity to simulate a jump
// Handel takes care of slowing down the jump to a stop and
// Returning the player to the ground
void Playerobject::jump(){
	// Make a new accel with the same X and Z values but y=100
	float new_acceleration[3]={getA().get()[0],100,getA().get()[2]};
	
	//We only jump if we are on the ground, this ain't sonic, no double jumps
	if(getP()[1]==10){
		//Set the acceleration
		setA(new_acceleration);
		// print();
	}
	
}

//CheckForInput
//
//Reads user input and assigns the values to acceleration/velocity
//
//Returns true if there was input
bool Playerobject::checkForInput(){
	return false;
}


//Handel Input
//
//Moves player object based on acceleration/velocity
//
//Restores old position if clipped through wall
//Returns true if walked through wall, else false
bool Playerobject::handel(Physics p){
	int i;

	//Create empty arrays we can write into 
	float temp_values1[3]={0,0,0};
	float temp_values2[3]={0,0,0};
	float temp_values3[3]={0,0,0};
	
	//Create temp values we will overwrite/modify
	float* temp_position= getP();
	float* temp_velocity = getV().get();
	float* temp_acceleration = getA().get();

	//Get time
	long double diff = p.getDiff()*10;
	// printf("%Lf\n",diff );

	//***********************************************************************//
	//POSITION
	//***********************************************************************//

	//Convert velocity into dislocation
	// X & Z
	for(i=0;i<3;i+=2){
		temp_values1[i]=diff*temp_velocity[i];
		temp_values1[i]=temp_position[i]+temp_values1[i];
	}
	// Y
	// If the player is below or where they need to be, set them on the floor
	if(getP()[1]<10 || getP()[1]==10){
		temp_values1[1]=10;
	}
	// Otherwise, 
	// if we are over the floor or our velocity hasn't been zero'd yet
	if(getP()[1]>10 || getV().get()[1]!=0){
		temp_values1[1]=diff*temp_velocity[1];
		temp_values1[1]=temp_position[1]+temp_values1[1];
	}

	//Save the Position
	setP(temp_values1);
	

	//TODO
	//Check for clipping into walls

	//***********************************************************************//
	//VELOCITY
	//***********************************************************************//    

	//Convert acceleration into velocity
	// X & Z
	temp_values2[0]=((diff*temp_acceleration[0])+temp_velocity[0])*.99;
	temp_values2[2]=((diff*temp_acceleration[2])+temp_velocity[2])*.99;

	// Y
	// If the player is below the flow we want to zero his movement
	if(getP()[1]<10){
		temp_values2[1]=0;
	}
	//Otherwise use the same formula as X and Y
	else{
		temp_values2[1]=(diff*temp_acceleration[1])+temp_velocity[1];
	}
	// Save Velocity
	setV(temp_values2);

	//***********************************************************************//
	//ACCELERATION
	//***********************************************************************//

	// X & Z
	for(i=0;i<3;i++){
		temp_values3[i]=temp_acceleration[i]*0.90;
	}
	//  Y
	if(temp_values3[1]>-5){
		temp_values3[1]=temp_values3[1]+(diff*-30);
	}

	//Save Acceleration
	setA(temp_values3);



	return false;
}

