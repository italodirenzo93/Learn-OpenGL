#include "Texture.h"

Texture::Texture(const char* fileName)
{
	glGenTextures(1, &ID);

    int width, height, nChannels;
    auto image = stbi_load(fileName, &width, &height, &nChannels, STBI_default);

    if (image)
    {
        GLint format = GL_RGB;
        if (nChannels == 1)
            format = GL_RED;
        else if (nChannels == 3)
            format = GL_RGB;
        else if (nChannels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, ID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(image);
    }
    else
    {
        std::cout << "Unable to load texture at " << fileName << std::endl;
        stbi_image_free(image);
    }
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
