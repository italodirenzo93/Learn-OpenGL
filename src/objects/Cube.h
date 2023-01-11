#ifndef CMAKEGRAPHICSPROJECT_CUBE_H
#define CMAKEGRAPHICSPROJECT_CUBE_H

#include "Mesh.h"

struct Transform
{
    glm::vec3 translation = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);

    Transform() = default;
    explicit Transform(const glm::vec3& translation)
            : translation(translation) {}
    Transform(const glm::vec3& translation, const glm::vec3& rotation)
        : translation(translation), rotation(rotation) {}
    Transform(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
        : translation(translation), rotation(rotation), scale(scale) {}

    glm::mat4 getModelMatrix() const
    {
        auto model = glm::identity<glm::mat4>();
        model = glm::translate(model, translation);
//        model = glm::rotate(model, 0.0f, glm::normalize(rotation));
        model = glm::scale(model, scale);
        return model;
    }
};

class Cube
{
public:
    Cube();
    explicit Cube(const glm::vec3& translation);
    Cube(const glm::vec3& translation, const glm::vec3& rotation);
    Cube(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);

    Transform transform;

    void draw(const Shader& shader) const;

private:
    uint32_t _vao = 0;
    uint32_t _vbo = 0;
    uint32_t _ebo = 0;

    Mesh _mesh;
};

#endif
