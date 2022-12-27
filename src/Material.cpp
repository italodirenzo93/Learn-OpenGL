#include "Material.h"

void Material::apply(const Shader &program, const std::string &uniformName) const
{
	program.setVec3(std::format("{}.ambient", uniformName), ambient);
	program.setVec3(std::format("{}.diffuse", uniformName), diffuse);
	program.setVec3(std::format("{}.specular", uniformName), specular);
	program.setFloat(std::format("{}.shininess", uniformName), shininess);
}
