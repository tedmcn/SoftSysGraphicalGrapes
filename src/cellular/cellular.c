/* Chessboard Drawing - All corrds from bottom left */

#include <stdio.h>
#include <GL/glut.h>

static const int TILE_LEN = 10;
static const int ORIGIN[2] = {10, 10};
static const int ROWS = 20;
static const int COLS = 20;
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

int getNeighborCount(row, col)
{
  int count = 0;
  count += alive_arr[row-1][col-1];
  count += alive_arr[row][col-1];
  count += alive_arr[row+1][col-1];
  count += alive_arr[row-1][col];
  count += alive_arr[row][col];
  count += alive_arr[row+1][col];
  count += alive_arr[row-1][col+1];
  count += alive_arr[row][col+1];
  count += alive_arr[row+1][col+1];
  return count;
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
    case 'd':
      // move forward one generation
      advanceGeneration();
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowPosition(100,100);
  glutInitWindowSize(300,300);
  glutCreateWindow ("Chessboard");

  glutKeyboardFunc(processKeys);

  glClearColor(0.0, 0.0, 0.0, 0.0);         // black background
  glMatrixMode(GL_PROJECTION);              // setup viewing projection
  glLoadIdentity();                           // start with identity matrix
  glOrtho(0.0, 250.0, 0.0, 250.0, -1.0, 1.0);   // setup a 10x10x2 viewing world

  glutDisplayFunc(display);
  glutMainLoop();

  return 0;
}