#ifndef TEXTURE_H
#define TEXTURE_H

#include "CommonInclude.h"

class Texture
{
public:
	Texture();
	~Texture();

	uint32_t getID() const { return ID; }

	void activate(GLenum textureUnit) const;

private:
	uint32_t ID;

public:
	static bool createFromFile(const char *fileName, Texture &texture);

private:
	NON_MOVABLE_CLASS(Texture)
};

#endif
