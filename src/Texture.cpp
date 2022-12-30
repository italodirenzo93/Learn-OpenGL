#include "Texture.h"

Texture::Texture()
	: ID(0)
{
	glGenTextures(1, &ID);
}

Texture::~Texture()
{
	glDeleteTextures(1, &ID);
}

void Texture::activate(GLenum textureUnit) const
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

bool Texture::createFromFile(const char *fileName, Texture &texture)
{
	int width, height, nChannels;
	auto image = stbi_load(fileName, &width, &height, &nChannels, STBI_default);
	if (!image)
	{
		std::cout << "Unable to load texture at " << fileName << std::endl;
		stbi_image_free(image);
		return false;
	}

	GLenum format = 0;
	if (nChannels == 1)
		format = GL_RED;
	else if (nChannels == 3)
		format = GL_RGB;
	else if (nChannels == 4)
		format = GL_RGBA;

	glBindTexture(GL_TEXTURE_2D, texture.getID());
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(image);

	return true;
}
