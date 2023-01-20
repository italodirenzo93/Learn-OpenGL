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
    {
        glGenTextures(1, &cubemapID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);

        string basePath = "./resources/textures/skybox/";

        int width, height, nChannels;
        for (uint32_t i = 0; i < texture_faces.size(); i++)
        {
            unsigned char *data = stbi_load((basePath + texture_faces[i]).c_str(), &width, &height, &nChannels, STBI_default);

            if (data) {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                             data);
            } else {
                cout << "Failed to load cubemap texture " << texture_faces[i] << endl;
            }

            stbi_image_free(data);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

//    cubemapVBO.setData({});

    util::createCube(cubeVBO, cubeIBO);

    cubeVAO.addBinding({ POSITION, 3, GL_FLOAT, false })
        .addBinding({NORMAL, 3, GL_FLOAT, false})
        .addBinding({ TEXCOORD, 2, GL_FLOAT, false });

    cubeVAO.mapToBuffer<float, 8>(cubeVBO);

    skyboxVAO.addBinding({POSITION, 3, GL_FLOAT, false});
    skyboxVAO.mapToBuffer<float, 8>(cubeVBO);

    boxTexture = make_unique<Texture>("./resources/textures/container.jpg");
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
//        glEnable(GL_CULL_FACE);
//        glCullFace(GL_BACK);
//        glFrontFace(GL_CW);

        auto shader = ShaderManager::instance().get("basic");

        shader->activate();

        camera.project(*shader);

        boxTexture->activate(GL_TEXTURE0);
        shader->setInt("uTexture", 0);

        shader->setMat4("uMatModel", glm::identity<glm::mat4>());

        cubeVAO.bind();
        cubeIBO.bind();

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
    }

    // Skybox
    {
//        glDisable(GL_CULL_FACE);

        auto skyboxShader = ShaderManager::instance().get("skybox");

//        glDepthMask(GL_FALSE);
        glDepthFunc(GL_LEQUAL);

        skyboxShader->activate();

        camera.project(*skyboxShader);

        skyboxVAO.bind();
//        cubeIBO.bind();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);
        skyboxShader->setInt("uCubemap", 0);

        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

        glDepthFunc(GL_LESS);
    }
}

void ModelViewerScene::renderUi()
{
	ImGui::SliderFloat("Light Intensity", &lightIntensity, 1.0f, 10.0f);
}
