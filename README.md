# Character Controller Demo - Description

My first attempt at making a 3D character controller in OpenGL from scratch for use in games. This demo is primarily for learning purposes, meant to be as simple as possible a way to create a first person character controller in OpenGL. 

For simplicity, the player collider is a sphere. This allows it to climb obstacles smaller than the radius of the sphere. 

Broad-phase collision detection is done with the use of an Axis-Aligned Bounding Box Tree (AABB Tree) data structure for O(logN) collision queries. 

Narrow-phase collision detection is done with tessellated triangles whose sides are about 1/2 the radius of the collider sphere to avoid complicated math (such as vector projection, plane intersection tests), so that we only have to check the radius between each triangle vertex and the sphere collider center.

Primary issues to address: Camera-Collider decoupling, adding velocity & acceleration, AABB tree insertion and deletion for dynamic scenes

# Build Instructions
(Windows)

Make sure g++ in installed on your machine.

Enter ````g++ -I./include -L./lib ./include/glad.c ./character-controller-demo/main.cpp -l:libglfw3.a -lopengl32 -lgdi32 -luser32 -o program.exe```` in cmd in the root directory.

