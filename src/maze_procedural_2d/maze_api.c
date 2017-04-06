/* 
 * Maze API: Provides drawing functionality for the maze
 */

#include "maze_api.h"

void createGrid(int rows, int cols, int tile_len, int origin[]) {
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

void createTile(int coord[], int side_len) {
  // Fill in grid square
  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex2f(coord[0], coord[1]);
  glVertex2f(coord[0] + side_len, coord[1]);
  glVertex2f(coord[0] + side_len, coord[1] + side_len);
  glVertex2f(coord[0], coord[1] + side_len);
  glEnd();
}