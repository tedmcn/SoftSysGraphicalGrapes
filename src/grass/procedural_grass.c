/* 
 * Procedural 2D maze with user motion
 * New rows are drawn when user passes edge
 */


#include "grass_api.h"
#include "buttons.h"
#include "sliders.h"

int SCREEN_WIDTH = 750;
int SCREEN_HEIGHT = 750;

// Set the ground plane params
float plane[3] = {50.0, 50.0, 1.0};
float ground_color[3] = {0.52, 0.37, 0.26};
float origin[2] = {0.0, 0.0};

// Set the generative grass parameters
float height[2] = {1.0, 3.0};
float thick[2] = {0.01, 0.1};
float color[2][3] = {{0.576471, 0.858824, 0.439216}, 
                      {0.184314, 0.309804, 0.184314}};
float sparse = 0.2;

float dev = 50.0;

// Global pointer to grass terrain paramters
Node **list;

int redraw_terrain = 1;

// Declare all the sliders
struct Slider HeightSlider = {600, 700, 
												650, 0.0, (750 / 5) * 1, 
												"short", "tall"};
struct Slider WidthSlider = {600, 700, 
												650, 0.0, (750 / 5) * 2, 
												"thin", "thick"};
struct Slider SparseSlider = {600, 700,
												650, 0.0, (750 / 5) * 3, 
												"sparse", "full"};
struct Slider DistrSlider = {600, 700, 
												650, 0.0, (750 / 5) * 4, 
												"clumped", "spread"};

// Declare the redraw button and callback
void redrawCallback() {
	// Update the grass params from the sliders
	height[1] = HeightSlider.value;
	thick[1] = WidthSlider.value;
	sparse = SparseSlider.value;
	dev = DistrSlider.value;

	// Regenerate the blade list
	// TODO: free the mem for old list

	Node **newList;

	float temp[8] = {0,0,0,0,0,0,0,0};

  Node *newHead = makeNode(temp, NULL);

  newList = &newHead;

  printf("New list: %i\n", numNodes(list));

  generateTerrain(newList, height, thick, color, plane[0], 
                  plane[1], sparse, dev);

  printf("Nodes passed: %i\n", numNodes(newList));

  *list = *newList;

  printf("Passed list: %i\n", numNodes(list)); 

  redraw_terrain = 1;

  glutPostRedisplay();
}


struct Button Redraw = {600, 675, 100, 25, 0, "Redraw", redrawCallback};
struct Mouse TheMouse = {0, 0, 0, 0, 0};


/*
 * Draw the user interface sliders and inputs
 */
void drawGui() {

	// Start 2d
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	char *title = "Procedural Grass Demo";

	glColor3f(0.0, 255.0f, 0.0);	
	Font(GLUT_BITMAP_HELVETICA_10, title, 600, 50);

	ButtonDraw(&Redraw);
	SliderDraw(&HeightSlider);
	SliderDraw(&WidthSlider);
	SliderDraw(&SparseSlider);
	SliderDraw(&DistrSlider);
}


/*
 * Draw the OpenGL display
 */
void display(void)
{

	printf("Redraw\n");
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glEnable(GL_DEPTH_TEST);

  // Draw a ground plane
  drawGround(plane[0], plane[1], plane[2], ground_color, origin);

  // Draw the grass terrain
  if (redraw_terrain) {
  	printf("Redraw terrain\n");
  	drawTerrain(list);
  	redraw_terrain = 0;
  }

  drawGui();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective( /* field of view in degree */ 40.0,
  /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 200.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 20.0,  /* eye is at (0,0,30) */
  0.0, 8.0, 0.0,      /* center is at (0,0,0) */
  0.0, 1.0, 0.0);      /* up is in postivie Y direction */

	// UD rotation
  glRotatef(-50.0, 1.0, 0.0, 0.0);

  // Spin rotation
  glRotatef(45.0, 0.0, 0.0, 1.0);

  glutSwapBuffers();

}


/* 
 *	Update the mouse position while clicked
 */
