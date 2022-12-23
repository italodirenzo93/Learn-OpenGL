#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D uSampler;

void main()
{
	FragColor = texture(uSampler, TexCoord) * vec4(ourColor, 1.0);
}
