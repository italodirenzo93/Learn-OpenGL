#include "Material.h"

void Material::apply(const Shader &program, const std::string &uniformName) const
{
	if (diffuseMap >= 0)
	{
		program.setInt(uniformName + ".diffuse", diffuseMap);
	}
	else
	{
		program.setVec3(uniformName + ".diffuse", diffuse);
	}

	if (specularMap >= 0)
	{
		program.setInt(uniformName + ".specular", specularMap);
	}
	else
	{
		program.setVec3(uniformName + ".specular", specular);
	}

	program.setFloat(uniformName + ".shininess", shininess);
}
