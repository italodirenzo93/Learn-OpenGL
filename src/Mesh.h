#ifndef MESH_H
#define MESH_H

#include "CommonInclude.h"
#include "Shader.h"

class Mesh
{
public:
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    struct Texture
    {
        uint32_t id;
        std::string type;
        std::string path;
    };

public:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
    std::vector<Texture> textures;

	explicit Mesh(const std::vector<Vertex> &vertexData, const std::vector<uint32_t> &indexData, const std::vector<Texture> &textures);
    Mesh(const Mesh& other);
    Mesh(Mesh&& other) noexcept;
	~Mesh();

	void draw(const Shader& program) const;

private:
	uint32_t _vbo = 0;
    uint32_t _vao = 0;
    uint32_t _ebo = 0;

	void setupMesh() const;

public:
    Mesh& operator= (const Mesh& other);
    Mesh& operator= (Mesh&& other) noexcept;
};

#endif
