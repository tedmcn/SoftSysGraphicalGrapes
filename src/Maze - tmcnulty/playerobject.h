/*Ted McNulty
 *2/27/17
 *ENGR 2535

 *Header for playerobject
*/

#ifndef playerobject_h
#define playerobject_h

#include "gameobject.h"
#include "vectorobject.h"

class Playerobject : public Gameobject{

public:
	
	Playerobject();
	~Playerobject();

	//Set the camera based on the playerobjects's pos and where it is looking
	void look();

	//Check for user input to turn or move forward
	bool checkForInput();

protected:
	
	Vectorobject d[3];	//Direction
};


#endif		