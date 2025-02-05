#ifndef MESHWORLD_H
#define MESHWORLD_H

#include "../common.h"
#include "../context.h"


void meshWorld(Common& common, Context& context){
for(int i = 0; i < common.triangles.size(); i++){
	pushV3N3(context.sVertexData, common.triangles[i].v1, common.triangles[i].normal);
	pushV3N3(context.sVertexData, common.triangles[i].v2, common.triangles[i].normal);
	pushV3N3(context.sVertexData, common.triangles[i].v3, common.triangles[i].normal);
}


glGenVertexArrays(1, &context.sVAO);
glGenBuffers(1, &context.sVBO);
glBindVertexArray(context.sVAO);
glBindBuffer(GL_ARRAY_BUFFER, context.sVBO);
glBufferData(GL_ARRAY_BUFFER, context.sVertexData.size() * sizeof(float), context.sVertexData.data(), GL_STATIC_DRAW);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);
glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);

}
#endif