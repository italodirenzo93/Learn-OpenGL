#include "ModelViewerScene.h"
#include "ShaderManager.h"
#include "Utility.h"

using namespace std;

static const vector<string> texture_faces{
        "right.jpg",
        "left.jpg",
        "top.jpg",
        "bottom.jpg",
        "front.jpg",
        "back.jpg"
};

ModelViewerScene::ModelViewerScene(Camera& camera, const char* path) : camera(camera)
{
//	model = make_unique<Model>(path);

	ShaderManager::instance().preloadShaders();

	lightIntensity = 2.5f;

    // Cubemap
	cubemapID = util::loadCubemap("./resources/textures/skybox/");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

	// Cube object
    util::createCube(cubeVAO, cubeVBO, cubeIBO);

    boxTexture = make_unique<Texture>("./resources/textures/container.jpg");

	// Skybox
	skyboxVBO.setData({
		// positions          
	   -1.0f,  1.0f, -1.0f,
	   -1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
	   -1.0f,  1.0f, -1.0f,

	   -1.0f, -1.0f,  1.0f,
	   -1.0f, -1.0f, -1.0f,
	   -1.0f,  1.0f, -1.0f,
	   -1.0f,  1.0f, -1.0f,
	   -1.0f,  1.0f,  1.0f,
	   -1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

	   -1.0f, -1.0f,  1.0f,
	   -1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
	   -1.0f, -1.0f,  1.0f,

	   -1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
	   -1.0f,  1.0f,  1.0f,
	   -1.0f,  1.0f, -1.0f,

	   -1.0f, -1.0f, -1.0f,
	   -1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
	   -1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	});

	skyboxVAO.addBinding({ POSITION, 3, GL_FLOAT, false });
	skyboxVAO.mapToBuffer<float, 3>(skyboxVBO);
}

ModelViewerScene::~ModelViewerScene()
{
    glDeleteTextures(1, &cubemapID);
}

void ModelViewerScene::render(float deltaTime)
{
    util::clear(true, true, false, 0, 0.1f, 0.1f, 0.1f, 1.0f);

    // Model
//    {
//        auto shader = ShaderManager::instance().get("mesh");
//        shader->activate();
//
//        camera.project(*shader);
//
//        auto matModel = glm::identity<glm::mat4>();
//        shader->setMat4("uMatModel", matModel);
//
//        auto matNormal = glm::transpose(glm::inverse(matModel));
//        shader->setMat4("uMatNormal", matNormal);
//
//        shader->setVec3("uDirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
//        shader->setVec3("uDirLight.ambient", glm::vec3(0.2f));
//        shader->setVec3("uDirLight.diffuse", glm::vec3(0.5f));
//        shader->setVec3("uDirLight.specular", glm::vec3(1.0f));
//        shader->setFloat("uDirLight.intensity", lightIntensity);
//
//        shader->setFloat("uMaterial.shininess", 32.0f);
//
//        model->draw(*shader);
//    }

    // Box
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);

        auto shader = ShaderManager::instance().get("basic");

        shader->activate();

        camera.project(*shader);

        boxTexture->activate(GL_TEXTURE0);

        shader->setMat4("uMatModel", glm::identity<glm::mat4>());

        cubeVAO.bind();
        cubeIBO.bind();

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
    }

    // Skybox
    {
        auto skyboxShader = ShaderManager::instance().get("skybox");

		glCullFace(GL_FRONT);  // Show the "inward" faces of the cubemap
        glDepthFunc(GL_LEQUAL);

        skyboxShader->activate();

        camera.project(*skyboxShader);
		skyboxShader->setMat4("uMatView", glm::mat4(glm::mat3(camera.getViewMatrix())));

        skyboxVAO.bind();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glCullFace(GL_BACK);
        glDepthFunc(GL_LESS);
    }
}

void ModelViewerScene::renderUi()
{
	ImGui::SliderFloat("Light Intensity", &lightIntensity, 1.0f, 10.0f);
}
