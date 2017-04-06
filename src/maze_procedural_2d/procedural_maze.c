/* Chessboard Drawing - All corrds from bottom left */


/*
 * Generate a new row of the maze using procedural parameters
 * 
 * INPUT: frequency - 0-1.0 percentage of tiles filled per row,
 *        separation - 0-1.0 factor of space between tiles  
 */
void generateRow(float frequency, float separation) {

}


/*
 *
 */
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