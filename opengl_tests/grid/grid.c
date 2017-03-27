/* 2D Shape Library */

#include <stdio.h>
#include <GL/glut.h>

void createGrid(int rows, int cols, int tile_len, int origin[]) {
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINES);
  int r;
  int c;
  // Rows
  for (int r = 0; r < rows + 1; r++) {
    glVertex2f(origin[0], origin[1] + (tile_len * r));
    glVertex2f(origin[0] + (cols * tile_len), origin[1] + (tile_len * r));
  }
  // Cols
  for (int c = 0; c < cols + 1; c++) {
    glVertex2f(origin[0] + (tile_len * c), origin[1]);
    glVertex2f(origin[0] + (tile_len * c), origin[1] + (rows * tile_len));
  }
  glEnd();
}

void display(void)
{
  glClear( GL_COLOR_BUFFER_BIT);
  int origin[2] = {5, 5};
  createGrid(5, 7, 5, origin);
  glFlush();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowPosition(100,100);
  glutInitWindowSize(300,300);
  glutCreateWindow ("square");

  glClearColor(0.0, 0.0, 0.0, 0.0);         // black background
  glMatrixMode(GL_PROJECTION);              // setup viewing projection
  glLoadIdentity();                           // start with identity matrix
  glOrtho(0.0, 50.0, 0.0, 50.0, -1.0, 1.0);   // setup a 10x10x2 viewing world

  glutDisplayFunc(display);
  glutMainLoop();

  return 0;
}