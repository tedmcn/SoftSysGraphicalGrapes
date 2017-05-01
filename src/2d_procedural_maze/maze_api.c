/* 
 * Procedural Maze API - Provide drawing interface for maze
 */

#include "maze_api.h"

/*
 * Draw the background grid to place cells within
 */
void createGrid(int rows, int cols, int * ORIGIN, int TILE_LEN) {
  glColor3f(0.0, 1.0, 0.0);
  glLineWidth(10);
  glBegin(GL_LINES);
  int r;
  int c;
  // Rows
  for (r = 0; r < rows + 1; r++) {
    glVertex2f(ORIGIN[0], ORIGIN[1] + (TILE_LEN * r));
    glVertex2f(ORIGIN[0] + (cols * TILE_LEN), ORIGIN[1] + (TILE_LEN * r));
  }
  // Cols
  for (c = 0; c < cols + 1; c++) {
    glVertex2f(ORIGIN[0] + (TILE_LEN * c), ORIGIN[1]);
    glVertex2f(ORIGIN[0] + (TILE_LEN * c), ORIGIN[1] + (rows * TILE_LEN));
  }
  glEnd();
}


/*
 * Draw an individual tile within the set grid
 */
void createTile(int * coord, int alive, int TILE_LEN) {
  // Fill in grid square
  if (alive) {
    glColor3f(0.0, 0.0, 1.0);
  } else {
    glColor3f(0.0, 0.0, 0.0);
  }
  glBegin(GL_POLYGON);
  glVertex3f(coord[0], coord[1], 0.0);
  glVertex3f(coord[0] + TILE_LEN, coord[1], 0.0);
  glVertex3f(coord[0] + TILE_LEN, coord[1] + TILE_LEN, 0.0);
  glVertex3f(coord[0], coord[1] + TILE_LEN, 0.0);
  glEnd();
}


/*
 * Draw the player square at a given position
 */
void drawPlayer(int x, int y, int width) {
  // Draw initial player position
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex3f(x, y, 1.0);
  glVertex3f(x+width, y, 1.0);
  glVertex3f(x+width, y+width, 1.0);
  glVertex3f(x, y+width, 1.0);
  glEnd();
}


/*
 * Draw the start screen with instructions
 */
void drawStartScreen() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Set viewing world with one top and bottom row outside of view
  glOrtho(0.0, 750.0, 0.0, 750.0, -1.0, 1.0);

  // Draw background
  glColor3f(0.8, 0.8, 1.0);
  glBegin(GL_POLYGON);
  glVertex3f(0, 0, 0.0);
  glVertex3f(750, 0, 0.0);
  glVertex3f(750, 750, 0.0);
  glVertex3f(0, 750, 0.0);
  glEnd();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  char *title = "The Infinite Maze";

  glColor3f(0.1, 0.3, 6.0);  
  Font(GLUT_BITMAP_TIMES_ROMAN_24, title, 310, 500);


  char *goal = "The goal is simple - reach the top or bottom of the maze to win.";
  Font(GLUT_BITMAP_TIMES_ROMAN_24, goal, 150, 375);
}