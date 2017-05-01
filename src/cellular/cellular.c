/* Chessboard Drawing - All corrds from bottom left */

#include <stdio.h>
#include <GL/glut.h>

static const int TILE_LEN = 10;
static const int ORIGIN[2] = {5, -10};
static const int ROWS = 20;
static const int COLS = 20;
int yTranslation = 0;
int alive_arr[20][20] = {  
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

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

void createTile(int coord[], int alive) {
  // Fill in grid square
  if (alive) {
    glColor3f(0.0, 0.0, 1.0);
  } else {
    glColor3f(0.0, 0.0, 0.0);
  }
  glBegin(GL_POLYGON);
  glVertex2f(coord[0], coord[1]);
  glVertex2f(coord[0] + TILE_LEN, coord[1]);
  glVertex2f(coord[0] + TILE_LEN, coord[1] + TILE_LEN);
  glVertex2f(coord[0], coord[1] + TILE_LEN);
  glEnd();
}

int getNeighborCount(int row, int col)
{
  int count = 0;
  count += alive_arr[row-1][col-1];
  count += alive_arr[row][col-1];
  count += alive_arr[row+1][col-1];
  count += alive_arr[row-1][col];
  count += alive_arr[row+1][col];
  count += alive_arr[row-1][col+1];
  count += alive_arr[row][col+1];
  count += alive_arr[row+1][col+1];
  return count;
}


/*
 * Fill in the cells in the top or bottom row
 * 
 * Input: direction - 0 if top, 1 if bottom
 */
void advanceRow(int direction) {
  int row;
  if (direction == 0) {
    row = 0;
  }
  else {
    row = 19;
  }
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
 * Input: direction - 0 if top, 1 if bottom
 */
void createRow(int direction)
{
  // If top: shift all rows down one, generate new top row
  if (direction == 1) {
    int i;
    for (i = 20; i > 0; i--) {
      int a;
      for (a = 0; a < COLS; a++) {
        alive_arr[i][a] = alive_arr[i-1][a];
      }
    }
    int x;
    for (x = 0; x < COLS; x++) {
      alive_arr[0][x] = 0;
    }
    advanceRow(0);
    glTranslatef(0.0, -TILE_LEN, 0.0);
  }
  // If bottom: shift all rows up one, generate new bottom row
  else {
    int j;
    for (j = 0; j < 20; j++) {
      int b;
      for (b = 0; b < COLS; b++) {
        alive_arr[j][b] = alive_arr[j+1][b];
      }
    }
    int y;
    for (y = 0; y < COLS; y++) {
      alive_arr[19][y] = 0;
    }
    advanceRow(1);
    glTranslatef(0.0, TILE_LEN, 0.0);
  }
}


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

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  createChessboard();
  glFlush();
}

void processKeys(unsigned char key, int x, int y)
{
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
      glTranslatef(0.0, -1.0, 0.0);
      yTranslation++;
      printf("%i\n", yTranslation);
      break;
    case 's':
      // move down
      glTranslatef(0.0, 1.0, 0.0);
      yTranslation--;
      printf("%i\n", yTranslation);
      break;
    case 'a':
      // move left
      glTranslatef(1.0, 0.0, 0.0);
      break;
    case 'd':
      // move right
      glTranslatef(-1.0, 0.0, 0.0);
      break;
    default:
      break;
  }

  // Check if we've translated enough to create a new row
  if (yTranslation == TILE_LEN) {
    // Create new row on top
    printf("Create top row.\n");
    createRow(0);

    // Reset translation count
    yTranslation = 0;
  }
  else if (yTranslation == (-TILE_LEN)) {
    // Create new row on bottom
    printf("Create bottom row.\n");
    createRow(1);

    // Reset translation count
    yTranslation = 0;
  }

  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowPosition(100,100);
  glutInitWindowSize(1000, 750);
  glutCreateWindow ("2D Procedural Maze");

  glutKeyboardFunc(processKeys);

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Set viewing world with one top and bottom row outside of view
  glOrtho(0.0, 210.0, 0.0, 180.0, -1.0, 1.0);

  // Create initial maze
  int i;
  for (i = 0; i < 40; i++) {
    advanceGeneration();
  }

  glutDisplayFunc(display);
  glutMainLoop();

  return 0;
}