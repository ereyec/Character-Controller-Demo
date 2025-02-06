#ifndef COLLISIONRESOLUTION_H
#define COLLISIONRESOLUTION_H

#include "../common.h"
#include "../context.h"

//(penetration depth, contact point, position)
void resolveCollision(Collision& collision, Common& common, Context& context){
	glm::vec3 moveDirection = glm::normalize(common.player.position - collision.trianglePoint);
	moveDirection *= collision.penetrationDepth;
	//common.player.position += moveDirection;
	context.camera.cameraPos += moveDirection;
}

#endif