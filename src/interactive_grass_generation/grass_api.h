/*
 * Grass API: Provides drawing functionality for the grass terrain
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "list.h"

void drawGround(float width, float legnth, float depth, float color[], 
				float origin[]);
void drawBlade(float base, float height, float position[3], float color[3]);
void generateTerrain(Node **result, float height[2], float thick[2],
                     float color[2][3], float grid_w, float grid_l, 
                     float sparse, float dev);
void drawTerrain(Node **params);
int numBlades(float sparse, float grid_w, float grid_l, float med);
float randomFloat(float a, float b);
float roundFloat(float n);
float map(float in_range[2], float out_range[2], float input);
float gaussian();
float boxMuller(float mean, float std_dev, float min, float max);