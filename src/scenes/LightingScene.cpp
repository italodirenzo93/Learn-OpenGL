#include "LightingScene.h"

#include "Material.h"

static const float vertices[] = {
	// positions // normals // texture coords
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

static constexpr unsigned int stride = 8 * sizeof(float);

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

Material orangeMaterial(
	glm::vec3(1.0f, 0.5f, 0.31f),
	glm::vec3(1.0f, 0.5f, 0.31f),
	glm::vec3(0.5f),
	32.0f);

LightingScene::LightingScene(std::shared_ptr<Camera> camera)
	: _camera(camera)
{
	_program = std::make_unique<Shader>("./resources/shaders/lit.vert", "./resources/shaders/lit.frag");
	_lightProgram = std::make_unique<Shader>("./resources/shaders/basic.vert", "./resources/shaders/light.frag");

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	_program->use();
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	// aPos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);
	// aNormal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	_lightProgram->use();
	glGenVertexArrays(1, &_lightVao);
	glBindVertexArray(_lightVao);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glUseProgram(0);
}

LightingScene::~LightingScene()
{
	glDeleteBuffers(1, &_vbo);
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

	orangeMaterial.apply(*_program, "uMaterial");

	glm::vec3 lightColor;
	lightColor.x = sinf(fTime * 2.0f);
	lightColor.y = sinf(fTime * 0.7f);
	lightColor.z = sinf(fTime * 1.3f);
	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

	_program->setVec3("uLight.position", lightPos);
	_program->setVec3("uLight.ambient", ambientColor);
	_program->setVec3("uLight.diffuse", diffuseColor); // darkened
	_program->setVec3("uLight.specular", 1.0f, 1.0f, 1.0f);

	{
		glm::mat4 matModel(1.0f);
		_program->setMat4("uMatModel", matModel);
		_program->setMat4("uMatNormal", glm::transpose(glm::inverse(matModel)));

		glBindVertexArray(_vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	_lightProgram->use();
	_lightProgram->setMat4("uMatProjection", _camera->getProjectionMatrix());
	_lightProgram->setMat4("uMatView", _camera->getViewMatrix());
	_lightProgram->setVec3("uLightColor", lightColor);

	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		_lightProgram->setMat4("uMatModel", model);

		glBindVertexArray(_lightVao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
