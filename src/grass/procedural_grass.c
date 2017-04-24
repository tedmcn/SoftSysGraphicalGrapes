/* Procedural 2D maze with user motion
 * New rows are drawn when user passes edge
 */


#include "grass_api.h"

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
 * Draw the OpenGL display
 */
void display(void)
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  // Draw a ground plane
  drawGround(plane[0], plane[1], plane[2], ground_color, origin);

  // Draw the grass terrain
  drawTerrain(list);

  glutSwapBuffers();
}


int main(int argc, char **argv)
{
  glutInit(&argc, argv);

  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize(500, 500);
  glutCreateWindow("Grass");

  float temp[8] = {0,0,0,0,0,0,0,0};

  Node *head = makeNode(temp, NULL);

  list = &head;

  // Generate grass params
  generateTerrain(list, height, thick, color, plane[0], 
                  plane[1], sparse);

  printf("Nodes passed: %i\n", numNodes(list));

  /* Use depth buffering for hidden surface elimination. */
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
  glutDisplayFunc(display);

  glutMainLoop();

  return 0;  
}