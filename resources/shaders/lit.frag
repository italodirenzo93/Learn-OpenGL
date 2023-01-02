#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 uViewPos;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

uniform Material uMaterial;

struct Light {
	// vec3 position; // not necessary when using directional lights
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light uLight;

void main()
{
	// Ambient
	vec3 ambient = uLight.ambient * vec3(texture(uMaterial.diffuse, TexCoords));

	// Diffuse
	vec3 norm = normalize(Normal);
	// vec3 lightDir = normalize(uLight.position - FragPos);
	vec3 lightDir = normalize(-uLight.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = uLight.diffuse * diff * vec3(texture(uMaterial.diffuse, TexCoords));

	// Specular (calculated in world space)
	vec3 viewDir = normalize(uViewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
	vec3 specular = uLight.specular * spec * vec3(texture(uMaterial.specular, TexCoords));

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);
}
