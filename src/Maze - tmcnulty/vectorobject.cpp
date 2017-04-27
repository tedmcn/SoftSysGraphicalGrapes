/*Ted McNulty
 *2/27/17
 *ENGR 2535
*/

//A vector is a one directional line with finite length
//we are using it to represent the direction of a given object in 3D space
//
//The direction is derived by caluclating the angel from the origin
//to the float[] of coordinates...
//
//IE A vector of values {0,1,0} is representing straight up because
//From the origin {0,0,0} to {0,1,0} is a move of 1 up in the y direction.
//
//More complex vectors can be represented with coordinates further 
// from the origin such as {1,2,0} (x=2y graph) which is different from 
// {1,1,0} (which is x=y graph)

#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include "vectorobject.h"
//Construct a new vector object
//
//c : pointer to float array storing the coordinates it points to from origin
Vectorobject::Vectorobject(float* c){
	coordinates = (float *)malloc(sizeof(float)*3);

    //assign them
	coordinates[0]=c[0];
	coordinates[1]=c[1];
	coordinates[2]=c[2];
}

//Construct a new vector object
Vectorobject::Vectorobject(){
	
	coordinates = (float *)malloc(sizeof(float)*3);

    //Assign all 0 for no argument call
	coordinates[0]=0;
	coordinates[1]=0;
	coordinates[2]=0;
}

Vectorobject::~Vectorobject(){

}


//Read the vectors values
//
//Returns a pointer to a float array of coordinates
float* Vectorobject::get(){
    return coordinates;
}

//Set the vectors values
//
//c : poiter to float array with coordinates to where the vector points
void Vectorobject::set(float* c){
    coordinates[0]=c[0];
    coordinates[1]=c[1];
    coordinates[2]=c[2];
}

bool Vectorobject::add(Vectorobject v){
    coordinates[0]=coordinates[0]+v.coordinates[0];
    coordinates[1]=coordinates[1]+v.coordinates[1];
    coordinates[2]=coordinates[2]+v.coordinates[2];
    return true;
}

//Averages two different vectors
//
//The average of {0,1,0} and {1,0,0} (a vector going straigh up and straight 
//on the x axis) should be {1,1,0} because it is going in between the straight
//up and straight to the side vectors, resulting in a x=y vector.
Vectorobject Vectorobject::average(Vectorobject v){
    
    float x1 = (v.coordinates[0]+coordinates[0])/2;
    float y1 = (v.coordinates[1]+coordinates[1])/2;
    float z1 = (v.coordinates[2]+coordinates[2])/2;
    float coords[3]={x1,y1,z1};
    Vectorobject new_v = Vectorobject(coords);
    return new_v;
}


Vectorobject Vectorobject::distribute(){
    float sum = get()[0]+get()[2];
    if(sum<0){
        sum=sum*-1;
    }
    if(sum==0){

    }
    float coords[3]={get()[0]/sum,
                    0,
                    get()[2]/sum};
    Vectorobject new_v = Vectorobject(coords);
    print();
    return new_v;
}

Vectorobject Vectorobject::invert(){
    int i;
    float temp[]={0,0,0};
    for(i=0;i<3;i++){
        temp[i]=coordinates[i]*-1;
    }
    return Vectorobject(temp);
}

Vectorobject Vectorobject::rotate_clockwise(double angel){
    double radians= (M_PI*angel)/360;
    float cs = cos(radians);
    float sn = sin(radians);
    float x = (coordinates[0] * cs)-(coordinates[2]*sn);
    float z = (coordinates[0] * sn)+(coordinates[2]*cs);
    float temp[] = {x,0,z};
    return Vectorobject(temp);
}

void Vectorobject::print(){
    printf("\n%f | %f | %f\n",coordinates[0], coordinates[1], coordinates[2]);
}