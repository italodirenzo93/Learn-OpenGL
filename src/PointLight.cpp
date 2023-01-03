#include "PointLight.h"

void PointLight::apply(const Shader &program, const std::string &uniformName) const
{
	program.use();
	program.setVec3(std::format("{}.position", uniformName), position);

	program.setVec3(std::format("{}.ambient", uniformName), ambient);
	program.setVec3(std::format("{}.diffuse", uniformName), diffuse); // darkened
	program.setVec3(std::format("{}.specular", uniformName), specular);

	program.setFloat(std::format("{}.constant", uniformName), constant);
	program.setFloat(std::format("{}.linear", uniformName), linear);
	program.setFloat(std::format("{}.quadratic", uniformName), quadratic);
}
