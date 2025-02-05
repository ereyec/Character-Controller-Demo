#ifndef CONTEXT_H
#define CONTEXT_H

#include <vector>
#include <string>

#include "../include/engine/Camera.h"
#include "../include/engine/Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Context{
	GLFWwindow* window = nullptr;

	unsigned int windowWidth = 1200;
	unsigned int windowHeight = 900;
	std::string windowName = "Character Controller Demo";

	std::vector<float> sVertexData; 

	unsigned int sVAO;
	unsigned int sVBO;

	Shader colorShader;

	Camera camera;	

};

Context context;

#endif