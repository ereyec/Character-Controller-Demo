#ifndef AABBTREE_H
#define AABBTREE_H

#include "../common.h"

void createObjects(Common& common){
for(int i = 0; i < common.triangles.size(); i++){
	std::vector<glm::vec3> points;	
	points.push_back(common.triangles[i].v1);
	points.push_back(common.triangles[i].v2);
	points.push_back(common.triangles[i].v3);
	
	glm::vec3 p;
	glm::vec3 q;
	std::sort(points.begin(), points.end(), [](const glm::vec3& a, const glm::vec3& b) //!!!
	{ return a.x < b.x; }	
	);
	p.x = points[0].x - 2.0f; //!!!
	q.x = points[2].x + 2.0f;

	std::sort(points.begin(), points.end(), [](const glm::vec3& a, const glm::vec3& b) //!!!
	{ return a.y < b.y; }	
	);
	p.y = points[0].y - 2.0f;
	q.y = points[2].y + 2.0f;

	std::sort(points.begin(), points.end(), [](const glm::vec3& a, const glm::vec3& b) //!!!
	{ return a.z < b.z; }	
	);
	p.z = points[0].z - 2.0f;
	q.z = points[2].z + 2.0f;

	BoundingBox box = {p, q};

	glm::vec3 v12 = getMidpoint3D(common.triangles[i].v1, common.triangles[i].v2);
	glm::vec3 v13 = getMidpoint3D(common.triangles[i].v1, common.triangles[i].v3);
	glm::vec3 v23 = getMidpoint3D(common.triangles[i].v2, common.triangles[i].v3);
	
	triangleQuart tq = {common.triangles[i].v1, common.triangles[i].v2, common.triangles[i].v3, v12, v13, v23, common.triangles[i].normal};

	std::pair<BoundingBox, triangleQuart> pair = std::make_pair(box, tq);
	common.objects.push_back(pair);

}
}

void constructAABBTree(Common& common, int lowIndex, int highIndex, std::unique_ptr<AABBNode>& nodePtr){

int xMin = std::numeric_limits<int>::max();
int xMax = std::numeric_limits<int>::min();
int yMin = std::numeric_limits<int>::max();
int yMax = std::numeric_limits<int>::min();
int zMin = std::numeric_limits<int>::max();
int zMax = std::numeric_limits<int>::min();

//todo: change the variable names
for(int i = lowIndex; i <= highIndex; i++){
	if(common.objects[i].first.p.x < xMin){
		xMin = common.objects[i].first.p.x;
	}
	if(common.objects[i].first.q.x > xMax){
		xMax = common.objects[i].first.q.x;
	}

	if(common.objects[i].first.p.y < yMin){
		yMin = common.objects[i].first.p.y;
	}
	if(common.objects[i].first.q.y > yMax){
		yMax = common.objects[i].first.q.y;
	}

	if(common.objects[i].first.p.z < zMin){
		zMin = common.objects[i].first.p.z;
	}
	if(common.objects[i].first.q.z > zMax){
		zMax = common.objects[i].first.q.z;
	}
}

int xAxisLen = xMax - xMin;
int yAxisLen = yMax - yMin;
int zAxisLen = zMax - zMin;

nodePtr->boundingVolume.p.x = xMin;
nodePtr->boundingVolume.q.x = xMax;
nodePtr->boundingVolume.p.y = yMin;
nodePtr->boundingVolume.q.y = yMax;
nodePtr->boundingVolume.p.z = zMin;
nodePtr->boundingVolume.q.z = zMax;

if(lowIndex + 1 == highIndex){
	nodePtr->left = std::make_unique<AABBNode>();
	nodePtr->right = std::make_unique<AABBNode>();	
	nodePtr->left->boundingVolume = common.objects[lowIndex].first;
	nodePtr->left->triangles = common.objects[lowIndex].second;
	nodePtr->right->boundingVolume = common.objects[highIndex].first;
	nodePtr->right->triangles = common.objects[highIndex].second;
	return;
}

if(xAxisLen >= yAxisLen && xAxisLen >= zAxisLen){

	std::sort(common.objects.begin() + lowIndex, common.objects.begin() + highIndex, [](const std::pair<BoundingBox, triangleQuart>& a, const std::pair<BoundingBox, triangleQuart>& b)
	{ return (a.first.p.x + a.first.q.x) / 2.f < (b.first.p.x + b.first.q.x) / 2.f; }
	);
	
	int middle = (lowIndex + highIndex) / 2;
	//be mindful of memory leaks
	nodePtr->left = std::make_unique<AABBNode>();
	constructAABBTree(common, lowIndex, middle, nodePtr->left);
	nodePtr->right = std::make_unique<AABBNode>();
	constructAABBTree(common, middle, highIndex, nodePtr->right);
	
}
else if(yAxisLen >= xAxisLen && yAxisLen >= zAxisLen){

	std::sort(common.objects.begin() + lowIndex, common.objects.begin() + highIndex, [](const std::pair<BoundingBox, triangleQuart>& a, const std::pair<BoundingBox, triangleQuart>& b)
	{ return (a.first.p.y + a.first.q.y) / 2.f < (b.first.p.y + b.first.q.y) / 2.f; }
	);
	
	int middle = (lowIndex + highIndex) / 2;
	//be mindful of memory leaks
	nodePtr->left = std::make_unique<AABBNode>(); 
	constructAABBTree(common, lowIndex, middle, nodePtr->left);
	nodePtr->right = std::make_unique<AABBNode>();
	constructAABBTree(common, middle, highIndex, nodePtr->right);
	
}
else if(zAxisLen >= xAxisLen && zAxisLen >= yAxisLen){

	std::sort(common.objects.begin() + lowIndex, common.objects.begin() + highIndex, [](const std::pair<BoundingBox, triangleQuart>& a, const std::pair<BoundingBox, triangleQuart>& b)
	{ return (a.first.p.z + a.first.q.z) / 2.f < (b.first.p.z + b.first.q.z) / 2.f; }
	);
	
	int middle = (lowIndex + highIndex) / 2;
	nodePtr->left = std::make_unique<AABBNode>();
	constructAABBTree(common, lowIndex, middle, nodePtr->left);
	nodePtr->right = std::make_unique<AABBNode>();
	constructAABBTree(common, middle, highIndex, nodePtr->right);
	
}

}


