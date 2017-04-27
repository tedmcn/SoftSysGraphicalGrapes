#include "playerobject.h"



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
    gluLookAt(	getP()[0],					getP()[1],					getP()[2],
    			getP()[0]+getD().get()[0],	getP()[1]+getD().get()[1],	getP()[2]+getD().get()[2],
    			0.0,						getP()[1]+1.0,				0.0);
}

void Playerobject::move(char Key){
	switch(Key){
        case 'w':
        	getA().add(getD().distribute());
            break;
        case 'a':
        	getA().add(getD().rotate_clockwise(-180).distribute());
            break;
        case 's': 
        	getA().add(getD().invert().distribute());       
        	break;    
        case 'd':
            getA().add(getD().rotate_clockwise(180).distribute());
            break;
        default:

        	break;
    }
}

void Playerobject::rotateLeft(){
    setD(getD().rotate_clockwise(-5).get());
    // getD().print();
}

void Playerobject::rotateRight(){
    setD(getD().rotate_clockwise(5).get());
    // getD().print();
}

void Playerobject::jump(){
	float new_acceleration[3]={getA().get()[0],3,getA().get()[2]};
	if(getP()[1]==10){
		setA(new_acceleration);
		print();
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
	long double diff = p.getDiff()*100;
	// printf("%Lf\n",diff );

	//***********************************************************************//
	//POSITION
	//***********************************************************************//

	//Convert velocity into dislocation
	for(i=0;i<3;i+=2){
		temp_values1[i]=diff*temp_velocity[i];
		temp_values1[i]=temp_position[i]+temp_values1[i];
	}
	if(getP()[1]<10 || getP()[1]==10){
		temp_values1[1]=10;
	}
	if(getP()[1]>10 || getV().get()[1]!=0){
		temp_values1[1]=diff*temp_velocity[1];
		temp_values1[1]=temp_position[1]+temp_values1[1];
	}

	setP(temp_values1);
	//Check for clipping into walls

	//***********************************************************************//
	//VELOCITY
	//***********************************************************************//    

	//Convert acceleration into velocity
	temp_values2[0]=((diff*temp_acceleration[0])+temp_velocity[0])*.99;
	temp_values2[2]=((diff*temp_acceleration[2])+temp_velocity[2])*.99;

	if(getP()[1]<10){
		temp_values2[1]=0;
	}
	else{
		temp_values2[1]=(diff*temp_acceleration[1])+temp_velocity[1];
	}

	setV(temp_values2);

	//***********************************************************************//
	//ACCELERATION
	//***********************************************************************//


	for(i=0;i<3;i++){
		temp_values3[i]=temp_acceleration[i]*0.90;
	}
	if(temp_values3[1]>-5){
		temp_values3[1]=temp_values3[1]+(diff*-.15);
	}
	// temp_values3[1]=-.5;
	setA(temp_values3);



	return false;
}

