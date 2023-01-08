#include "Mesh.h"

using namespace std;

Mesh::Mesh(const std::vector<Vertex> &vertexData, const std::vector<uint32_t> &indexData,
           const std::vector<Texture> &textures)
        : vertices(vertexData), indices(indexData), textures(textures)
{
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);

    setupMesh();
}

Mesh::~Mesh()
{
    if (_vao != 0)
        glDeleteVertexArrays(1, &_vao);
    if (_vbo != 0)
        glDeleteBuffers(1, &_vao);
    if (_ebo != 0)
        glDeleteBuffers(1, &_ebo);
}

Mesh::Mesh(const Mesh &other)
        : vertices(other.vertices), indices(other.indices), textures(other.textures)
{
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);

    setupMesh();
}

Mesh::Mesh(Mesh &&other) noexcept
        : _vao(other._vao), _vbo(other._vbo), _ebo(other._ebo)
{
    vertices = std::move(other.vertices);
    indices = std::move(other.indices);
    textures = std::move(other.textures);

    other._vao = 0;
    other._vbo = 0;
    other._ebo = 0;
}

void Mesh::draw(const Shader &program) const
{
    uint32_t diffuseNr = 1;
    uint32_t specularNr = 1;
    for (int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate the proper texture unit
        string name = "uMaterial.";
        name += textures[i].type;

        if (textures[i].type == "texture_diffuse")
            name += to_string(diffuseNr++);
        else if (textures[i].type == "texture_specular")
            name += to_string(specularNr++);

        program.setInt(name, i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    glBindVertexArray(_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh() const
{
    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<int32_t>(vertices.size() * sizeof(Vertex)),
                 reinterpret_cast<const void *>(vertices.data()), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<int32_t>(indices.size() * sizeof(uint32_t)),
                 reinterpret_cast<const void *>(indices.data()), GL_STATIC_DRAW);

    // vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    // vertex normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    // vertex tex coord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh &Mesh::operator= (const Mesh &other)
{
    std::copy(other.vertices.begin(), other.vertices.end(), vertices.begin());
    std::copy(other.indices.begin(), other.indices.end(), indices.begin());
    std::copy(other.textures.begin(), other.textures.end(), textures.begin());

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);

    setupMesh();

    return *this;
}

Mesh &Mesh::operator= (Mesh &&other) noexcept
{
    std::move(other.vertices.begin(), other.vertices.end(), vertices.begin());
    std::move(other.indices.begin(), other.indices.end(), indices.begin());
    std::move(other.textures.begin(), other.textures.end(), textures.begin());

    _vao = other._vao;
    other._vao = 0;

    _vbo = other._vbo;
    other._vbo = 0;

    _ebo = other._ebo;
    other._ebo = 0;

    return *this;
}
