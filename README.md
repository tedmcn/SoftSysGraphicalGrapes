This project includes interactive implementations of procedural terrain generation algorithms in C and OpenGL.  

* The first is a 2D infinite maze game.
* The second is an interactive grass generation display.  

This website provides demos and implementation details for each.  To play the games or use the APIs that we have created, use the github link in the header and follow the instructions provided in the README.

## Background

For both of the implementations described below, we use OpenGL to create the graphics and user interface.  Procedural generation algorithms and cellular automata are both incorporated as well.  The following section provides a brief background for each of these concepts.

### OpenGL

OpenGL is a cross-platform API used to render 2D and 3D graphics.  We utilized OpenGL to create the UI and display the generated maze and grass blades.  There are examples of primitive drawing functions, camera view setups, user interfaces, and lighting methods in our opengl_development directory for reference.

### Procedural Generation and Cellular Automata

Procedural generation in computer graphics means to generate textures and models algorithmically and potentially with random components instead of manually. Modern games have been using procedural generation to create complex content, and we chose to explore terrain generation as a specific implementation of this concept. 

Cellular Automaton (CA) is a discrete model that consists of a set of cells, where each cell has its own assigned state. A new generation is created when each cell changes its state based on its current state and the states of its neighbours following pre-defined rules. We implemented CA as our algorithm for maze generation and this enables the appearance of infinite procedural generation within a finite array of cells based our given set of rules.


## Implementation and Results

### Interactive 2D Maze Game

**Overview**

The 2d infinite maze game continually generates new rows as the player moves up and down the maze, showing how a seemingly infinite map can be created and stored with a small amount of memory. Each new portion of the maze is created using the cellular automata maze generation model, which determines whether or not to fill cells based on the status of the surrounding cells. User motion is provided through wasd keyboard control.

Play the video below to see a demonstration of the full game.

