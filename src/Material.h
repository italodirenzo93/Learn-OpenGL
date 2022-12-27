#ifndef MATERIAL_H
#define MATERIAL_H

#include "CommonInclude.h"
#include "Shader.h"

class Material
{
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess = 32.0f;

	Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess)
		: ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

	void apply(const Shader &program, const std::string &uniformName) const;

private:
	NON_MOVABLE_CLASS(Material)
};

#endif
