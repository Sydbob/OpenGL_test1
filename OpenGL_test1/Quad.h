#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "stb_image.h"
#include <array>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Quad {

public:
	Quad();
	void GenerateQuad(float size);
	void DrawQuad();
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
