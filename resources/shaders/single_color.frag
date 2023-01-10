#version 330 core

out vec4 FragColor;

uniform vec3 uColor = vec3(0.04, 0.28, 0.26);

void main()
{
    FragColor = vec4(uColor, 1.0);
}