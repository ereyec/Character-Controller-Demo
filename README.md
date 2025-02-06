# Character Controller Demo - Description

My first attempt at making a 3D character controller in OpenGL from scratch for use in games. This demo is for learning purposes, meant to be as simple as possible a way to create a first person character controller in OpenGL. 

For simplicity, the player collider is a sphere. This allows it to climb obstacles smaller than the radius of the sphere. 

Broad phase collision detection is done with the use of a std::multimap, with the neighboring points around the player acting as the key to hash triangles. 

The tessellation stage creates triangles whose sides are about 1/2 the radius of the collider sphere to avoid complicated math (such as vector projection, plane intersection tests), so that we only have to check the radius between each triangle vertex and the sphere collider center. 

While playable, there are many issues to address. The biggest two are dealing with velocity and the scene organization in memory. The velocity of the collider is currently a static variable in the physicsUpdate() function. To make the movement more realistic, I'd have the velocity be a part of a player class and introduce forces. Another is how the scene is stored in memory. Ideally, it should be organized as an aabb tree to allow for more efficient lookup of possible collisions.

# Build Instructions
(Windows)

Make sure g++ in installed on your machine.

Enter ````g++ -I./include -L./lib ./include/glad.c ./character-controller-demo/main.cpp -l:libglfw3.a -lopengl32 -lgdi32 -luser32 -o program.exe```` in cmd in the root directory.

