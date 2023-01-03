#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "CommonInclude.h"
#include "Shader.h"

class PointLight
{
public:
	glm::vec3 position = glm::vec3(0.0f);

	glm::vec3 ambient = glm::vec3(0.2f);
	glm::vec3 diffuse = glm::vec3(0.5f);
	glm::vec3 specular = glm::vec3(1.0f);

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	PointLight() = default;
	PointLight(const PointLight &) = default;
	PointLight(const glm::vec3 &position) : position(position) {}

	void apply(const Shader &program, const std::string &uniformName) const;

private:
	NON_MOVABLE_CLASS(PointLight)
};

#endif
