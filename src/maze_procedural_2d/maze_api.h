/*
 * Maze API: Provides drawing functionality for the maze
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

void drawGrid(int rows, int cols, int tile_len, int origin[]);
void drawTiles(int coord[][], int tile_len, int origin[]);