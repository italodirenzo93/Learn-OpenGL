#ifndef UTILITY_H
#define UTILITY_H

#include "Buffer.h"

namespace util
{
    /**
     * Vertex layout is POSITION, NORMAL, TEXCOORD
     * @param vertexBuffer
     * @param indexBuffer
     */
    void createCube(VertexBuffer<float> &vertexBuffer, IndexBuffer &indexBuffer);
}

#endif
