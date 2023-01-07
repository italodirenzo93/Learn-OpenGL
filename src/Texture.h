#ifndef TEXTURE_H
#define TEXTURE_H

#include "CommonInclude.h"

class Texture
{
public:
	explicit Texture(const char* fileName);
	~Texture();

	uint32_t getID() const { return ID; }

	void activate(GLenum textureUnit) const;

private:
	uint32_t ID;

private:
	NON_MOVABLE_CLASS(Texture)
};

#endif
