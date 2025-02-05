#ifndef W3DVECTOR_H
#define W3DVECTOR_H

#include <vector>
#include "../common.h"

void map3DWorld(Common& common){
const static int WORLD_HEIGHT = 10;

//by y -> by x -> by z
for(int z = 0; z < 28; z++){
	for(int x = 0; x < 28; x++){
		int index = z * 28 + x;
		int height = common.worldHeightmap[index];
		common.world3DData.push_back(0);
		for(int y = 1; y <= height; y++){
			common.world3DData.push_back(1);
		}
		for(int y = height + 1; y < WORLD_HEIGHT; y++){
			common.world3DData.push_back(0);
		}
	}
}

}
#endif