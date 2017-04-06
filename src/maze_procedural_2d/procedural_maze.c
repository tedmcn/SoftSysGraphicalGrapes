/* Procedural 2D maze with user motion
 * New rows are drawn when user passes edge
 */

#include "maze_api.h"

// Procedural Parameters
float frequency = 0.5;
float separation = 0.5;

// Set the side length of the initial board
int board_size = 10;
int tile_size = 25;
// Store current board params to allow adding rows and columns
int current_rows = 10;
int current_cols = 10;
int origin[2] = {10, 10};

int up_tr = 0;
int up_max = 0;

// List of tiles
int coord[][];

/*
 * Generate a new row of the maze using procedural parameters
 * 
 * INPUT: direction - 0 up, 1, down, 2 left, 3 right
 *        frequency - 0-1.0 percentage of tiles filled per row,
 *        separation - 0-1.0 factor of space between tiles  
 */
void generateRow(float frequency, float separation) {
  // Update tile list
  y = current_rows;

  current_rows++;
}


/*
 * Draw the OpenGL display
 */
void display(void)
{
  glClear( GL_COLOR_BUFFER_BIT );
  drawGrid(board_size, board_size, tile_size, origin);
  drawTiles(coord, tile_size, origin);

  glFlush();
}


/*
 * WASD User Motion
 */
void processKeys(unsigned char key, int x, int y) {
  // Check keys
  switch(key) {
    // ESC
    case 27:
      exit(0);
    case 'w':
      // move up
      glTranslatef(0.0, -1.0, 0.0);
      up_tr++;
      break;
    case 's':
      // move down
      glTranslatef(0.0, 1.0, 0.0);
      up_tr--;
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

  // Check generate trigger
  if (up_tr == up_max + tile_size) {
    up_max += tile_size;
    generateRow(frequency, separation);
  }

  // Update view
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