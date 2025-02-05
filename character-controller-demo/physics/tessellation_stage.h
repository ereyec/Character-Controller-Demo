#ifndef TESSELLATIONSTAGE_H
#define TESSELLATIONSTAGE_H

struct triangleQuart{
	glm::vec3 v1;
	glm::vec3 v2;
	glm::vec3 v3;
	glm::vec3 v12;
	glm::vec3 v13;
	glm::vec3 v23;
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

std::multimap<glm::vec3, triangleQuart, Vec3Hash, Vec3Equal> sceneMap; //need a hash

for(int i = 0; i < common.triangles.size(); i++){
	glm::vec3 v12 = getMidpoint3D(common.triangles[i].v1, common.triangles[i].v2);
	glm::vec3 v13 = getMidpoint3D(common.triangles[i].v1, common.triangles[i].v3);
	glm::vec3 v23 = getMidpoint3D(common.triangles[i].v2, common.triangles[i].v3);
	glm::vec3 key = common.triangles[i].anchor;
	triangleQuart tq = {common.triangles[i].v1, common.triangles[i].v2, common.triangles[i].v3, v12, v13, v23};
	sceneMap.insert(std::make_pair(key, tq));	
}

#endif