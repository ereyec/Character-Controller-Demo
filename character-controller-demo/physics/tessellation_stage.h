#ifndef TESSELLATIONSTAGE_H
#define TESSELLATIONSTAGE_H

/****OBSOLETE****/

#include "../common.h"

void tessellationStage(Common& common){
for(int i = 0; i < common.triangles.size(); i++){
	glm::vec3 v12 = getMidpoint3D(common.triangles[i].v1, common.triangles[i].v2);
	glm::vec3 v13 = getMidpoint3D(common.triangles[i].v1, common.triangles[i].v3);
	glm::vec3 v23 = getMidpoint3D(common.triangles[i].v2, common.triangles[i].v3);
	glm::vec3 key = common.triangles[i].anchor;
	triangleQuart tq = {common.triangles[i].v1, common.triangles[i].v2, common.triangles[i].v3, v12, v13, v23, common.triangles[i].normal};
	common.sceneMap.insert(std::make_pair(key, tq));	
}

}
#endif