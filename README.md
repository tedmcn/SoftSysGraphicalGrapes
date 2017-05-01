

This project includes interactive implementations of procedural terrain generation algorithms in C and OpenGL.

## Background

### OpenGL

What is opengl

### Procedural Generation and Cellular Automata

What is procedural generation / CAs


## Implementation and Results

### Interactive 2D Maze Game

**Overview**

The 2d infinite maze game continually generates new rows as the player moves up and down the maze, showing how a seemingly infinite map can be created and stored with a small amount of memory. Each new portion of the maze is created using the cellular automata maze generation model, which determines whether or not to fill cells based on the status of the surrounding cells. User motion is provided through wasd keyboard control.

Play the video below to see a demonstration of the full game.

[![Loading Maze Game Demo ...](https://img.youtube.com/vi/LWTZEe8x_QY/0.jpg)](https://www.youtube.com/watch?v=LWTZEe8x_QY "2D Infinite Maze Demo")

**Implementation**

In order to create the illusion of an infinite maze, the player viewing window is focused in on a specific portion of the much larger maze.  Every time the player moves up or down a cell, the entire maze moves down, generating a new randomly seeded row at the top or bottom.  The player view then moves to prevent the shift of the maze from being visible as the new row pushes the old up or down.  Every row above or below the viewing window is also run through many generations of the cellular automota to ensure that the new row causes as much of the maze to fill in as possible.

The video below shows the zoomed out viewing frame with the full maze shifting and regenerating as the user moves up and down.

[![Loading Maze Generation Demo ...](https://img.youtube.com/vi/PByjrMZ_-Mo/0.jpg)](http://www.youtube.com/watch?v=PByjrMZ_-Mo "Maze Generation with Player Motion")

### Interactive Grass Generation

**Overview**

This interactive model allows users to change the parameters of a procedural grass generation algorithm and observe the effects on a drawn field of grass blades. The algorithm generates each blade in the field based on height, width, and distribution sliders, and the position of each blade is determined using the Box-Muller algorithm, allowing a variety of distributions from gaussian to realistic clusters.

Play the video below to see a demonstration of the interactive grass terrain.

[![Loading Interactive Grass Demo ...](https://img.youtube.com/vi/85TKIOZwD2o/0.jpg)](http://www.youtube.com/watch?v=85TKIOZwD2o "Interactive Grass Demo")

**Implementation**

To create many blades of grass efficiently, our algorithm determines a target number of grass blades based on a sparseness parameter and creates a linked list where each node stores a list of characteristics for a single blade.  Each of these blades can then be rendered as many times as necessary until new blades with different parameters are desired.  In the simplest form, each blade is drawn as a cone with a width, height, color, and position.  As shown in the image below, a list of these cones can quickly be changed from a few simple drawings to a large field of semi-realistic grass blades.

[![Loading Grass Image ...](https://github.com/tedmcn/SoftSysGraphicalGrapes/blob/gh-pages/images/grass_basic.png)](https://github.com/tedmcn/SoftSysGraphicalGrapes/blob/gh-pages/images/grass_basic.png)

The previous drawings both show blades drawn evenly across the base plane.  In order to create a realistic position distribution for the grass, we use the [Box-Muller transform](https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform).  This transform samples pseudo-random numbers to generate normally distributed pairs of coordinates.  By changing the mean, standard deviation, and number of blades in this normal distribution, the scene can be drawn in a cluster pattern that closely mimics the natural clustering of grass in the real world as shown below.

[![Loading Grass Image ...](https://github.com/tedmcn/SoftSysGraphicalGrapes/blob/gh-pages/images/grass_distribution.png)](https://github.com/tedmcn/SoftSysGraphicalGrapes/blob/gh-pages/images/grass_basic.png)

Overall, this model allows users to explore the ways that procedural algorithms can convert simple, geometric shapes into scenes that mimic much more complex real world phenomena. 


## Summary

In these two interactive graphics applications, we show two varieties of procedural graphics generation.  The infinite maze appears to be endless terrain to the user while taking only finite memory as it regenerates using cellular automata.  We also show an implementation of creating an appearance of realism through terrain variety parameters in both the appearance and distrubution algorithms used to draw the grass field.

Conclusion here


## Project Information

**Project Authors**

Haozheng Du, Kathryn Hite, Ted McNulty, Bill Wong

**Project License**

This project is licensed using the MIT License.  See the [README](https://github.com/tedmcn/SoftSysGraphicalGrapes/blob/master/README.md) for more details.
