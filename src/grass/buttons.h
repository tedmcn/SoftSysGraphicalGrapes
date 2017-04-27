/* 
 * GUI API - Buttons: Provide drawing functionality for OpenGL user interface
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>

typedef struct Mouse Mouse;
typedef struct Button Button;
typedef void (*ButtonCallback)();

struct Mouse 
{
	int x; // The x coordinate of the mouse cursor
	int y; // The y coordinate of the mouse cursor
	int lmb; // Is the left button pressed
	int mmb; // Is the middle button pressed
	int rmb; // Is the right button pressed
	int xpress; // Stores the x-coord of when the first button press occurred
	int ypress; // Stores the y-coord of when the first button press occurred
};


struct Button 
{
	int   x; // Top left x coord of the button
	int   y; // Top left y coord of the button
	int   w; // The width of the button
	int   h; // The height of the button
	int	  state; // The state, 1 if pressed, 0 otherwise
	char* label; // The text label of the button
	ButtonCallback callbackFunction; // Button callback function
};

void Font(void *font,char *text,int x,int y);
int ButtonClickTest(Button* b, int x, int y);
void ButtonRelease(Button *b,int x,int y);
void ButtonPress(Button *b,int x,int y);
void ButtonDraw(Button *b);