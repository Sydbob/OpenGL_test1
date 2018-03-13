#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "stb_image.h"
#include <array>
#include "Shader.h"
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

class Quad {

public:
	Quad();
	void GenerateQuad();
	void DrawQuad(Shader shaderProg, float size);
	unsigned int GetEBO();
private:
	unsigned int VBO, VAO, EBO;
	unsigned int indeces[6] = {
		0, 1, 3,
		1, 2, 3
	};
	float vertices[20] = {
		1.0f,  1.0f, 0.0f,      1.0f, 1.0f, // top right
		1.0f, -1.0f, 0.0f,      1.0f, 0.0f, // bottom right
		-1.0f, -1.0f, 0.0f,		0.0f, 0.0f, // bottom left
		-1.0f,  1.0f, 0.0f,		0.0f, 1.0f  // top left 
	};

};
