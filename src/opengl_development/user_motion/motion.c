/* Chessboard Drawing - All corrds from bottom left */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

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

void createChessboard(int tile_len, int origin[]) {
  // Create grid
  createGrid(9, 9, tile_len, origin);

  // Fill in tiles in chessboard pattern
  int coord[2];
  int everyother = 0;
  int i;
  int j;
  // Rows
  for (i = 0; i < 9; i++) {
    // Cols
    for (j = 0; j < 9; j++) {
      coord[0] = origin[0] + (tile_len * j);
      coord[1] = origin[1] + (tile_len * i);
      if (everyother % 2 == 0) {
        createTile(coord, tile_len);
      }
      everyother++;
    }
  }
}

void display(void)
{
  glClear( GL_COLOR_BUFFER_BIT);
  int origin[2] = {10, 10};
  createChessboard(25, origin);
  glFlush();
}


void processKeys(unsigned char key, int x, int y) {
  switch(key) {
    // ESC
    case 27:
      exit(0);
    case 'w':
      // move up
      glTranslatef(0.0, 1.0, 0.0);
      break;
    case 's':
      // move down
      glTranslatef(0.0, -1.0, 0.0);
      break;
    case 'a':
      // move left
      glTranslatef(-1.0, 0.0, 0.0);
      break;
    case 'd':
      // move right
      glTranslatef(1.0, 0.0, 0.0);
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
  printf("Press escape to quit.\n");
  printf("Use wasd control to move.\n");

  glutKeyboardFunc(processKeys);

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 250.0, 0.0, 250.0, -1.0, 1.0);
  glutDisplayFunc(display);
  glutMainLoop();

  return 0;
}