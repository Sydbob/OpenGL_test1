#include "Quad.h"

Quad::Quad():
	VBO(0),
	VAO(0),
	EBO(0)
{}

unsigned int Quad::GetEBO() { return EBO; }

void Quad::GenerateQuad(float size) 
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//-----le triangle
	glBindVertexArray(VAO);
	//adjust vertices according to size
	for (unsigned int i = 0; i < sizeof(vertices); i++)
	{
		if (i == 3 || i == 8 || i ==13)
			i += 2;
		if (i == 18)
			break; 
		vertices[i] = vertices[i] * size;
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);
	//linking vertex attributes
	//postiion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//color
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Quad::DrawQuad() {
	glBindVertexArray(EBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}