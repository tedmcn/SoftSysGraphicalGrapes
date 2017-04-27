/* 
 * GUI API - Sliders: Provide drawing functionality for OpenGL user interface
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>

typedef struct Slider Slider;

struct Slider
{
	int x_min; // Min x coord for slider
	int x_max; // Max x coord for slider
	int x_state; // Current x pos of slider
	float value; // Translated value of x pos
	int y_draw; // Y drawing pos, bottom left
	char *min_label; // Text label for min
	char *max_label; // Text label for max
};

void SliderDraw(Slider *s);
int SliderClickTest(Slider* s, int x, int y);