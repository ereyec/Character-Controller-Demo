#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "../common.h"

void broadPhase(Common& common){
for(float z = -1.5f; z < 2; z += 0.5f){
	for(float x = -1.5f; x < 2; x += 0.5f){
		for(float y = -1.5f; y < 2; y += 0.5f){
			glm::vec3 pos0 = common.player.position;
			pos0 *= 2.f;
			pos0 = glm::floor(pos0);
			pos0 /= 2.f;
			pos0 += glm::vec3(x, y, z);

			auto range = common.sceneMap.equal_range(pos0); //!!!
			for(auto it = range.first; it != range.second; ++it){
				common.collisionCandidates.push_back(it->second);
			}
		}
	}
}
}

//narrow phase
void narrowPhase(Common& common){
common.collisions.clear();
for(int i = 0; i < common.collisionCandidates.size(); i++){
	triangleQuart tq = common.collisionCandidates[i];
	if(getDistance3D(common.player.position, tq.v1) < common.player.radius){
		float penetrationDepth = common.player.radius - (getDistance3D(common.player.position, tq.v1));
		common.collisions.push_back({tq.v1, common.player.position, penetrationDepth});
	}
	if(getDistance3D(common.player.position, tq.v2) < common.player.radius){
		float penetrationDepth = common.player.radius - (getDistance3D(common.player.position, tq.v2));
		common.collisions.push_back({tq.v2, common.player.position, penetrationDepth});
	}
	if(getDistance3D(common.player.position, tq.v3) < common.player.radius){
		float penetrationDepth = common.player.radius - (getDistance3D(common.player.position, tq.v3));
		common.collisions.push_back({tq.v3, common.player.position, penetrationDepth});
	}
	if(getDistance3D(common.player.position, tq.v12) < common.player.radius){
		float penetrationDepth = common.player.radius - (getDistance3D(common.player.position, tq.v12));
		common.collisions.push_back({tq.v12, common.player.position, penetrationDepth});
	}
	if(getDistance3D(common.player.position, tq.v13) < common.player.radius){
		float penetrationDepth = common.player.radius - (getDistance3D(common.player.position, tq.v13));
		common.collisions.push_back({tq.v13, common.player.position, penetrationDepth});
	}
	if(getDistance3D(common.player.position, tq.v23) < common.player.radius){
		float penetrationDepth = common.player.radius - (getDistance3D(common.player.position, tq.v23));
		common.collisions.push_back({tq.v23, common.player.position, penetrationDepth});
	}
}
}

//sort collisions by penetration depth
void sortCollisionsByDepth(Common& common){
	std::sort(common.collisions.begin(), common.collisions.end(), [](const Collision& a, const Collision& b)
	{ return a.penetrationDepth > b.penetrationDepth; }
	);
}

#endif