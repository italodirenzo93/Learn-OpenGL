#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>

class Shader
{
public:
	unsigned int ID;

	explicit Shader(const char *vertexPath, const char *fragmentPath);

	void use();
	void setBool(const char *name, bool value) const;
	void setInt(const char *name, int value) const;
	void setFloat(const char *name, float value) const;
	void setMatrix(const char *name, const glm::mat4 &value);
};

#endif
