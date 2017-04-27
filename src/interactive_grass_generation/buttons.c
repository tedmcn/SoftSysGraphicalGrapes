/* 
 * GUI API - Buttons: Provide drawing functionality for OpenGL user interface
 */

#include "buttons.h"


/*
 * Print text
 */
void Font(void *font, char *string, int x, int y)
{
	glRasterPos3f(x,y,1);
	int len = (int) strlen(string);

	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}


/*
 * Check if a given button was pressed
 */
int ButtonClickTest(Button* b, int x, int y) {
	if(b) {
		// If clicked within button area, then return true
	  if( x > b->x && x < b->x+b->w &&
				y > b->y && y < b->y+b->h ) {
			return 1;
		}
	}

	return 0;
}


/*
 * Handle the button release.
 */
void ButtonRelease(Button *b, int x, int y)
{
	if(b) 
	{
		// Check if relesaed mouse on button
		if( ButtonClickTest(b, x, y) )
		{
			// Check for callback function and run
			if (b->callbackFunction) {
				b->callbackFunction();
			}
		}

		b->state = 0;
	}
}


/*
 *	Handle the button press
 */
void ButtonPress(Button *b, int x, int y)
{
	if(b)
	{
		// Set button clicked state to true
		if( ButtonClickTest(b, x, y) )
		{
			b->state = 1;
		}
	}
}


/*
 * Draw the given button object.
 */
void ButtonDraw(Button *b)
{
	int fontx;
	int fonty;

	if(b)
	{
		glLineWidth(3);

		glColor3f(0.1, 0.1, 0.4);

		glBegin(GL_LINE_STRIP);
			glVertex2i( b->x+b->w, b->y);
			glVertex2i( b->x, b->y);
			glVertex2i( b->x, b->y+b->h);
		glEnd();

		glColor3f(0.1, 0.1, 0.4);
		
		glBegin(GL_LINE_STRIP);
			glVertex2i( b->x, b->y+b->h);
			glVertex2i( b->x+b->w, b->y+b->h);
			glVertex2i( b->x+b->w, b->y);
		glEnd();

		glLineWidth(1);

		// Calculate the x and y coords for the text string in order to center it.
		fontx = b->x + (b->w - glutBitmapLength(GLUT_BITMAP_HELVETICA_10,b->label)) / 2 ;
		fonty = b->y + (b->h+10)/2;

		glColor3f(0.8, 0.8, 1.0);
		Font(GLUT_BITMAP_HELVETICA_10,b->label,fontx,fonty);
	}
}