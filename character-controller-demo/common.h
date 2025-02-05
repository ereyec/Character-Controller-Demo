#ifndef COMMON_H
#define COMMON_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct triangle{
	glm::vec3 v1;
	glm::vec3 v2;
	glm::vec3 v3;
	glm::vec3 normal;
	glm::vec3 anchor;
};

class Common{
public:
	std::vector<int> worldHeightmap;
	std::vector<int> world3DData;

	std::vector<triangle> triangles;

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