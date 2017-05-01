/*Ted McNulty
 *2/27/17
 *ENGR 2535

 *Header for Physics object
*/

#ifndef physics_h
#define physics_h

#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h> 
#include <stdio.h>

class Physics{

public:

	Physics();
	~Physics();

	//Update the time between frames
	void update();
	//Read the time between frames
	long double getDiff();

protected:

	//Current time
	long double t;
	
	//Difference in time between the last and current time
	long double diff;

	//Struct used to write current time into with time.h
	struct timeval now;

private:

};

#endif