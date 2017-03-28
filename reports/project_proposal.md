# Graphical Grapes Project 2 Proposal

## Project Goals

**Overview**

Our goals for this project are focused around generating graphics procedurally.  We will learn to use OpenGL in conjunction with C to generate graphics and explore a variety of current procedural modeling methods.

**MVP**

Our MVP implementation is an endless maze that is continuously generated following a set of predetermined algorithms.  Maze characteristics will include always having a successful route to the exit confirmed using DFS and having cellular automata behaviors that define how the new blocks are generated at each step.

**Stretch Goals**
Make the maze game unique and fun to play in some way.  Possible ideas include you can only turn left, you can only go backwards, it teases you with the end of the maze but you can never reach it.  Extend the initial maze to implement another characteristic procedurally.  This could be color, texture, depth, or other factors.

## Resources

**OpenGL Resources**

An overview of the OpenGL pipeline and some of the available capabilities involved.

[Getting Started with OpenGL](http://duriansoftware.com/joe/An-intro-to-modern-OpenGL.-Table-of-Contents.html)

A tutorial on how to build an OpenGL application in the C programming language.

[Building OpenGL Applications in C](http://www.opengl-tutorial.org/miscellaneous/building-your-own-c-application/)

A tutorial on rendering 3D text in OpenGL.

[Rendering 3D Objects in OpenGL](https://www.toptal.com/opengl/introduction-to-opengl-a-quick-tutorial)

A set of lecture notes that describes how a variety of shapes and patterns can be created.

**Procedural Generation Resources**

[Princeton Lecture on Procedural Modeling](http://www.cs.princeton.edu/courses/archive/spr03/cs426/lectures/16-procedural.pdf)

This paper provides a general overview of procedural modeling capabilities.

[Cellular Automata library](http://kidojo.com/cellauto/) 

A C library for generating cellular automata, useful to look at code to see how cellular automata work.

[Procedural Generation tutorials for Unity](http://catlikecoding.com/unity/tutorials/)

Tutorials for procedural generation in Unity for everything from fractal generation to complex procedural meshes and textures.

[A General Procedural Modeling Algorithm](http://graphics.stanford.edu/~pmerrell/tvcg.pdf)

A paper on generating complex terrain.  This is too complex for the scope of our project, but an interesting look at the possibilities of the field.

[Artistic Rendering of Mountainous Terrain](http://www.cs.utah.edu/~bratkova/research/projects/panorama/togFinal2.pdf)

Again, the full implementation outlined in this paper is outside of the scope of our project, but shows how simple procedural algorithms can be used in conjunction with area guides to create complex scenes.

[Guided Procedural Modeling](http://hpcg.purdue.edu/bbenes/papers/Benes11EG.pdf)

## Product Backlog

Our project backlog can be seen on our team Trello board [here](https://trello.com/b/UZL4Y39R/softsysgraphicalgrapes).

## Potential Roadblocks

Our team members have varied previous experience in OpenGL, so we are beginning the project by ensuring that everyone is up to speed on the basic development process.

Implementing procedural algorithms can involve complex math and physics.  We are starting with simple model deliverables to step our way into more complex implementations without getting lost in the details of one particular algorithm.

Finally, this is a very large and complex field of study that could be easy to get lost in.  By choosing a final deliverable implementation, we are limiting ourselves to one particular path in this field.