void MouseActiveUpdate(int x, int y)
{

	int dx = x - TheMouse.x;
	int dy = y - TheMouse.y;

	TheMouse.x = x;
	TheMouse.y = y;

	// Check for slider position updates
	if (SliderClickTest(&HeightSlider, TheMouse.x, TheMouse.y)) {
		if (TheMouse.x > HeightSlider.x_max) {
			HeightSlider.x_state = HeightSlider.x_max;
		}
		else if (TheMouse.x < HeightSlider.x_min) {
			HeightSlider.x_state = HeightSlider.x_min;
		}
		else {
			HeightSlider.x_state = TheMouse.x;
		}

		// Update height value
		float h_in[2] = {(float)HeightSlider.x_min, (float)HeightSlider.x_max};
		float h_out[2] = {1.0, 5.0};
		HeightSlider.value = map(h_in, h_out, HeightSlider.x_state);
		printf("Max height: %f\n", HeightSlider.value);
	}
	else if (SliderClickTest(&WidthSlider, TheMouse.x, TheMouse.y)) {
		if (TheMouse.x > WidthSlider.x_max) {
			WidthSlider.x_state = WidthSlider.x_max;
		}
		else if (TheMouse.x < DistrSlider.x_min) {
			WidthSlider.x_state = WidthSlider.x_min;
		}
		else {
			WidthSlider.x_state = TheMouse.x;
		}

		// Update width value
		float w_in[2] = {(float)WidthSlider.x_min, (float)WidthSlider.x_max};
		float w_out[2] = {0.08, 1.0};
		WidthSlider.value = map(w_in, w_out, WidthSlider.x_state);
		printf("Max width: %f\n", WidthSlider.value);
	}
	else if (SliderClickTest(&SparseSlider, TheMouse.x, TheMouse.y)) {
		if (TheMouse.x > SparseSlider.x_max) {
			SparseSlider.x_state = SparseSlider.x_max;
		}
		else if (TheMouse.x < SparseSlider.x_min) {
			SparseSlider.x_state = SparseSlider.x_min;
		}
		else {
			SparseSlider.x_state = TheMouse.x;
		}

		// Update sparse value
		float s_in[2] = {(float)SparseSlider.x_min, (float)SparseSlider.x_max};
		float s_out[2] = {0.0, 0.2};
		SparseSlider.value = map(s_in, s_out, SparseSlider.x_state);
		printf("Sparse: %f\n", SparseSlider.value);
	}
	else if (SliderClickTest(&DistrSlider, TheMouse.x, TheMouse.y)) {
		if (TheMouse.x > DistrSlider.x_max) {
			DistrSlider.x_state = DistrSlider.x_max;
		}
		else if (TheMouse.x < DistrSlider.x_min) {
			DistrSlider.x_state = DistrSlider.x_min;
		}
		else {
			DistrSlider.x_state = TheMouse.x;
		}

		// Update dev value
		float d_in[2] = {(float)DistrSlider.x_min, (float)DistrSlider.x_max};
		float d_out[2] = {50, 100};
		DistrSlider.value = map(d_in, d_out, DistrSlider.x_state);
		printf("Distribution: %f\n", DistrSlider.value);
	}

	glutPostRedisplay();
}


/* 
 *	Update the mouse position while not clicked
 */
void MousePassiveUpdate(int x, int y)
{

	int dx = x - TheMouse.x;
	int dy = y - TheMouse.y;

	TheMouse.x = x;
	TheMouse.y = y;
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


int main(int argc, char **argv)
{
  glutInit(&argc, argv);

  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutCreateWindow("Grass Demo");

  float temp[8] = {0,0,0,0,0,0,0,0};

  Node *head = makeNode(temp, NULL);

  list = &head;


  printf("New list: %i\n", numNodes(list));

  // Generate grass params
  generateTerrain(list, height, thick, color, plane[0], 
                  plane[1], sparse, dev);

  printf("Nodes passed: %i\n", numNodes(list));

	glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective( /* field of view in degree */ 40.0,
  /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 200.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 20.0,  /* eye is at (0,0,30) */
  0.0, 8.0, 0.0,      /* center is at (0,0,0) */
  0.0, 1.0, 0.0);      /* up is in postivie Y direction */

	// UD rotation
  glRotatef(-50.0, 1.0, 0.0, 0.0);

  // Spin rotation
  glRotatef(45.0, 0.0, 0.0, 1.0);

	// Update the mouse position when moved
	glutMotionFunc(MouseActiveUpdate);
	glutPassiveMotionFunc(MousePassiveUpdate);

	// Check for mouse click
	glutMouseFunc(MouseButton);

  glutDisplayFunc(display);

  glutMainLoop();

  return 0;
}