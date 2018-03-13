#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "stb_image.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Texture
{
public:
	Texture();
	Texture(char const *filename, unsigned int texture);
	void GenerateTexture();
	void DrawTexture();
	unsigned int GetTextureID();

private:
	unsigned int m_Texture;
	char const* m_Filename;
	int m_Width;
	int m_Height;
		

};