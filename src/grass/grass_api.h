/*
 * Maze API: Provides drawing functionality for the maze
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "list.h"

void drawGround(float width, float legnth, float depth, float color[], 
				float origin[]);
void drawBlade(float base, float height, float position[3], float color[3]);
void generateTerrain(Node **result, float height[2], float h_var, 
					float thick[2], float t_var, float color[2][3], 
					float c_var, float grid_w, float grid_l, float clump, 
					float sparse);
void drawTerrain(Node **params);
float randomFloat(float a, float b);