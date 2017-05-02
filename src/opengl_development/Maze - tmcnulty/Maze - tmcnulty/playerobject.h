/*Ted McNulty
 *2/27/17
 *ENGR 2535

 *Header for playerobject
*/

#ifndef playerobject_h
#define playerobject_h

#include "gameobject.h"
#include "vectorobject.h"
#include "physics.h"

class Playerobject : public Gameobject{

public:
	
	Playerobject();
	~Playerobject();

	void print();

	//Set the camera based on the playerobjects's pos and where it is looking
	void look();

	//Move the character based on the key input
	void move(char Key);

	//Rotate the player Left
	void rotateLeft();

	//Rotate the player right
	void rotateRight();

	//Makes the player jump
	void jump();

	//Check for user input to turn or move forward
	bool checkForInput();
	
	//Handel the input for the current user, move the user forward
	//based on their acceleration/velocity and fix clipping through
	//walls
	bool handel(Physics p);

	//Direction represented with a vector
	void setD(float* direction);
	Vectorobject getD();

protected:
	
	Vectorobject d;	//Direction
};


#endif		