[![Loading Maze Game Demo ...](https://img.youtube.com/vi/LWTZEe8x_QY/0.jpg)](https://www.youtube.com/watch?v=LWTZEe8x_QY "2D Infinite Maze Demo")

**Implementation**

In order to create the illusion of an infinite maze, the player viewing window is focused in on a specific portion of the much larger maze.  Every time the player moves up or down a cell, the entire maze moves down, generating a new randomly seeded row at the top or bottom.  The player view then moves to prevent the shift of the maze from being visible as the new row pushes the old up or down.  Every row above or below the viewing window is also run through many generations of the cellular automata to ensure that the new row causes as much of the maze to fill in as possible.

The cellular automata rules we used is the ["Maze"](http://www.conwaylife.com/w/index.php?title=Maze) ruleset.  Cells are born if they have 3 neighbors, and survive if they have 1-5 neighbors.

To limit movement of the player, we had to detect if the player would walk into a wall with every keypress.  To do this, we keep track of the x and y position of the center of the player at all times.  Using these positions and the width of the player, we can calculate which cells the player is currently occupying and which cells they would occupy after a movement.  If a movement keypress causes the player to occupy a cell that is a wall, we block the movement.

The video below shows the zoomed out viewing frame with the full maze shifting and regenerating as the user moves up and down.

[![Loading Maze Generation Demo ...](https://img.youtube.com/vi/PByjrMZ_-Mo/0.jpg)](http://www.youtube.com/watch?v=PByjrMZ_-Mo "Maze Generation with Player Motion")

### 3D Maze Game

**Overview**

This game which is based on the work done in the 2D version, aims to provide a tool for students to better understand and visualize Cellular Automata. The original goal of this 3D version was to create a game in which a maze consistantly is generated infront of the player regardless of how far from the starting point they are. However, a fundamental issue with this is that when the CA would generate a new row the tile the player is standing on may need to be swapped, and in the case where that happens the player gets stuck in a wall with no way out. To remedy this problem, we changed the controls of the game such that they player chooses when the CA will advance by pressing the 'k' key. This way, the user has total control over how fast the CA adavances so that they can fully understand one step before moving onto the next.

Play the video below to see a demonstration of the full game.
[![Loading Maze Game Demo ...](https://img.youtu.be/b5bxTZT8aWk/0.jpg)](https://youtu.be/b5bxTZT8aWk "3D Maze Demo")

**Controls**

W- Forward

S- Backward

A- Strafe Left

D- Strafe Right

J- Look Left

L- Look Right

k- Advance the CA

" "- Jump


**Implementation**

There are a few steps in order to create this 3D version of the maze game. First, we have to correct the camera's. This is accomplished by creating a Player absraction which can hold dedicated information about the player such as his position, his acceleration, and other variables needed for movement. Typically in OpenGL you would set the camera's position and where it was looking with:
``glutLookAt()``
However, this function takes in 9 paramerers such as the player's normal vector, the player's position and the player's direction. We wrapped this in a look() function which loads the needed parameters from the player object's variables. This helps us achieve a viewport which is accurately being changed as the player moves the camera. Furthermore, it creates a convenient, organized way for us to handel the many variables we will need.

The second step is to map the CA to a constant location within the OpenGL enviornment. In other words, we want the top-left most edge of the CA to be at 0,0 and we want it to always be at 0,0 regareless of whether the user moved or if that tile has changed. This is accomplished directly drawing the maze from the CA every frame. It is typical OpenGL convention to save, in structures, objects that you need to draw frame after frame while only modifying their values every frame. However, in this situation that would require a lot of overhead as each wall (tile of the CA) would need to have their position, scale, rotation, and normal vector saved. In order to avoid saving all this information we draw each tile seperately every frame (as it doesn't slow us down noticeably). 

Lastly, we need to implement user controls as well as collision detection to make sure that the player doesn't walking into the walls of the maze. OpenGL provides some handy tools to handel user input:
`` glutKeyboardFunc(keyboard_input);glutKeyboardUpFunc(keyboard_up);``
In order to allow a user to input multiple commands at once we add each pressed key to a buffer (This is done by glutKeyboardFunc). Once a key is released it is removed from the buffer by glutKeyboardUpFunc. Every frame, the program will check the buffer and apply the command of every key in the buffer which in turn allows a user to run foward and jump at the same time, or rotate the camera left and walk backwards. If this were implemented in another way, the user would need to stop walking forward (pressing w) in order to jump (press " ").

### Interactive Grass Generation

**Overview**

This interactive model allows users to change the parameters of a procedural grass generation algorithm and observe the effects on a drawn field of grass blades. The algorithm generates each blade in the field based on height, width, and distribution sliders, and the position of each blade is determined using the Box-Muller algorithm, allowing a variety of distributions from gaussian to realistic clusters.

Play the video below to see a demonstration of the interactive grass terrain.

[![Loading Interactive Grass Demo ...](https://img.youtube.com/vi/85TKIOZwD2o/0.jpg)](http://www.youtube.com/watch?v=85TKIOZwD2o "Interactive Grass Demo")

**Implementation**

To create many blades of grass efficiently, our algorithm determines a target number of grass blades based on a sparseness parameter and creates a linked list where each node stores a list of characteristics for a single blade.  Each of these blades can then be rendered as many times as necessary until new blades with different parameters are desired.  In the simplest form, each blade is drawn as a cone with a width, height, color, and position.  As shown in the image below, a list of these cones can quickly be changed from a few simple drawings to a large field of semi-realistic grass blades.

[![Loading Grass Image ...](https://github.com/tedmcn/SoftSysGraphicalGrapes/raw/gh-pages/images/grass_detail.png)](https://github.com/tedmcn/SoftSysGraphicalGrapes/blob/gh-pages/images/grass_detail.png)

The previous drawings both show blades drawn evenly across the base plane.  In order to create a realistic position distribution for the grass, we use the [Box-Muller transform](https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform).  This transform samples pseudo-random numbers to generate normally distributed pairs of coordinates.  By changing the mean, standard deviation, and number of blades in this normal distribution, the scene can be drawn in a cluster pattern that closely mimics the natural clustering of grass in the real world as shown below.

[![Loading Grass Image ...](https://github.com/tedmcn/SoftSysGraphicalGrapes/raw/gh-pages/images/grass_distribution.png)](https://github.com/tedmcn/SoftSysGraphicalGrapes/blob/gh-pages/images/grass_distribution.png)

Overall, this model allows users to explore the ways that procedural algorithms can convert simple, geometric shapes into scenes that mimic much more complex real world phenomena. 


## Summary

In these two interactive graphics applications, we show two varieties of procedural graphics generation.  The infinite maze appears to be endless terrain to the user while taking only finite memory as it regenerates using cellular automata.  We also show an implementation of creating an appearance of realism through terrain variety parameters in both the appearance and distribution algorithms used to draw the grass field.

Both of the interactive examples as well as the drawing apis that we have created can be used to better understand procedural graphics generation and create new projects and implementations.


## Project Information

**Project Authors**

Haozheng Du, Kathryn Hite, Ted McNulty, Bill Wong

**Project License**

This project is licensed using the MIT License.  See the [README](https://github.com/tedmcn/SoftSysGraphicalGrapes/blob/master/README.md) for more details.
