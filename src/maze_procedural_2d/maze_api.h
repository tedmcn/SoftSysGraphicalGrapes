/*
 * Maze API: Provides drawing functionality for the maze
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

void drawGrid(int rows, int cols, int tile_len, int origin[]);
void drawTile(int coord[], int tile_len, int origin[]);
int addRow(int *row_num, int *col_num, int tile_len, int side, int *origin[]);
int addCol(int *row_num, int *col_num, int tile_len, int side, int *origin[]);