#ifndef MESH_H
#define MESH_H

#include "CommonInclude.h"
#include "Shader.h"
#include "Material.h"

class Mesh
{
public:
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

//    struct Texture
//    {
//        uint32_t id;
//        std::string type;
//    };

public:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	Material material;

	explicit Mesh(const std::vector<Vertex> &vertexData, const std::vector<uint32_t> &indexData, Material material);
	~Mesh();

	void draw(const Shader& program) const;

private:
	uint32_t _vbo, _vao, _ebo;

	void setupMesh() const;
};

#endif
