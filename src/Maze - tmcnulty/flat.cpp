/*Ted McNulty
 *2/27/17
 *ENGR 2535


 *Main entry point for program
 *Runs a simulation of a ball falling onto a flat plane with a little bounce-back
*/

#include <GL/glut.h>
#include <stdlib.h> 
#include <stdio.h>

#include "gameobject.h"
#include "vectorobject.h"
#include "physics.h"
#include "sphereobject.h"
#include "planeobject.h"


//Create the sphere and plane globally since they are needed throughout the whole simulation
    Sphereobject s= Sphereobject(1);
    float plane_normal[]={0,1,0};
    float plane_scale[]={10,.1,10};
    float plane_rotate[]={0,0,0};
    Planeobject plane=Planeobject(plane_normal, plane_scale, plane_rotate);
    Physics p;


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
 

//This function is used on every frame, it is used to draw the 3d environment onto the screen
static void display(void)
{ 
    //Clear the previous image
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    //Reset the viewport to the standard camera angel
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Set the camera
    gluLookAt(14,15,15,0.0,0.0,0.0,0.0,1.0,0.0);

    //Draw in red
    glColor3d(1,0,0);

    //Draw the sphere
    s.draw();

    //Draw in blue
    glColor3d(0,0,0.2); 

    //Draw the plane
    plane.draw();
 
    //Apply the time update
    p.update();

    //Update the sphere object
    s.apply(p,plane);


    //Send the new image to the buffer
    glutSwapBuffers(); 
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
   
    //Start opengl, Create the window
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); 
 
    //Define the location of the objects
    GLfloat sphere_coordinates[] = {0,10,0};
    GLfloat plane_coordinates[] = {0,0,0};

    //Put the sphere and plane in the correct position
    s.setP(sphere_coordinates);
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

    //Empty void function
    glutMainLoop(); 
 
    return EXIT_SUCCESS;
}