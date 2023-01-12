//
// Created by Italo Di Renzo on 2023-01-10.
//

#include "Cube.h"

#include <array>
using namespace std;

static constexpr uint32_t NUM_ELEMENTS = 36;
static constexpr uint32_t STRIDE = 8;

static const array<float, NUM_ELEMENTS * STRIDE> g_vertices{
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
};

static const array<uint32_t, NUM_ELEMENTS> g_indices{0,1,2,0,2,3,4,5,6,4,6,7,8,9,10,8,10,11,12,13,14,12,14,15,16,17,18,16,18,19,20,21,22,20,22,23};

static vector<Mesh::Vertex> transformVertexArray()
{
    vector<Mesh::Vertex> verts;
    for (uint32_t i = 0; i < g_vertices.size(); i += STRIDE)
    {
        Mesh::Vertex v = {};
        v.position = glm::vec3(g_vertices[i], g_vertices[i + 1], g_vertices[i + 2]);
        v.normal = glm::vec3(g_vertices[i + 3], g_vertices[i + 4], g_vertices[i + 5]);
        v.texCoords = glm::vec2(g_vertices[i + 6], g_vertices[i + 7]);
        verts.emplace_back(v);
    }
    return verts;
}

Cube::Cube()
    : _mesh(transformVertexArray(), vector(g_indices.begin(), g_indices.end()), vector<Mesh::Texture>())
{
}

Cube::Cube(const glm::vec3& translation)
        : _mesh(transformVertexArray(), vector(g_indices.begin(), g_indices.end()), vector<Mesh::Texture>()), transform(translation)
{
}

Cube::Cube(const glm::vec3& translation, const glm::vec3& rotation)
        : _mesh(transformVertexArray(), vector(g_indices.begin(), g_indices.end()), vector<Mesh::Texture>()), transform(translation, rotation)
{
}

Cube::Cube(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
    : _mesh(transformVertexArray(), vector(g_indices.begin(), g_indices.end()), vector<Mesh::Texture>()), transform(translation, rotation, scale)
{
}

void Cube::draw(const Shader &shader) const
{
    auto model = transform.getModelMatrix();

    shader.setMat4("uMatModel", model);
    shader.setMat4("uMatNormal", glm::transpose(glm::inverse(model)));

    _mesh.draw(shader);
}

