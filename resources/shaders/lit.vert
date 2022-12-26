#version 330 core

layout(location=0) in vec3 aPos;

uniform mat4 uMatModel;
uniform mat4 uMatView;
uniform mat4 uMatProjection;

void main()
{
	gl_Position = uMatProjection * uMatView * uMatModel * vec4(aPos, 1.0);
}
