/*  
 * 2D Maze Game - Procedurally generated using cellular automata
 */

#include <stdio.h>
#include <GL/glut.h>
#include "buttons.h"

static const int TILE_LEN = 10;
static const int PLAYER_WIDTH = 4;
static const int SPEED = 2;
static const int ORIGIN[2] = {-300, -290};
static const int STARTING_ROW = 39;
static const int STARTING_COL = 40;
static const int ROWS = 80;
static const int COLS = 80;

// Init cellular array and position parameters
int yTranslation = 0;
int xTranslation = 0;
int xTransAbs = (40 * 10) + 5; // (STARTING_COL * TILE_LEN) + (TILE_LEN/2)
int alive_arr[80][80];
int generations = 100;

// Set window view refresh rows
int topCut = 29;
int bottomCut = 51;

// Store the state of the game 
typedef enum State State;
enum State {
  start,
  play
};
State gameState = start;


/*
 * Change the game state when the start button is pressed
 */
void startCallback() {
  gameState = play;

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Set viewing world with one top and bottom row outside of view
  glOrtho(0.0, 200.0, 0.0, 200.0, -1.0, 1.0);

  glutPostRedisplay();
}

// Create the start button and mouse objects
struct Button Start = {325, 200, 100, 50, 0, "START", startCallback};
struct Mouse TheMouse = {0, 0, 0, 0, 0};


/*
 * Draw the background grid to place cells within
 */
void createGrid(int rows, int cols) {
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
void createTile(int coord[], int alive) {
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
 * Determine the number of live neighbors around a given cell
 */
int getNeighborCount(int row, int col)
{
  int count = 0;

  // Check previous row
  if (row > 0) {
    if (col > 0) count += alive_arr[row-1][col-1];
    count += alive_arr[row-1][col];
    if (col+1 < COLS) count += alive_arr[row-1][col+1];
  }

  // Check up and down the current row
  if (col > 0) count += alive_arr[row][col-1];
  if (col+1 < COLS) count += alive_arr[row][col+1];

  // Check next row
  if (row+1 < ROWS) {
    if (col > 0) count += alive_arr[row+1][col-1];
    count += alive_arr[row+1][col];
    if (col+1 < COLS) count += alive_arr[row+1][col+1];
  }

  return count;
}


/*
 * Fill in the cells in the top or bottom row
 * 
 * Input: direction - 0 if top, 1 if bottom
 */
void advanceRow(int row) {
  int j;
  for (j = 0; j < COLS; j++) {
    // survive if you have 1-5 neighbors
    // create if you have 3 neighbors
    int neighbors = getNeighborCount(row,j);
    if (alive_arr[row][j]) {
      // This is alive
      if (neighbors < 1 || neighbors > 5) {
        // Die
        alive_arr[row][j] = 0;
      }
    } else {
      // This is dead
      if (neighbors == 3) {
        // Create
        alive_arr[row][j] = 1;
      }
    }
  }
}


/*
 * Advance one generation over the entire grid
 */
void advanceGeneration()
{
  int i;
  int j;
  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLS; j++) {
      // survive if you have 1-5 neighbors
      // create if you have 3 neighbors
      int neighbors = getNeighborCount(i,j);
      if (alive_arr[i][j]) {
        // This is alive
        if (neighbors < 1 || neighbors > 5) {
          // Die
          alive_arr[i][j] = 0;
        }
      } else {
        // This is dead
        if (neighbors == 3) {
          // Create
          alive_arr[i][j] = 1;
        }
      }
    }
  }
}


/*
 * Create a new row at either the top or the bottom of the maze
 * 
 * Also refreshes all cells above or below the viewing window
 * 
 * Input: direction - 0 if top, 1 if bottom
 */
void createRow(int direction)
{
  // If top: shift all rows down one, generate new top row
  if (direction == 1) {
    // Shift all rows down
    int i;
    for (i = ROWS; i > 0; i--) {
      int a;
      for (a = 0; a < COLS; a++) {
        alive_arr[i][a] = alive_arr[i-1][a];
      }
    }
    // Create new top row
    int x;
    int r;
    for (x = 0; x < COLS; x++) {
      r = rand() % 10;
      if (r == 5) {
        alive_arr[0][x] = 1;
      }
      else {
        alive_arr[0][x] = 0;
      }
    }
    // Run for generations to reset
    for (i = 0; i < generations; i++) {
      int a;
      for (a = topCut; a >= 0; a--) {
        advanceRow(a);
      }
    }
    glTranslatef(0.0, -TILE_LEN, 0.0);
  }

  // If bottom: shift all rows up one, generate new bottom row
  else {
    // Shift all rows up
    int j;
    for (j = 0; j < ROWS; j++) {
      int b;
      for (b = 0; b < COLS; b++) {
        alive_arr[j][b] = alive_arr[j+1][b];
      }
    }
    // Create new bottom row
    int y;
    int r;
    for (y = 0; y < COLS; y++) {
      r = rand() % 10;
      if (r == 5) {
        alive_arr[ROWS-1][y] = 1;
      }
      else {
        alive_arr[ROWS-1][y] = 0;
      }
    }
    // Run for generations to reset
    for (j = 0; j < generations; j++) {
      int b;
      for (b = bottomCut; b < ROWS; b++) {
        advanceRow(b);
      }
    }
    glTranslatef(0.0, TILE_LEN, 0.0);
  }
}


/*
 * Draw the grid and tiles of the maze
 */
void createChessboard() {
  int coord[2];
  int i;
  int j;

  createGrid(ROWS, COLS);
  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLS; j++) {
      coord[0] = ORIGIN[0] + (TILE_LEN * j);
      coord[1] = ORIGIN[1] + (TILE_LEN * i);
      createTile(coord, alive_arr[i][j]);
    }
  }
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

  // Draw the button
  ButtonDraw(&Start);
}


