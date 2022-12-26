#ifndef SHADER_H
#define SHADER_H

#include "CommonInclude.h"

class Shader
{
public:
	unsigned int ID;

	explicit Shader(const char *vertexPath, const char *fragmentPath);
	~Shader();

	void use();
	void setBool(const char *name, bool value) const;
	void setInt(const char *name, int value) const;
	void setFloat(const char *name, float value) const;
	void setMat4(const char *name, const glm::mat4 &value) const;
	void setVec3(const char *name, const glm::vec3 &value) const;
	void setVec3(const char *name, float x, float y, float z) const;

private:
	NON_COPYABLE_OR_MOVABLE_CLASS(Shader)
};

#endif
