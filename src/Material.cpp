#include "Material.h"

void Material::apply(const Shader &program, const std::string &uniformName) const
{
	if (diffuseMap >= 0)
	{
		program.setInt(std::format("{}.diffuse", uniformName), diffuseMap);
	}
	else
	{
		program.setVec3(std::format("{}.diffuse", uniformName), diffuse);
	}
	program.setVec3(std::format("{}.specular", uniformName), specular);
	program.setFloat(std::format("{}.shininess", uniformName), shininess);
}
