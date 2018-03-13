#include "Texture.h"

Texture::Texture(char const *filename, unsigned int texture)
	:m_Texture(texture)
	,m_Filename(filename)
	,m_Width(0)
	,m_Height(0)
{}

unsigned int Texture::GetTextureID() { return m_Texture; }

void Texture::GenerateTexture(){

	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	//setting wrap option for x(s) and y(t) axes of the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//parameters for minimising and magnifying filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//mipmap filtering options
	//note that mag optio doesnt use the mipmap option (will produce an error as mipmaps are not used for upscaling)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//loading the texture
	//setting vertical flip on the load
	stbi_set_flip_vertically_on_load(true);
	int m_nrChannels = 0;
	unsigned char* data = stbi_load(m_Filename, &m_Width, &m_Height, &m_nrChannels, 0);

	//actually generating the texture
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load the texture" << std::endl;
	}
	//freeing the memory
	stbi_image_free(data); 
}