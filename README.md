# Project Title: MiniRT - Raytracing with miniLibX
This project is a simple ray tracing renderer built in C using the miniLibX library. The renderer is capable of producing images from a scene, defined by geometric objects and lighting, from a specific angle and position.

## Features
Fluid window management: The content of the window remains unchanged and adjusts accordingly when the resolution of the window changes.<br>
Geometric objects: The renderer supports simple geometric objects such as plane, sphere, and cylinder.<br>
Object resizing: The unique properties of objects, such as the diameter of a sphere and the width and height of a cylinder, can be resized.<br>
Transformation: The renderer supports translation and rotation transformations for objects, lights, and cameras (except for spheres and lights that cannot be rotated).<br>
Light management: The renderer supports spot brightness, hard shadows, and ambiance lighting. Both Ambient and diffuse lighting are implemented.<br>
Window controls: Pressing ESC or clicking on the red cross on the window's frame closes the window and quits the program cleanly.<br>
Scene description: The program takes a scene description file with the .rt extension as a first argument. The file contains the information about each element in the scene.<br>
