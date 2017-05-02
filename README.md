# Software Systems Team Graphical Grapes: Procedural Graphics Generation

## Description

This project includes several interactive implementations of procedural terrain generation algorithms in C and OpenGL.

**2D Infinite Maze Game**

Attempt to escape this addicting maze at your own risk.  The game continually generates new rows as the player moves up and down the maze, showing how a seemingly infinite map can be created and stored with a small amount of memory.  Each new portion of the maze is created using the cellular automata maze generation model, which determines whether or not to fill cells based on the status of the surrounding cells.  User motion is provided through wasd keyboard control.

**3D Maze Game**

Based on the work in the 2D game mentioned above, this 3D maze allows a player to explore a cellular automata in 3D space in order to achieve better understanding of how CA's work and operate step by step. The player can walk around the grid and press 'k' to advance the CA one step, he can also press the space bar to jump in order to get a better top-down view of the CA. Careful though; if a cell turns on while standing on top of it the player will be trapped inside the cell.

**Interactive Grass Field Generation**

This interactive model allows users to change the parameters of a procedural grass generation algorithm and observe the effects on a drawn field of grass blades.  The algorithm generates each blade in the field based on height, width, and distribution sliders, and the position of each blade is determined using the Box-Muller algorithm, allowing a variety of distributions from gaussian to realistic clusters.  

**Project Website**

For more background, demos, and implementation details, check out the project site [here](https://tedmcn.github.io/SoftSysGraphicalGrapes/).


## Authors

Haozheng Du, Kathryn Hite, Ted McNulty, Bill Wong


## Getting Started

### Installing OpenGL

To install the background libraries for OpenGL in Linux, run the following command:

```
$ sudo apt-get install freeglut3-dev freeglut3
```

### Compilation

Each of the following directories in src contain an individual interactive game:

* `src/2d_procedural_maze`: A 2D infinite maze with wasd player control.
* `src/3d_procedural_maze`: A 3D, exporable maze constructed with a Cellular Automata.
* `src/interactive_grass_generation`: A terrain generation example with interactive parameters.


To build any of these games, run 

```
$ make all
```

in the corresponding directory.

There is also a `opengl_development` directory with a variety of mini development projects in opengl.  These can be used to provide resources for future implementations.


## Usage

Use the appropriate command below to run each game in its directory.

* For 2d_procedural_maze: `$ ./2d_maze`
* For 3d_procedural_maze: `$ ./3d_maze`
* For interactive_grass_generation: `$ ./grass`

Each of the project folders also contains the source code for the game, which is broken out into various api file that can be used for other implementations.  For example, the drawing functions for each maze as well as the sets of grass blades are separated into api files and can be imported into other applications.


## License

MIT License

Copyright (c) 2017 Haozheng Du, Kathryn Hite, Ted McNulty, Bill Wong

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
