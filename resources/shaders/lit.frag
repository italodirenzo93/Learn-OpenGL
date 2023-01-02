#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirectionalLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	float cutoff;
	float outerCutoff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 uViewPos;
uniform Material uMaterial;
// uniform DirectionalLight uLight;
// uniform PointLight uLight;
uniform SpotLight uLight;

void main()
{
	// Ambient
	vec3 ambient = uLight.ambient * vec3(texture(uMaterial.diffuse, TexCoords));

	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(uLight.position - FragPos);
	// vec3 lightDir = normalize(-uLight.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = uLight.diffuse * diff * vec3(texture(uMaterial.diffuse, TexCoords));

	// Specular (calculated in world space)
	vec3 viewDir = normalize(uViewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
	vec3 specular = uLight.specular * spec * vec3(texture(uMaterial.specular, TexCoords));

	// float distance = length(uLight.position - FragPos);
	// float attenuation = 1.0 / (uLight.constant + uLight.linear * distance + uLight.quadratic * (distance * distance));
	// ambient *= attenuation;
	// diffuse *= attenuation;
	// specular *= attenuation;

	float theta = dot(lightDir, normalize(-uLight.direction));
	float epsilon = uLight.cutoff - uLight.outerCutoff;
	float intensity = clamp((theta - uLight.outerCutoff) / epsilon, 0.0, 1.0);

	diffuse *= intensity;
	specular *= intensity;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);
}
