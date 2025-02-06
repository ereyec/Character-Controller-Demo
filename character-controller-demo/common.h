#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <unordered_map>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct playerCollider{ //a sphere for now
	glm::vec3 position;
	float radius;
};

struct Collision{
	glm::vec3 trianglePoint;
	glm::vec3 colliderPoint;
	float penetrationDepth;
	glm::vec3 contactNormal; //(e.g. if the contact is the ground, normal is (0,1,0))
};

struct triangle{
	glm::vec3 v1;
	glm::vec3 v2;
	glm::vec3 v3;
	glm::vec3 normal;
	glm::vec3 anchor;
};

struct triangleQuart{
	glm::vec3 v1;
	glm::vec3 v2;
	glm::vec3 v3;
	glm::vec3 v12;
	glm::vec3 v13;
	glm::vec3 v23;
	glm::vec3 normal;
};

struct Vec3Hash{
	std::size_t operator()(const glm::vec3& v) const{
	std::size_t h1 = std::hash<float>{}(v.x);
	std::size_t h2 = std::hash<float>{}(v.y);
	std::size_t h3 = std::hash<float>{}(v.z);
	std::size_t result = h1;
	result ^= h2 + 0x9e3779b9 + (result << 6) + (result >> 2);
	result ^= h3 + 0x9e3779b9 + (result << 6) + (result >> 2);
	return result;
}};

struct Vec3Equal{
	bool operator()(const glm::vec3& v1, const glm::vec3& v2) const {
		return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
	}
};

glm::vec3 getMidpoint3D(glm::vec3 p, glm::vec3 q){
	glm::vec3 midpoint = glm::vec3((p.x + q.x) / 2.f, (p.y + q.y) / 2.f, (p.z + q.z) / 2.f);
	return midpoint;
}

float getDistance3D(glm::vec3 p1, glm::vec3 p2){
	return std::sqrt( (p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y) + (p2.z - p1.z)*(p2.z - p1.z));
}

class Common{
public:
	std::vector<int> worldHeightmap;
	std::vector<int> world3DData;

	std::vector<triangle> triangles;

	playerCollider player;

	std::unordered_multimap<glm::vec3, triangleQuart, Vec3Hash, Vec3Equal> sceneMap;

	std::vector<triangleQuart> collisionCandidates;
	std::vector<Collision> collisions;

};

Common common;

void pushV3N3(std::vector<float>& vertices, glm::vec3 vec, glm::vec3 norm){
	vertices.push_back(vec.x);
        vertices.push_back(vec.y);
        vertices.push_back(vec.z);
	vertices.push_back(norm.x);
        vertices.push_back(norm.y);
        vertices.push_back(norm.z);
}

#endif