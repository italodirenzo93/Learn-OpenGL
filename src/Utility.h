#ifndef UTILITY_H
#define UTILITY_H

#include "Buffer.h"
#include "VertexArrayLayout.h"

namespace util
{
    void clear(bool color = true, bool depth = true, bool stencil = false, int stencilValue = 0, float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);

    /**
     * Vertex layout is POSITION, NORMAL, TEXCOORD
     * @param vertexBuffer
     * @param indexBuffer
     */
    void createCube(VertexArrayLayout& vertexArray, VertexBuffer<float> &vertexBuffer, IndexBuffer &indexBuffer);

	/**
	 * @param textureDir
	 */
	unsigned int loadCubemap(const std::string& textureDir);
}

#endif
