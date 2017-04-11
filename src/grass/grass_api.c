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

  // Calculate ranges from var
  // percentiles here

  for (x = 0; x <= grid_w; x += 0.6) {
    for (y = 0; y <= grid_l; y += 0.6) {
      float * temp;
      temp = (float *)malloc(sizeof(float)*8);

      temp[0] = randomFloat(thick[0], thick[1]); // Base
      temp[1] = randomFloat(height[0], height[1]); // Height
      temp[2] = x; // Pos x
      temp[3] = y; // Pos y
      temp[4] = 0.0; // Pos z
      temp[5] = randomFloat(color[0][0], color[1][0]); //0.137255; // Color r
      temp[6] = randomFloat(color[0][1], color[1][1]); //0.556863; // Color g
      temp[7] = randomFloat(color[0][2], color[1][2]); //0.137255; // Color b

      push(result, temp);
    }
  }

  printf("Created %i nodes\n", num_nodes(result));
}


/*
 * Draw a field of grass from an array of params
 * 
 * INPUT: color - RGB float array
 *        curve - x distance between top of blade and bottom of blade
 */
void drawTerrain(Node **params) {
  printf("Drawing terrain ..\n");
  float pos[3];
  float color[3];

  int limit = num_nodes(params);
  Node *dummy = *params;

  while (limit > 0) {
    float * grab = dummy->val;

    pos[0] = grab[2];
    pos[1] = grab[3];
    pos[2] = grab[4];
    color[0] = grab[5];
    color[1] = grab[6];
    color[2] = grab[7];
    drawBlade(grab[0], grab[1], pos, color);

    dummy = dummy->next;
    limit--;
  }
}

float randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}