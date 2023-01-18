#include "ModelViewerScene.h"
#include "ShaderManager.h"

using namespace std;

ModelViewerScene::ModelViewerScene(Camera& camera, const char* path) : camera(camera)
{
	model = make_unique<Model>(path);

	ShaderManager::getInstance().preloadShaders();

	lightIntensity = 2.5f;
}

void ModelViewerScene::render(float deltaTime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto shader = ShaderManager::getInstance().get("mesh");
	shader->activate();

	camera.project(*shader);

	auto matModel = glm::identity<glm::mat4>();
	shader->setMat4("uMatModel", matModel);

	auto matNormal = glm::transpose(glm::inverse(matModel));
	shader->setMat4("uMatNormal", matNormal);

	shader->setVec3("uDirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	shader->setVec3("uDirLight.ambient", glm::vec3(0.2f));
	shader->setVec3("uDirLight.diffuse", glm::vec3(0.5f));
	shader->setVec3("uDirLight.specular", glm::vec3(1.0f));
	shader->setFloat("uDirLight.intensity", lightIntensity);

	shader->setFloat("uMaterial.shininess", 32.0f);

	model->draw(*shader);
}

void ModelViewerScene::renderUi()
{
	ImGui::SliderFloat("Light Intensity", &lightIntensity, 1.0f, 10.0f);
}
