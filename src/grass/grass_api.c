/* 
 * Maze API: Provides drawing functionality for the maze
 */

#include "grass_api.h"

/*
 * Draw a ground plane
 * 
 * INPUT: color - RGB float array
 *        origin - referenced from the bottom left corner of the plane
 */
void drawGround(float width, float length, float depth, float color[], float origin[]) {
  glColor3f(color[0], color[1], color[2]);
  glBegin(GL_POLYGON);
  glVertex3f(origin[0], origin[1], 0.0);
  glVertex3f(origin[0] + width, origin[1], 0.0);
  glVertex3f(origin[0] + width, origin[1] + length, 0.0);
  glVertex3f(origin[0], origin[1] + length, 0.0);
  glEnd();
}


/*
 * Draw a single grass blade with specified parameters
 * 
 * INPUT: color - RGB float array
 *        curve - x distance between top of blade and bottom of blade
 */
void drawBlade(float base, float height, float position[3], float color[3]) {
  // Set color
  printf("Draw blade\n");
  glColor3f(color[0], color[1], color[2]);
  GLUquadricObj *quadObj = gluNewQuadric();
  glPushMatrix();
  glTranslatef(position[0], position[1], position[2]);
  gluCylinder(quadObj, base, 0, height, 20, 20);
  glPopMatrix();
}


/*
 * Generate a set of parameters to draw a field of grass
 * 
 * INPUT: color - RGB float array
 *        curve - x distance between top of blade and bottom of blade
 */
void generateTerrain(Node **result, float height[2], float h_var, 
          float thick[2], float t_var, float color[2][3], 
          float c_var, float grid_w, float grid_l, float clump, 
          float sparse) {
  printf("Generating terrain\n");
  float x;
  float y;
  int i = 0;
  float params[8];
  float test[8] = {3, 2, 5 ,6, 6, 6, 6, 6};
  float test2[8] = {5, 7, 5 ,6, 6, 6, 6, 6};
  float test3[8] = {7, 7, 5 ,6, 6, 6, 6, 6};
  Node *head = make_node(test, NULL);

  result = &head;

  float * grab;
  grab = head->val;
  printf("%f\n", grab[0]);

  push(result, test2);

  push(result, test3);

  printf("%i\n", num_nodes(result));

  grab = pop(result);
  printf("%f\n", grab[0]);

  grab = pop(result);
  printf("%f\n", grab[0]);


  // for (x = 0; x <= grid_w; x; += 5) {
  //   for (y = 0; y <= grid_l; y += 5) {
  //     // result[i][0] = 0.5; // Base
  //     // result[i][1] = 5.0; // Height
  //     // result[i][2] = x; // Pos x
  //     // result[i][3] = y; // Pos y
  //     // result[i][4] = 0.0; // Pos z
  //     // result[i][5] = 0.137255; // Color r
  //     // result[i][6] = 0.556863; // Color g
  //     // result[i][7] = 0.137255; // Color b
  //     // printf("New size: %i\n", (int)sizeof(result[0]));
  //     // i++;
  //     // printf("%i\n", i);
  //   }
  // }
}


/*
 * Draw a field of grass from an array of params
 * 
 * INPUT: color - RGB float array
 *        curve - x distance between top of blade and bottom of blade
 */
void drawTerrain(Node **params) {
  printf("Draw terrain\n");
  float pos[3];
  float color[3];
  int i;
  // for (i = 0; i < sizeof(grass); i++) {
  //   pos[0] = grass[i][2];
  //   pos[1] = grass[i][3];
  //   pos[2] = grass[i][4];
  //   color[0] = grass[i][5];
  //   color[1] = grass[i][6];
  //   color[2] = grass[i][7];
  //   drawBlade(grass[i][0], grass[i][1], pos, color);
  // }
}