#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

struct playerCollider{ //a sphere for now
	vec3 position;
	float radius;
};

struct collision{
	glm::vec3 trianglePoint;
	glm::vec3 colliderPoint;
	float penetrationDepth;
};

std::vector<triangleQuart> collisionCandidates;
std::vector<collision> collisions;

//broad phase
//glm::vec3 playerPos; radius = 1.f;

for(float z = -1.5f; z < 2; z += 0.5f){
	for(float x = -1.5f; x < 2; x += 0.5f){
		for(float y = -1.5f; y < 2; y += 0.5f){
			glm::vec3 pos; //should be multiple of 0.5 and then added to x,y,z.
			if(sceneMap.find(pos) != sceneMap.end()){
				triangleQuart = sceneMap.find(pos)->second; //check to push all objects!
				collisionCandidates.push_back(triangleQuart); 
			}
		}
	}
}

//narrow phase
for(int i = 0; i < collisionCandidates.size(); i++){
	triangleQuart tq = collisionCandidates[i];
	if(getDistance(.pos, tq.v1) < r){
		float penetrationDepth = r - (std::abs(.pos - tq.v1));
		collisions.push_back({tq.v1, .pos, penetrationDepth});
	}
}

//sort collisions by penetration depth
std::sort(collisions.begin(), collision.end(), [](const collision& a, const collision& b)
{ return a.penetrationDepth > b.penetrationDepth; }
);

#endif