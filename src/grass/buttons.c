/* 
 * GUI API: Provide drawing functionality for OpenGL user interface
 */

#include "buttons.h"

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


Button Redraw = {5, 5, 100, 25, 0, "Redraw", redrawCallback};
Mouse TheMouse = {0, 0, 0, 0, 0};


/*
 * Redraw button callback
 */
void redrawCallback()
{
	
}


/*
 * Print text
 */
void Font(void *font,char *text,int x,int y)
{
	glRasterPos2i(x, y);

	while( *text != '\0' )
	{
		glutBitmapCharacter( font, *text );
		++text;
	}
}


/*
 * Check if the button was pressed
 */
int ButtonClickTest(Button* b, int x, int y) {
	if(b) {
		/*
		 *	If clicked within button area, then return true
		 */
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
void ButtonRelease(Button *b,int x,int y)
{
	if(b) 
	{
		// Check if pressed and relesaed mouse on button
		if( ButtonClickTest(b, TheMouse.xpress, TheMouse.ypress) && 
			ButtonClickTest(b, x, y) )
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
void ButtonPress(Button *b,int x,int y)
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

		/*
		 *	draw background for the button.
		 */
		glBegin(GL_QUADS);
			glVertex2i( b->x, b->y );
			glVertex2i( b->x, b->y+b->h );
			glVertex2i( b->x+b->w, b->y+b->h );
			glVertex2i( b->x+b->w, b->y );
		glEnd();

		/*
		 *	Draw an outline around the button with width 3
		 */
		glLineWidth(3);

		/*
		 *	The colours for the outline are reversed when the button. 
		 */
		if (b->state) 
			glColor3f(0.4f,0.4f,0.4f);
		else 
			glColor3f(0.8f,0.8f,0.8f);

		glBegin(GL_LINE_STRIP);
			glVertex2i( b->x+b->w, b->y );
			glVertex2i( b->x, b->y );
			glVertex2i( b->x, b->y+b->h );
		glEnd();

		if (b->state) 
			glColor3f(0.8f,0.8f,0.8f);
		else 
			glColor3f(0.4f,0.4f,0.4f);

		glBegin(GL_LINE_STRIP);
			glVertex2i( b->x, b->y+b->h );
			glVertex2i( b->x+b->w, b->y+b->h );
			glVertex2i( b->x+b->w, b->y );
		glEnd();

		glLineWidth(1);


		/*
		 *	Calculate the x and y coords for the text string in order to center it.
		 */
		fontx = b->x + (b->w - glutBitmapLength(GLUT_BITMAP_HELVETICA_10,b->label)) / 2 ;
		fonty = b->y + (b->h+10)/2;

		/*
		 *	if the button is pressed, make it look as though the string has been pushed
		 *	down. It's just a visual thing to help with the overall look....
		 */
		if (b->state) {
			fontx+=2;
			fonty+=2;
		}

		glColor3f(1,1,1);
		Font(GLUT_BITMAP_HELVETICA_10,b->label,fontx,fonty);
	}
}


/* 
 * Handle mouse press or release.
 */
void MouseButton(int button, int state, int x, int y)
{
	// update the mouse position
	TheMouse.x = x;
	TheMouse.y = y;

	if (state == GLUT_DOWN) 
	{
		if ( !(TheMouse.lmb || TheMouse.mmb || TheMouse.rmb) ) {
			TheMouse.xpress = x;
			TheMouse.ypress = y;
		}

		// which button was pressed?
		switch(button) 
		{
		case GLUT_LEFT_BUTTON:
			TheMouse.lmb = 1;
			ButtonPress(&Redraw, x, y);
		case GLUT_MIDDLE_BUTTON:
			TheMouse.mmb = 1;
			break;
		case GLUT_RIGHT_BUTTON:
			TheMouse.rmb = 1;
			break;
		}
	}
	else 
	{
		// which button was released?
		switch(button) 
		{
		case GLUT_LEFT_BUTTON:
			TheMouse.lmb = 0;
			ButtonRelease(&Redraw, x, y);
			break;
		case GLUT_MIDDLE_BUTTON:
			TheMouse.mmb = 0;
			break;
		case GLUT_RIGHT_BUTTON:
			TheMouse.rmb = 0;
			break;
		}
	}
}

/* 
 *	Update the mouse while clicked
 */
void MouseActiveUpdate(int x, int y)
{

	int dx = x - TheMouse.x;
	int dy = y - TheMouse.y;

	TheMouse.x = x;
	TheMouse.y = y;

	glutPostRedisplay();
}


/* 
 *	Update the mouse while not clicked
 */
void MousePassiveUpdate(int x, int y)
{

	int dx = x - TheMouse.x;
	int dy = y - TheMouse.y;

	TheMouse.x = x;
	TheMouse.y = y;

	glutPostRedisplay();
}


void drawButtons() {
	ButtonDraw(&Redraw);
}