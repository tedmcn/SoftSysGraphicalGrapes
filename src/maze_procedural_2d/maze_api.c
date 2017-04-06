/* 
 * Maze API: Provides drawing functionality for the maze
 */

#include "maze_api.h"

/*
 * Draw a grid
 */
void drawGrid(int rows, int cols, int tile_len, int origin[]) {
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINES);
  int r;
  int c;
  // Rows
  for (r = 0; r < rows + 1; r++) {
    glVertex2f(origin[0], origin[1] + (tile_len * r));
    glVertex2f(origin[0] + (cols * tile_len), origin[1] + (tile_len * r));
  }
  // Cols
  for (c = 0; c < cols + 1; c++) {
    glVertex2f(origin[0] + (tile_len * c), origin[1]);
    glVertex2f(origin[0] + (tile_len * c), origin[1] + (rows * tile_len));
  }
  glEnd();
}


/*
 * Draw a tile at the given coord in the board
 * Reference from bottom left corner
 *
 * INPUT: coord is row and column indexing from 0 and bottom left corner
 */
void drawTile(int coord[], int tile_len, int origin[]) {
  // Bottom left corner (x, y) of square
  int x = (tile_len * coord[0]) + origin[0];
  int y = (tile_len * coord[1]) + origin[1];

  // Fill in grid square
  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex2f(x, y);
  glVertex2f(x + tile_len, y);
  glVertex2f(x + tile_len, y + tile_len);
  glVertex2f(x, y + tile_len);
  glEnd();
}


/*
 * Add a row to the grid
 * 
 * INPUT: side - -1 is left and +1 is right
 * UPDATE: num rows and cols, origin  
 */
int addRow(int *row_num, int *col_num, int tile_len, int side, int *origin[]) {
  // TODO
}


/*
 * Add a column to the grid
 * 
 * INPUT: side - -1 is left and +1 is right
 * UPDATE: num rows and columns, origin
 */
int addCol(int *row_num, int *col_num, int tile_len, int side, int *origin[]) {
  // TODO
}