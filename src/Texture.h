#ifndef TEXTURE_H
#define TEXTURE_H

#include "CommonInclude.h"

class Texture
{
public:
	Texture();
	~Texture();

	unsigned int getID() const { return ID; }

	void activate(GLenum textureUnit) const;

private:
	unsigned int ID;

public:
	static bool createFromFile(const char *fileName, Texture &texture);

private:
	NON_MOVABLE_CLASS(Texture)
};

#endif
