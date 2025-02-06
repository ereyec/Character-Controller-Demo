#ifndef TRIANGULATEWORLDDATA_H
#define TRIANGULATEWORLDDATA_H

#include <vector>
#include "../common.h"

struct zNormalQuad{
	inline static glm::vec3 v1 = glm::vec3(0, 0.5f, 0);
	inline static glm::vec3 v2 = glm::vec3(0.5f, 0.5f, 0);
	inline static glm::vec3 v3 = glm::vec3(0, 0, 0);
	inline static glm::vec3 v4 = glm::vec3(0.5f, 0, 0);
};
struct xNormalQuad{
	inline static glm::vec3 v1 = glm::vec3(0, 0.5f, 0);
	inline static glm::vec3 v2 = glm::vec3(0, 0.5f, 0.5f);
	inline static glm::vec3 v3 = glm::vec3(0, 0, 0);
	inline static glm::vec3 v4 = glm::vec3(0, 0, 0.5f);
};
struct yNormalQuad{
	inline static glm::vec3 v1 = glm::vec3(0.5f, 0, 0);
	inline static glm::vec3 v2 = glm::vec3(0.5f, 0, 0.5f);
	inline static glm::vec3 v3 = glm::vec3(0, 0, 0);
	inline static glm::vec3 v4 = glm::vec3(0, 0, 0.5f);
};

void triangulateWorld(Common& common){
//28x28x10
for(int z = 1; z < 27; z++){
	for(int x = 1; x < 27; x++){
		for(int y = 1; y < 9; y++){
			int index = z*280 + x*10 + y;
			int nIndex = (z-1)*280 + x*10 + y;
			int sIndex = (z+1)*280 + x*10 + y;
			int eIndex = z*280 + (x-1)*10 + y;
			int wIndex = z*280 + (x+1)*10 + y;
			int tIndex = z*280 + x*10 + (y+1);
			int bIndex = z*280 + x*10 + (y-1);

			int block = common.world3DData[index];
			int nBlock = common.world3DData[nIndex];
			int sBlock = common.world3DData[sIndex];
			int eBlock = common.world3DData[eIndex];
			int wBlock = common.world3DData[wIndex];
			int tBlock = common.world3DData[tIndex];
			int bBlock = common.world3DData[bIndex];
			glm::vec3 pos = glm::vec3(x, y, z) / 2.f;
			glm::vec3 offset;
			if(block == 0){
				if(nBlock == 1){
				common.triangles.push_back({zNormalQuad::v1 + pos, zNormalQuad::v2 + pos, zNormalQuad::v3 + pos, glm::vec3(0,0,-1), zNormalQuad::v3 + pos});
				common.triangles.push_back({zNormalQuad::v2 + pos, zNormalQuad::v3 + pos, zNormalQuad::v4 + pos, glm::vec3(0,0,-1), zNormalQuad::v3 + pos});
				}
				if(sBlock == 1){
				offset = glm::vec3(0, 0, 0.5f);		
				common.triangles.push_back({zNormalQuad::v1 + pos + offset, zNormalQuad::v2 + pos + offset, zNormalQuad::v3 + pos + offset, glm::vec3(0,0,1), zNormalQuad::v3 + pos + offset});
				common.triangles.push_back({zNormalQuad::v2 + pos + offset, zNormalQuad::v3 + pos + offset, zNormalQuad::v4 + pos + offset, glm::vec3(0,0,1), zNormalQuad::v3 + pos + offset});
				}
				if(eBlock == 1){
				common.triangles.push_back({xNormalQuad::v1 + pos, xNormalQuad::v2 + pos, xNormalQuad::v3 + pos, glm::vec3(-1,0,0), xNormalQuad::v3 + pos});
				common.triangles.push_back({xNormalQuad::v2 + pos, xNormalQuad::v3 + pos, xNormalQuad::v4 + pos, glm::vec3(-1,0,0), xNormalQuad::v3 + pos});
				}
				if(wBlock == 1){
				offset = glm::vec3(0.5f, 0, 0);
				common.triangles.push_back({xNormalQuad::v1 + pos + offset, xNormalQuad::v2 + pos + offset, xNormalQuad::v3 + pos + offset, glm::vec3(1,0,0), xNormalQuad::v3 + pos + offset});
				common.triangles.push_back({xNormalQuad::v2 + pos + offset, xNormalQuad::v3 + pos + offset, xNormalQuad::v4 + pos + offset, glm::vec3(1,0,0), xNormalQuad::v3 + pos + offset});
				}
				if(bBlock == 1){
				common.triangles.push_back({yNormalQuad::v1 + pos, yNormalQuad::v2 + pos, yNormalQuad::v3 + pos, glm::vec3(0,-1,0), yNormalQuad::v3 + pos});
				common.triangles.push_back({yNormalQuad::v2 + pos, yNormalQuad::v3 + pos, yNormalQuad::v4 + pos, glm::vec3(0,-1,0), yNormalQuad::v3 + pos});
				}
				if(tBlock == 1){
				offset = glm::vec3(0, 0.5f, 0);
				common.triangles.push_back({yNormalQuad::v1 + pos + offset, yNormalQuad::v2 + pos + offset, yNormalQuad::v3 + pos + offset, glm::vec3(0,1,0), yNormalQuad::v3 + pos + offset});
				common.triangles.push_back({yNormalQuad::v2 + pos + offset, yNormalQuad::v3 + pos + offset, yNormalQuad::v4 + pos + offset, glm::vec3(0,1,0), yNormalQuad::v3 + pos + offset});
				}
			}
			
		}
	}
}

}
#endif