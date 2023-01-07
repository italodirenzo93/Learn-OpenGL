#include "Mesh.h"

#include <utility>

Mesh::Mesh(const std::vector<Vertex>& vertexData, const std::vector<uint32_t>& indexData, Material material)
	: vertices(vertexData), indices(indexData), material(std::move(material)), _vbo(0), _vao(0), _ebo(0)
{
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	setupMesh();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vao);
	glDeleteBuffers(1, &_ebo);
}

void Mesh::draw(const Shader& program) const
{
	material.apply(program, "uMaterial");

	glBindVertexArray(_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

	glDrawElements(GL_TRIANGLES, static_cast<int32_t>(indices.size()), GL_UNSIGNED_INT, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::setupMesh() const
{
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

	glBufferData(GL_ARRAY_BUFFER, static_cast<int32_t>(vertices.size() * sizeof(Vertex)), reinterpret_cast<const void*>(vertices.data()), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<int32_t>(indices.size() * sizeof(Vertex)), reinterpret_cast<const void*>(indices.data()), GL_STATIC_DRAW);

	// vertex position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glEnableVertexAttribArray(0);

	// vertex normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	// vertex tex coord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

