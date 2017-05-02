/*Ted McNulty
 *2/27/17
 *ENGR 2535


 *Main entry point for program
 *Runs a simulation of a ball falling onto a flat plane with a 
 *little bounce-back
*/

#include <GL/glut.h>
#include <time.h>
#include <stdlib.h> 
#include <stdio.h>

#include "gameobject.h"
#include "vectorobject.h"
#include "physics.h"
#include "sphereobject.h"
#include "planeobject.h"
#include "playerobject.h"


/*
Bill's Work
*/

static const int ROWS = 20;
static const int COLS = 20;
static const int SIZE = 30;
int alive_arr[ROWS][COLS] = {  
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int getNeighborCount(int row, int col)
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


/*
    Ted's Work
*/

void drawMaze(){
    float cube_n[]={0,1,0};
    float cube_s[]={SIZE,SIZE,SIZE};
    float floor_s[]={cube_s[0],0.1,cube_s[2]};
    float cube_r[]={0,0,0};
    int i;
    int j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if(alive_arr[i][j]==1){
                Planeobject p = Planeobject(cube_n, cube_s, cube_r);
                float cube_p[]= {i-(1/2)*SIZE, 0, j-(1/2)*SIZE};
                p.setP(cube_p);
                glColor3d(0,0,0.3);
                p.draw();
            }else{
                Planeobject p = Planeobject(cube_n, floor_s, cube_r);
                float cube_p[]= {i-(1/2)*SIZE, 0, j-(1/2)*SIZE};
                p.setP(cube_p);
                glColor3d(0,0.2,0);
                p.draw();
            }
        }
    }
}



Physics p;

//Player object which will work as the camera and take user input
float player_starting_coords[]={0,10,1};
float player_starting_direction[]={1,0,0};
Playerobject player;

bool inputBuffer[256];

//Used for resizing the window if it changes
//
// width:  new width of window
// height: new height of window

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height; 
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 1000.0); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
} 
 

//This function is used on every frame, it is used to draw the 
// 3d environment onto the screen
static void display(void)
{ 
    //Clear the previous image
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    //Reset the viewport to the standard camera angel
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Set the camera
    //First set of 3 is coords of eye, second set of 3 is where it is looking, 
    // 3rd is normal
    player.look();

    glColor3d(0,0.2,0);
    drawMaze();

    //Apply the time update
    p.update();

    //Send the new image to the buffer
    glutSwapBuffers(); 

    //Check player input for next frame
    player.checkForInput();


    //Save the player position
    float old_p[] = {player.getP()[0], player.getP()[1],player.getP()[2]};

    //Execute the input and make sure you are not clipping into a wall
    //Apply 
    player.handel(p);

    //Check to see if the player walked into the walls
    float new_p[] = {player.getP()[0], player.getP()[1],player.getP()[2]};

    int i;
    int j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if((i*SIZE)-(0.5*SIZE)-5 < new_p[0] && new_p[0]<(i*SIZE)+(0.5*SIZE)+5){
                if(j*SIZE-(0.5*SIZE)-5 < new_p[2] && new_p[2]<(j*SIZE)+(0.5*SIZE)+5){
                    if(alive_arr[i][j]==1){
                        printf("%i - %i | %f - %f \n", i,j, player.getP()[0], player.getP()[2]);
                        player.setP(old_p);
                    }
                } 
            }
        }
    }


    //Apply all the user inputs in the buffer
    for(i=0;i<256;i++){
        if(inputBuffer[i]==true){
            switch(i){
                case 'w':
                case 'a':
                case 's':
                case 'd':
                    player.move(i);
                    break;
                case 'r':
                    //Command to switch cell the user is standing on
                    break;
                case ' ':
                    player.jump();
                    break;
                case 'j':
                    player.rotateLeft();
                    break;
                case 'l':
                    player.rotateRight();
                    break;
                case 'k':
                    advanceGeneration();
                    inputBuffer['k']=false;
                    break;
                case 27:
                    printf("\nUser exited\n");
                    exit(0);
            }
        }
    }
} 

//When a player presses a key add it to the buffer
void keyboard_input(unsigned char key, int x, int y){
    inputBuffer[key]=true;
}
//When the player releases the key remove it from the buffer
void keyboard_up(unsigned char key, int x, int y){
    inputBuffer[key]=false;
}

//Create lights 
    const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f }; 
     
    const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[] = { 100.0f }; 
 
/* Program entry point */
 
int main(int argc, char *argv[])
{

    srand(time(NULL));
    int x;
    for(x=0;x<50;x++){
        alive_arr[rand()%20][rand()%20]=1;
    }

    player = Playerobject();
    player.setP(player_starting_coords);
    player.setD(player_starting_direction);





    //Start opengl, Create the window
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); 
 

    //Create the window
    glutCreateWindow("Physics"); 
 
    //Account for resizing the window
    glutReshapeFunc(resize);
    glutDisplayFunc(display); 
 
    //Background color is a pale yellow
    glClearColor(1,1,.85,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); 
 
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); 
 
    //GL light and shading helpers
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING); 
 
    //Set the lights
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); 
 
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess); 
 
    //When the program is idle run display
    glutIdleFunc(display);

    //Tell OpenGL what keyboard functions we need to listen for
    glutKeyboardFunc(keyboard_input);
    glutKeyboardUpFunc(keyboard_up);

    //Empty void function
    glutMainLoop(); 
 
    return EXIT_SUCCESS;
}