#version 330 core

layout(location=0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 uMatProjection;
uniform mat4 uMatView;

void main()
{
    gl_Position = uMatProjection * uMatView * vec4(aPos, 1.0);
    TexCoords = aPos;
}
