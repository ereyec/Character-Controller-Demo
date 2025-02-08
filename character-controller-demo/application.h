#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <stdlib.h>

#include "common.h"
#include "context.h"
#include "./world/read_file.h"
#include "./world/w3d_vector.h"
#include "./triangulation/triangulate_world_data.h"
#include "./mesh/mesh_world.h"
#include "./physics/tessellation_stage.h"
#include "./physics/physics.h"

class Application{
public:	

	Application(){}

	int init(Context& context){
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		context.window = glfwCreateWindow(context.windowWidth, context.windowHeight, context.windowName.c_str(), nullptr, nullptr);
		if(context.window == nullptr){
			std::cout << "Window could not be created. " << std::endl;
			return -1;
		}
		glfwMakeContextCurrent(context.window);
		glfwSetInputMode(context.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        		std::cout << "Failed to initialize GLAD. " << std::endl;
        		return -1;
    		}	

		glEnable(GL_DEPTH_TEST);	

		//Set shaders, camera
		context.colorShader = Shader("./character-controller-demo/mesh/shaders/sVertex.vs", "./character-controller-demo/mesh/shaders/sFragment.fs", true);

		context.camera = Camera(context.window);
		context.camera.cameraSpeed = 8.f;

		return 0;
	}

	void run(Context& context, Common& common);

	void cleanup(Context& context);

private:
	float lastFrame = 0.0f;
	float deltaTime = 0.0f;

};

void Application::run(Context& context, Common& common){

if(readFile(common, "scenedata.txt") == -1){
	std::cout << "Application failed to read file. " << std::endl;
	return;
}
map3DWorld(common);
triangulateWorld(common);
meshWorld(common, context);

physicsInit(common);

context.camera.cameraPos = glm::vec3(6.f, 6.f, 6.f);
common.player.position = context.camera.cameraPos;
common.player.radius = 1.f;

while (!glfwWindowShouldClose(context.window)){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.227f, 0.4f, 0.6f, 1.0f);
	
	float currentFrame = glfwGetTime();
        this->deltaTime = currentFrame - this->lastFrame;
        this->lastFrame = currentFrame;

	context.camera.update(this->deltaTime);

	physicsUpdate(context, common, this->deltaTime);

	glm::mat4 view = glm::lookAt(context.camera.cameraPos, context.camera.cameraPos + context.camera.cameraFront, context.camera.cameraUp);
        glm::mat4 projection = glm::perspective(45.0f, 1200.0f / 900.0f, 0.1f, 400.0f);

	glUseProgram(context.colorShader.ID);
	glUniformMatrix4fv(glGetUniformLocation(context.colorShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(context.colorShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));

	glBindVertexArray(context.sVAO);
	glDrawArrays(GL_TRIANGLES, 0, context.sVertexData.size() / 6);

	glfwSwapBuffers(context.window);
        glfwPollEvents();
}

}

void Application::cleanup(Context& context){
	glDeleteVertexArrays(1, &context.sVAO);
	glDeleteBuffers(1, &context.sVBO);

	glfwTerminate();
}

#endif