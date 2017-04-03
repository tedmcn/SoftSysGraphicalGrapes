#include "playerobject.h"

void look(){
    gluLookAt(p[0], p[1],           p[2],           //Position of eye
    p[0]+getV()[0], p[1]+getV()[1], p[2]+getV()[2], //Where eye is looking
    0,              1,              0)              //Normal vector of eye
    // gluLookAt(0,10,1,1,10,1,0.0,1.0,0.0);
}

bool checkForInput(){
	return false;
}