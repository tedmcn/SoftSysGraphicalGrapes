/* 
 * GUI API - SLiders: Provide drawing functionality for OpenGL user interface
 */

#include "sliders.h"


/*
 * Print text
 */
void SliderLabels(void *font, char *string, int x, int y)
{
	glRasterPos3f(x,y,1);
	int len = (int) strlen(string);

	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}


/*
 * Draw the given slider object.
 */
void SliderDraw(Slider *s)
{
	int fontx;
	int fonty;

	if(s)
	{
		// Draw the slider bar
		glLineWidth(3);

		glColor3f(0.1, 0.1, 0.4);

		glBegin(GL_LINE_STRIP);
			glVertex2i( s->x_min, s->y_draw );
			glVertex2i( s->x_max, s->y_draw );
		glEnd();

		// Draw the button
		glColor3f(0.8, 0.8, 1.0);
		glBegin(GL_QUADS);
			glVertex2i(  s->x_state, s->y_draw-20 );
			glVertex2i( 20 + s->x_state, s->y_draw-20 );
			glVertex2i( 20 + s->x_state, s->y_draw+20 );
			glVertex2i( s->x_state, s->y_draw+20 );
		glEnd();
	}
}


/*
 * Check if the slider button was pressed
 */
int SliderClickTest(Slider* s, int x, int y) {
	// If clicked within the slider button area, then return true
	if (s) {
    if( x > s->x_state-20 && x < s->x_state+20 &&
				y > s->y_draw-20 && y < s->y_draw+20 ) {
			return 1;
		}
	}
	return 0;
}