/* 
 * Grass API: Provide drawing functionality for procedurally generated grass
 */

#include "grass_api.h"

/*
 * Draw a ground plane
 * 
 * INPUT: color - RGB float array
 *        origin - referenced from the bottom left corner of the plane
 */
void drawGround(float width, float length, float depth, 
                float color[], float origin[]) {
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
void generateTerrain(Node **result, float height[2], float thick[2],
                     float color[2][3], float grid_w, float grid_l, 
                     float sparse, float dev) {
  printf("Generating terrain\n");
  float x = 0;
  float y = 0;

  // Compute median of the base range
  float base_mid = (thick[0] + thick[1])/2;
  printf("Base median: %f\n", base_mid);

  // Compute number of blades in the scene
  int number_blades = numBlades(sparse, grid_w, grid_l, base_mid);
  printf("Number of blades: %i\n", number_blades);

  // Generate the blade parameters
  int i;
  for (i = 0; i < number_blades; i++) {
    // Allocate blade node
    float * temp;
    temp = (float *)malloc(sizeof(float)*8);

    // Demo 1: Compute blade position based on distribution around center point
    x = boxMuller(grid_w / 2.0, dev, 0.0, grid_w);
    y = boxMuller(grid_l / 2.0, dev, 0.0, grid_l);

    // Demo 2: Spread blades evenly over terrain
    // x += base_mid;
    // if (x > grid_w) {
    //   x = 0;
    //   y += base_mid;
    // } 

    // Assign blade params to node
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

  printf("Created %i nodes\n", numNodes(result));
}


/*
 * Draw a field of grass from an array of params
 * 
 * INPUT: color - RGB float array
 *        curve - x distance between top of blade and bottom of blade
 */
void drawTerrain(Node **params) {
  float pos[3];
  float color[3];

  int limit = numNodes(params);
  Node *dummy = *params;

  printf("%i\n", limit);

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
  printf("Drew terrain\n");
}


/*
 * Determine the number of blades needed to create the given sparse effect
 * 
 * INPUT: med - median of the blade base limits
 *        sparse - 0-1.0, percentage of scene filled with grass
 */
int numBlades(float sparse, float grid_w, float grid_l, float med) {
  return (int)(sparse * ((grid_w / med) * (grid_l / med)));
}


/*
 * Return a random float within the given bounds
 * 
 * INPUT: a - min value
 *        b - max value
 */
float randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}


/*
 * Return the correct rounded value of the given float
 */
float roundFloat(float n) {
    return floor(n + 0.5);
}


/*
 * Return the input value mapped to the output range
 */
float map(float in_range[2], float out_range[2], float input) {
  float slope = 1.0 * (out_range[1] - out_range[0]) / 
                      (in_range[1] - in_range[0]);
  return out_range[0] + slope * (input - in_range[0]);
}


/*
 * Return gaussian coordinate in cartesian form
 * Using the Marsaglia polar method to improve run time
 */
float gaussian() {
  float v1, v2, s;
  do {
      v1 = 2.0f * randomFloat(0.0f, 1.0f) - 1.0f;
      v2 = 2.0f * randomFloat(0.0f, 1.0f) - 1.0f;
      s = v1 * v1 + v2 * v2;
  } while (s >= 1.0f || s == 0.0f);

  s = sqrt((-2.0f * log(s)) / s);

  return v1 * s;
}


/*
 * Return an (x, y) coord using the Box-Miller distribution
 */
float boxMuller(float mean, float std_dev, float min, float max) {
  float x;
  do {
    x = gaussian(mean, std_dev);
    x = mean + x * std_dev;
  } while (x < min || x > max);

  return x;
}