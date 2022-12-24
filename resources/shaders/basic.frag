#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float uBlendAmount = 0.2;

void main()
{
	FragColor = mix(
		texture2D(texture1, TexCoord),
		texture2D(texture2, TexCoord),
		uBlendAmount);
}
