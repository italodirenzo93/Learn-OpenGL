#ifndef MATERIAL_H
#define MATERIAL_H

#include "CommonInclude.h"
#include "Shader.h"
#include "Texture.h"

class Material
{
public:
//	glm::vec3 diffuse;
//	int diffuseMap = -1;
//	glm::vec3 specular;
//	int specularMap = -1;
	float shininess = 32.0f;

    std::weak_ptr<Texture> diffuse;
    std::weak_ptr<Texture> specular;

//	Material() {}
//
//	Material(const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess)
//		: diffuse(diffuse), specular(specular), shininess(shininess) {}

	void apply(const Shader &program, const std::string &uniformName) const;
};

#endif
