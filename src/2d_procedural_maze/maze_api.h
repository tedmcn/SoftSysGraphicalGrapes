/* 
 * Procedural Maze API - Drawing and cellular automata interface
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>

void createGrid(int rows, int cols, int * ORIGIN, int TILE_LEN);
void createTile(int * coord, int alive, int TILE_LEN);
void drawPlayer(int x, int y, int width);
void drawStartScreen();