#ifndef PHYSICS_H
#define PHYSICS_H

#include "../common.h"
#include "../context.h"
#include "collision_detection.h"
#include "collision_resolution.h"

void physicsUpdate(Context& context, Common& common, float deltaTime){

broadPhase(common);
if(!common.collisionCandidates.empty()){
	narrowPhase(common);
	if(!common.collisions.empty()){
		sortCollisionsByDepth(common);
		resolveCollision(common.collisions[0], common, context);
		//narrowPhase(common);
	}
}

common.player.position = context.camera.cameraPos;
context.camera.cameraPos += glm::vec3(0.0f, -2.0f, 0.0f) * deltaTime; //needs improving!!!

common.collisionCandidates.clear();

//physics engine:
//current frame
//1.perform broad phase
//2.if no collision candidates, continue to next frame, if collision cadidates, proceed to 3.
//3.perform narrow phase, if no collisions continue to next frame, if collisions, go to 4.
//4.sort collisions, resolve the collision with the deepest penetration depth, go to 3
//next frame

}
#endif