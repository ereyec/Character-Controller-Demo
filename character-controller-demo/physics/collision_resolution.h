#ifndef COLLISIONRESOLUTION_H
#define COLLISIONRESOLUTION_H

#include "../common.h"
#include "../context.h"

void resolveCollision(Collision& collision, Common& common, Context& context, float& velocity){
	glm::vec3 moveDirection = glm::normalize(common.player.position - collision.trianglePoint);
	moveDirection *= collision.penetrationDepth;
	context.camera.cameraPos += moveDirection;
	if(glm::dot(collision.contactNormal, glm::vec3(0.f, -1.f, 0.f)) > 0.99f) velocity = 0.0f; // why is it negative??
}

#endif