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
 * Draw tiles from list of coords at the given coords in the board
 * Reference from bottom left corner
 *
 * INPUT: coord is row and column indexing from 0 and bottom left corner
 */
void drawTiles(int coord[], int tile_len, int origin[]) {
  // Fill in grid square
  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_POLYGON);

  // Draw the list of tiles
  int i;
  for (i = 0; i < sizeof(coord); i++) {
    // Bottom left corner (x, y) of square
    int x = (tile_len * coord[0]) + origin[0];
    int y = (tile_len * coord[1]) + origin[1];

    glVertex2f(x, y);
    glVertex2f(x + tile_len, y);
    glVertex2f(x + tile_len, y + tile_len);
    glVertex2f(x, y + tile_len);
  }

  glEnd();
}