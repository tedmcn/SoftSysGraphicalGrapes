

This project includes several interactive implementations of procedural terrain generation algorithms in C and OpenGL.

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

### Interactive Grass Field

**Overview**

This interactive model allows users to change the parameters of a procedural grass generation algorithm and observe the effects on a drawn field of grass blades. The algorithm generates each blade in the field based on height, width, and distribution sliders, and the position of each blade is determined using the Box-Muller algorithm, allowing a variety of distributions from gaussian to realistic clusters.

Play the video below to see a demonstration of the interactive grass terrain.

[![Loading Interactive Grass Demo ...](https://img.youtube.com/vi/85TKIOZwD2o/0.jpg)](http://www.youtube.com/watch?v=85TKIOZwD2o "Interactive Grass Demo")

**Implementation**

Pictures / LL / Box-Muller

![Loading Grass Image ...](https://github.com/tedmcn/SoftSysGraphicalGrapes/blob/gh-pages/images/grass_basic.png)

![Loading Grass Image ...](https://github.com/tedmcn/SoftSysGraphicalGrapes/blob/gh-pages/images/grass_realistic.png)

![Loading Grass Image ...](https://github.com/tedmcn/SoftSysGraphicalGrapes/blob/gh-pages/images/grass_gaussian.png)

![Loading Grass Image ...](https://github.com/tedmcn/SoftSysGraphicalGrapes/blob/gh-pages/images/grass_clustered.png)


## Summary

What we did


## Project Information

**Project Authors**

Haozheng Du, Kathryn Hite, Ted McNulty, Bill Wong

**Project License**

This project is licensed using the MIT License.  See the [README](https://github.com/tedmcn/SoftSysGraphicalGrapes/blob/master/README.md) for more details.