void queryAABBTree(std::unique_ptr<AABBNode>& nodePtr, glm::vec3 point, std::vector<triangleQuart>& collisionCandidates){
	//base case: left and right are null, we are at a leaf node.
	if(nodePtr->left == nullptr && nodePtr->right == nullptr){
		bool c1 = point.x >= nodePtr->boundingVolume.p.x && point.x <= nodePtr->boundingVolume.q.x;
		bool c2 = point.y >= nodePtr->boundingVolume.p.y && point.y <= nodePtr->boundingVolume.q.y;		bool c3 = point.z >= nodePtr->boundingVolume.p.z && point.z <= nodePtr->boundingVolume.q.z;
		if(c1 && c2 && c3){
			collisionCandidates.push_back(nodePtr->triangles);
		}
		return;	
	}
	
	//else, we are at an internal node
	if(nodePtr->left !=nullptr){
		bool c1 = point.x >= nodePtr->boundingVolume.p.x && point.x <= nodePtr->boundingVolume.q.x;
		bool c2 = point.y >= nodePtr->boundingVolume.p.y && point.y <= nodePtr->boundingVolume.q.y;		bool c3 = point.z >= nodePtr->boundingVolume.p.z && point.z <= nodePtr->boundingVolume.q.z;		if(c1 && c2 && c3){
			queryAABBTree(nodePtr->left, point, collisionCandidates);
		}
	}
	if(nodePtr->right !=nullptr){
		bool c1 = point.x >= nodePtr->boundingVolume.p.x && point.x <= nodePtr->boundingVolume.q.x;
		bool c2 = point.y >= nodePtr->boundingVolume.p.y && point.y <= nodePtr->boundingVolume.q.y;		bool c3 = point.z >= nodePtr->boundingVolume.p.z && point.z <= nodePtr->boundingVolume.q.z;		if(c1 && c2 && c3){
			queryAABBTree(nodePtr->right, point, collisionCandidates);		
		}
	}


}

#endif