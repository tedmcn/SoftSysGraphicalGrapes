/* 
 * GUI API: Provide drawing functionality for OpenGL user interface
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>

typedef struct Mouse Mouse;
typedef struct Button Button;

void redrawCallback();
void Font(void *font,char *text,int x,int y);
int ButtonClickTest(Button* b, int x, int y);
void ButtonRelease(Button *b,int x,int y);
void ButtonPress(Button *b,int x,int y);
void ButtonDraw(Button *b);
void MouseButton(int button, int state, int x, int y);
void MouseActiveUpdate(int x, int y);
void MousePassiveUpdate(int x, int y);
void drawButtons();