#include "LightingScene.h"
#include "Material.h"

#include <array>

static const std::array<Vertex, 36> vertices{
	// positions // normals // texture coords
	Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f),
	Vertex(0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f),
	Vertex(0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f),
	Vertex(0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f),
	Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f),
	Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f),
	Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
	Vertex(0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
	Vertex(0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),
	Vertex(0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),
	Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
	Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
	Vertex(-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
	Vertex(-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
	Vertex(-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
	Vertex(-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
	Vertex(-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
	Vertex(-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
	Vertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
	Vertex(0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
	Vertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
	Vertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
	Vertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
	Vertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
	Vertex(-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f),
	Vertex(0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f),
	Vertex(0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f),
	Vertex(0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f),
	Vertex(-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f),
	Vertex(-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f),
	Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
	Vertex(0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f),
	Vertex(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
	Vertex(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
	Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f),
	Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f)};

static constexpr unsigned int stride = sizeof(Vertex);

static const std::array<glm::vec3, 10> cubePositions{
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(2.0f, 5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f, 3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f, 2.0f, -2.5f),
	glm::vec3(1.5f, 0.2f, -1.5f),
	glm::vec3(-1.3f, 1.0f, -1.5f)};

static glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// bool CreateTextureFromFile(const char *fileName, GLuint *texture)
// {
// 	int width, height, nChannels;
// 	auto image = stbi_load(fileName, &width, &height, &nChannels, STBI_default);
// 	if (image)
// 	{
// 		GLenum format = 0;
// 		if (nChannels == 1)
// 			format = GL_RED;
// 		else if (nChannels == 3)
// 			format = GL_RGB;
// 		else if (nChannels == 4)
// 			format = GL_RGBA;

// 		glGenTextures(1, texture);
// 		glBindTexture(GL_TEXTURE_2D, *texture);
// 		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
// 		glGenerateMipmap(GL_TEXTURE_2D);
// 		glBindTexture(GL_TEXTURE_2D, 0);

// 		stbi_image_free(image);
// 		return true;
// 	}

// 	stbi_image_free(image);
// 	return false;
// }

LightingScene::LightingScene(std::shared_ptr<Camera> camera)
	: _camera(camera)
{
	_program = std::make_unique<Shader>("./resources/shaders/lit.vert", "./resources/shaders/lit.frag");
	_lightProgram = std::make_unique<Shader>("./resources/shaders/basic.vert", "./resources/shaders/light.frag");

	// glGenBuffers(1, &_vbo);
	// glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
	_vbo.setData(vertices.size(), vertices.data());

	if (!Texture::createFromFile("./resources/textures/container2.png", _diffuseMap))
	{
		std::cout << "Could not load diffuse map!" << std::endl;
	}

	if (!Texture::createFromFile("./resources/textures/container2_specular.png", _specularMap))
	{
		std::cout << "Could not load specular map!" << std::endl;
	}

	_program->use();

	glBindBuffer(GL_ARRAY_BUFFER, _vbo.getID());

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	// aPos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);
	// aNormal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// aTexCoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	_lightProgram->use();
	glGenVertexArrays(1, &_lightVao);
	glBindVertexArray(_lightVao);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(0);

	_material.diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
	_material.diffuseMap = 0; // corresponds to GL_TEXTURE0
	_material.specular = glm::vec3(0.5f);
	_material.specularMap = 1; // corresponds to GL_TEXTURE1
	_material.shininess = 32.0f;
}

LightingScene::~LightingScene()
{
	// glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);
	glDeleteVertexArrays(1, &_lightVao);
}

void LightingScene::render(float deltaTime)
{
	float fTime = static_cast<float>(glfwGetTime());

	lightPos.x = sinf(fTime * 1.5f);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_program->use();

	_program->setMat4("uMatProjection", _camera->getProjectionMatrix());
	_program->setMat4("uMatView", _camera->getViewMatrix());
	_program->setVec3("uLightPos", lightPos);
	_program->setVec3("uViewPos", _camera->position);

	// glm::vec3 lightColor;
	// lightColor.x = sinf(fTime * 2.0f);
	// lightColor.y = sinf(fTime * 0.7f);
	// lightColor.z = sinf(fTime * 1.3f);
	// glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
	// glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
	glm::vec3 lightAmbient(0.2f);
	glm::vec3 lightDiffuse(0.5f);

	// _program->setVec3("uLight.position", lightPos);
	_program->setVec3("uLight.direction", -0.2f, -1.0f, -0.3f);
	_program->setVec3("uLight.ambient", lightAmbient);
	_program->setVec3("uLight.diffuse", lightDiffuse); // darkened
	_program->setVec3("uLight.specular", 1.0f, 1.0f, 1.0f);

	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 matModel(1.0f);
		matModel = glm::translate(matModel, cubePositions[i]);
		float angle = 20.0f * i;
		matModel = glm::rotate(matModel, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

		_program->setMat4("uMatModel", matModel);
		_program->setMat4("uMatNormal", glm::transpose(glm::inverse(matModel)));

		// glActiveTexture(GL_TEXTURE0);
		// glBindTexture(GL_TEXTURE_2D, _diffuseMap.getID());

		// glActiveTexture(GL_TEXTURE1);
		// glBindTexture(GL_TEXTURE_2D, _specularMap.getID());

		_diffuseMap.activate(GL_TEXTURE0);
		_specularMap.activate(GL_TEXTURE1);

		_material.diffuseMap = 0;
		_material.specularMap = 1;
		_material.apply(*_program, "uMaterial");

		glBindVertexArray(_vao);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	}

	// _lightProgram->use();
	// _lightProgram->setMat4("uMatProjection", _camera->getProjectionMatrix());
	// _lightProgram->setMat4("uMatView", _camera->getViewMatrix());
	// // _lightProgram->setVec3("uLightColor", lightColor);

	// {
	// 	glm::mat4 model = glm::mat4(1.0f);
	// 	model = glm::translate(model, lightPos);
	// 	model = glm::scale(model, glm::vec3(0.2f));
	// 	_lightProgram->setMat4("uMatModel", model);

	// 	glBindVertexArray(_lightVao);
	// 	glDrawArrays(GL_TRIANGLES, 0, 36);
	// }
}
