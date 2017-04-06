/* Procedural 2D maze with user motion
 * New rows are drawn when user passes edge
 */

#include "maze_api.h"

// Set the side length of the initial board
int board_size = 10;
int tile_size = 25;
// Store current board params to allow adding rows and columns
int current_rows = 10;
int current_cols = 10;
int origin[2] = {10, 10};

/*
 * Generate a new row of the maze using procedural parameters
 * 
 * INPUT: frequency - 0-1.0 percentage of tiles filled per row,
 *        separation - 0-1.0 factor of space between tiles  
 */
void generateRow(float frequency, float separation) {
  // TODO
}


/*
 * Draw the OpenGL display
 */
void display(void)
{
  glClear( GL_COLOR_BUFFER_BIT );
  drawGrid(board_size, board_size, tile_size, origin);
  int coord[] = {2, 2};
  drawTile(coord, tile_size, origin);
  glFlush();
}


/*
 * WASD User Motion
 */
void processKeys(unsigned char key, int x, int y) {
  switch(key) {
    // ESC
    case 27:
      exit(0);
    case 'w':
      // move up
      glTranslatef(0.0, -1.0, 0.0);
      break;
    case 's':
      // move down
      glTranslatef(0.0, 1.0, 0.0);
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
  glutPostRedisplay();
}


int main(int argc, char **argv)
{
  // Init OpenGL
  glutInit(&argc, argv);
  glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

  // Init viewing window
  glutInitWindowPosition(100,100);
  glutInitWindowSize(500,500);
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