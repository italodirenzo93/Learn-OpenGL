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
	void setMat4(const char *name, const glm::mat4 &value);

private:
	NON_COPYABLE_CLASS(Shader);
	NON_MOVABLE_CLASS(Shader);
};

#endif
