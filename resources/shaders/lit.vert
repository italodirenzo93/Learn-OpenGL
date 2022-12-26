#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 uMatModel;
uniform mat4 uMatView;
uniform mat4 uMatProjection;

void main()
{
	gl_Position = uMatProjection * uMatView * uMatModel * vec4(aPos, 1.0);
	FragPos = vec3(uMatModel * vec4(aPos, 1.0));

	// NOTE: inverting a matrix is very costly on the GPU. For production apps, a dedicated model
	// model matrix should be calculated on the CPU and sent to the GPU via a uniform.
	Normal = mat3(transpose(inverse(uMatModel))) * aNormal;
}
