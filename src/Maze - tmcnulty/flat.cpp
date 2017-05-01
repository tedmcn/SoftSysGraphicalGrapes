/*Ted McNulty
 *2/27/17
 *ENGR 2535


 *Main entry point for program
 *Runs a simulation of a ball falling onto a flat plane with a 
 *little bounce-back
*/

#include <GL/glut.h>
#include <stdlib.h> 
#include <stdio.h>

#include "gameobject.h"
#include "vectorobject.h"
#include "physics.h"
#include "sphereobject.h"
#include "planeobject.h"
#include "playerobject.h"


//Create the sphere and plane globally since they are needed 
// throughout the whole simulation
float plane_normal[]={0,1,0};
float plane_scale[]={100,.1,100};
float plane_rotate[]={0,0,0};
Planeobject plane=Planeobject(plane_normal, plane_scale, plane_rotate);
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
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0); 
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

    //Draw in red
    glColor3d(1,0,0);

    //Draw the sphere

    //Draw in blue
    glColor3d(0,0,0.2); 

    //Draw the plane
    plane.draw();
 
    //Apply the time update
    p.update();

    //Send the new image to the buffer
    glutSwapBuffers(); 

    //Check player input for next frame
    player.checkForInput();

    //Execute the input and make sure you are not clipping into a wall
    //Apply 
    player.handel(p);

    //Apply all the user inputs in the buffer
    int i;
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
    player = Playerobject();
    player.setP(player_starting_coords);
    player.setD(player_starting_direction);



    //Start opengl, Create the window
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); 
 
    //Define the location of the objects
    GLfloat sphere_coordinates[] = {0,10,0};
    GLfloat plane_coordinates[] = {0,0,0};

    //Put the sphere and plane in the correct position
    plane.setP(plane_coordinates);

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