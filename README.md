# SoftSys Team Graphical Grapes: Procedural Graphics Generation

## Description

This project includes several interactive implementations of procedural terrain generation algorithms in C and OpenGL.

**2D Inifinite Maze Game**

Short Description Here

**Interactive Grass Field Generation**

Short Description Here

**3D Infinite Maze Game**

Short Description here

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

Each of the three directories in src contain an individual interactive game:

* `src/2d_procedural_maze`: A 2D infinite maze with wasd player control.
* `src/interactive_grass_generation`: A terrain generation example with interactive parameters.
* `src/3d_procedural_maze`: A 3D infinite maze with player mechanics.

To build any of these games, run 

```
$ make all
```

in the corresponding directory.


## Usage

Use the appropriate command below to run each game in its directory.

* For 2d_procedural_maze: `$ ./2d_maze`
* For interactive_grass_generation: `$ ./grass`
* For 3d_procedural_maze: `$ ./3d_maze`

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
