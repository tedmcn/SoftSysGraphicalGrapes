/*
 * Maze API: Provides drawing functionality for the maze
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>


void createGrid(int rows, int cols, int tile_len, int origin[]) {
void createTile(int coord[], int side_len);