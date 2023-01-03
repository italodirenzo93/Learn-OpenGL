#include "PointLight.h"

void PointLight::apply(const Shader &program, const std::string &uniformName) const
{
	program.setVec3(uniformName + ".position", position);

	program.setVec3(uniformName + ".ambient", ambient);
	program.setVec3(uniformName + ".diffuse", diffuse); // darkened
	program.setVec3(uniformName + ".specular", specular);

	program.setFloat(uniformName + ".constant", constant);
	program.setFloat(uniformName + ".linear", linear);
	program.setFloat(uniformName + ".quadratic", quadratic);
}
