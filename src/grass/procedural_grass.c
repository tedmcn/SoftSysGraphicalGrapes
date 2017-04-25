/* 
 * Procedural 2D maze with user motion
 * New rows are drawn when user passes edge
 */


#include "grass_api.h"
#include "buttons.h"

int SCREEN_WIDTH = 1500;
int SCREEN_HEIGHT = 1500;

// Set the ground plane params
float plane[3] = {50.0, 50.0, 1.0};
float ground_color[3] = {0.52, 0.37, 0.26};
float origin[2] = {0.0, 0.0};

// Set the generative grass parameters
float height[2] = {1.0, 3.0};
float thick[2] = {0.01, 0.1};
float color[2][3] = {{0.576471, 0.858824, 0.439216}, 
                      {0.184314, 0.309804, 0.184314}};
float sparse = 0.1;

// Global pointer to grass terrain paramters
Node **list;


/*
 * Draw the user interface sliders and inputs
 */
void drawGui() {
	glPopMatrix();
	// Start 2d
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw background box
	glColor3f(100.0f, 255.0f, 100.0f);
	glBegin(GL_QUADS);
	    glVertex2f(SCREEN_WIDTH - SCREEN_WIDTH / 5.0, 0.0);
	    glVertex2f(SCREEN_WIDTH - SCREEN_WIDTH / 5.0, SCREEN_WIDTH);
	    glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT);
	    glVertex2f(SCREEN_WIDTH, 0.0);
	glEnd();
	
	char *title = "Procedural Grass Demo";

	// printText(50, 50, title);

	drawButtons();
}


/*
 * Draw the OpenGL display
 */
void display(void)
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 40.0,
  /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 200.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 20.0,  /* eye is at (0,0,30) */
    0.0, 8.0, 0.0,      /* center is at (0,0,0) */
    0.0, 1.0, 0.0);      /* up is in postivie Y direction */

  // UD rotation
  glRotatef(-50.0, 1.0, 0.0, 0.0);
  // Spin rotation
  glRotatef(45.0, 0.0, 0.0, 1.0);

  // Draw a ground plane
  drawGround(plane[0], plane[1], plane[2], ground_color, origin);

  // Draw the grass terrain
  drawTerrain(list);

  drawGui();

  glutSwapBuffers();
}


int main(int argc, char **argv)
{
  glutInit(&argc, argv);

  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutCreateWindow("Grass Demo");

  float temp[8] = {0,0,0,0,0,0,0,0};

  Node *head = makeNode(temp, NULL);

  list = &head;

  // Generate grass params
  generateTerrain(list, height, thick, color, plane[0], 
                  plane[1], sparse);

  printf("Nodes passed: %i\n", numNodes(list));

	// Update the mouse position when moved
	glutMotionFunc(MouseActiveUpdate);
	glutPassiveMotionFunc(MousePassiveUpdate);

	// Check for mouse click
	glutMouseFunc(MouseButton);

  glutDisplayFunc(display);

  glutMainLoop();

  return 0;
}