/*
 * Display the game or start screen depending on the game state
 */
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  if (gameState == start) {
    drawStartScreen();
  }
  else if (gameState == play) {
    createChessboard();
    drawPlayer(103+xTranslation, 103+yTranslation, PLAYER_WIDTH);
  }
  glFlush();
}

int getYCoorFromTrans(int trans, int isTop)
{
  switch (trans) {
    case 7 ... 10:
      return 40;
    case 4 ... 6:
      return 39 + isTop;
    case -3 ... 3:
      return 39;
    case -6 ... -4:
      return 38 + isTop;
    case -10 ... -7:
      return 38;
    default:
      return 39;
  }
}

/*
 * Check keys and track player motion for generating new rows
 */
void processKeys(unsigned char key, int x, int y)
{
  int lxCoor = (xTransAbs - PLAYER_WIDTH/2) / TILE_LEN;
  int rxCoor = (xTransAbs + PLAYER_WIDTH/2) / TILE_LEN;
  int tyCoor = getYCoorFromTrans(yTranslation, 1);
  int byCoor = getYCoorFromTrans(yTranslation, 0);
  int xCoorFuture;
  int yCoorFuture;

  switch(key) {
    // ESC
    case 27:
      exit(0);
    case 32:
      // move forward one generation
      advanceGeneration();
      break;
    case 'w':
      // move up
      yCoorFuture = getYCoorFromTrans(yTranslation + SPEED, 1);
      if (alive_arr[yCoorFuture][lxCoor] == 1 && alive_arr[yCoorFuture][rxCoor] == 1) {
        glTranslatef(0.0, -(float) SPEED, 0.0);
        yTranslation += SPEED;
      }
      break;
    case 's':
      // move down
      yCoorFuture = getYCoorFromTrans(yTranslation - SPEED, 0);
      if (alive_arr[yCoorFuture][lxCoor] == 1 && alive_arr[yCoorFuture][rxCoor] == 1) {
        glTranslatef(0.0, (float) SPEED, 0.0);
        yTranslation -= SPEED;
      }
      break;
    case 'a':
      // move left
      xCoorFuture = (xTransAbs - (PLAYER_WIDTH/2) - SPEED) / TILE_LEN;
      if (alive_arr[tyCoor][xCoorFuture] == 1 && alive_arr[byCoor][xCoorFuture] == 1) {
        glTranslatef((float) SPEED, 0.0, 0.0);
        xTranslation -= SPEED;
        xTransAbs -= SPEED;
      }
      break;
    case 'd':
      // move right
      xCoorFuture = (xTransAbs + (PLAYER_WIDTH/2) + SPEED) / TILE_LEN;
      if (alive_arr[tyCoor][xCoorFuture] == 1 && alive_arr[byCoor][xCoorFuture] == 1) {
        glTranslatef(-(float) SPEED, 0.0, 0.0);
        xTranslation += SPEED;
        xTransAbs += SPEED;
      }
      break;
    default:
      break;
  }

  // Check if we've translated enough to create a new row
  if (yTranslation == TILE_LEN) {
    // Create new row on top
    createRow(0);

    // Reset translation count
    yTranslation = 0;
  }
  else if (yTranslation == (-TILE_LEN)) {
    // Create new row on bottom
    createRow(1);

    // Reset translation count
    yTranslation = 0;
  }
  printf("%d, %d\n", xTranslation, yTranslation);

  glutPostRedisplay();
}


/* 
 * Handle mouse press or release.
 */
void MouseButton(int button, int state, int x, int y)
{
  printf("Mouse pressed\n");
  // update the mouse position
  TheMouse.x = x;
  TheMouse.y = y;
  printf("%i\n", x);
  printf("%i\n", y);

  if (state == GLUT_DOWN) 
  {
    if ( !(TheMouse.lmb || TheMouse.mmb || TheMouse.rmb) ) {
      TheMouse.xpress = x;
      TheMouse.ypress = y;
    }

    // which button was pressed?
    switch(button) 
    {
    case GLUT_LEFT_BUTTON:
      TheMouse.lmb = 1;
      ButtonPress(&Start, x, y);
    case GLUT_MIDDLE_BUTTON:
      TheMouse.mmb = 1;
      break;
    case GLUT_RIGHT_BUTTON:
      TheMouse.rmb = 1;
      break;
    }
  }
  else 
  {
    // which button was released?
    switch(button) 
    {
    case GLUT_LEFT_BUTTON:
      TheMouse.lmb = 0;
      ButtonRelease(&Start, x, y);
      break;
    case GLUT_MIDDLE_BUTTON:
      TheMouse.mmb = 0;
      break;
    case GLUT_RIGHT_BUTTON:
      TheMouse.rmb = 0;
      break;
    }
  }
}


/*
 * Create the viewing window, initial maze state, and initial maze
 */
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowPosition(100,100);
  glutInitWindowSize(1000, 750);
  glutCreateWindow ("2D Procedural Maze");

  glutKeyboardFunc(processKeys);

  // Create initial maze
  int i;
  int j;
  int r;
  srand(time(NULL));
  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLS; j++) {
      r = rand() % 10;
      if (r == 5) {
        alive_arr[i][j] = 1;
      } 
    }
  }

  for (i = 0; i < 1000; i++) {
    advanceGeneration();
  }

  // Make sure the player start tile is not a wall
  alive_arr[39][40] = 1;

  // Check for mouse click
  glutMouseFunc(MouseButton);

  glutDisplayFunc(display);
  glutMainLoop();

  return 0;
}