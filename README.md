# Mavis Beacon: Starship Commander
A typing game written in C++ with OpenGL.

## What is it?
Mavis Beacon: Starship Commander puts you at the helm of an intergalactic starship fighter, tasked with ridding the galaxy of the alien scum that inhabit the space-time continuum. Blast through enemies by accurately and quickly maneuvering your Qwerty Laser Cannon. Target your enemies by typing the words affixed to the front of their ships, destroy oncoming asteroids, and pick up useful repair-kits along the way. 

## How'd you make it?
Raw C++ and OpenGL. The SFML game engine is lightly employed for keyboard input and window creation. The GLUT and GLM libraries are used to get pixels on the screen and perform matrix math. A generic particle emission system was written, capable of creating fire emissions, explosions and more. A spline system was implemented to animate all the enemies, allowing them to zoom into view and fly around on the screen. A UI framwork was created for getting text on the screen, and an expressive message-passing system was written to pass game events through the heirarchy of nodes to ensure everything responds correctly to the state of the game.

## Screenshots
![Screenshot 1](https://i.imgur.com/T8u9N8W.png)
![Screenshot 1](https://i.imgur.com/o0k17lR.png)

