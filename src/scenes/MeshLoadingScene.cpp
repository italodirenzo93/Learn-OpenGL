#include "MeshLoadingScene.h"
#include "ShaderManager.h"

struct Light
{
    enum {
        DirectionalLight,
        PointLight,
        SpotLight
    } type = DirectionalLight;

    glm::vec3 ambient = glm::vec3(0.2f);
    glm::vec3 diffuse = glm::vec3(0.5f);
    glm::vec3 specular = glm::vec3(1.0f);

    // Directional light only
    glm::vec3 direction = glm::vec3(-0.2f, -1.0f, -0.3f);

    // Point light only
    glm::vec3 position = glm::vec3(0.0f);

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    // Spotlight only
    float cutoff = glm::cos(glm::radians(12.5f));
    float outerCutoff = glm::cos(glm::radians(17.5f));
};

static Light dirLight;

MeshLoadingScene::MeshLoadingScene(const std::shared_ptr<Camera> &camera)
{
    _camera = camera;
    _model = std::make_unique<Model>("./resources/objects/backpack/backpack.obj");

    glEnable(GL_STENCIL_TEST);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);
}

void MeshLoadingScene::render(float deltaTime)
{
    glEnable(GL_DEPTH_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    auto objectShader = ShaderManager::instance().get("mesh");

    objectShader->activate();

    glStencilFunc(GL_ALWAYS, 1, 0xFF); // all fragments pass the stencil test
    glStencilMask(0xFF); // enable writing to the stencil buffer

    objectShader->setVec3("uViewPos", _camera->position);

    objectShader->setMat4("uMatProjection", _camera->getProjectionMatrix());
    objectShader->setMat4("uMatView", _camera->getViewMatrix());
    objectShader->setMat4("uMatModel", glm::mat4(1.0f));
    objectShader->setMat4("uMatNormal", glm::transpose(glm::inverse(glm::mat4(1.0f))));

    objectShader->setVec3("uDirLight.direction", dirLight.direction);
    objectShader->setVec3("uDirLight.ambient", dirLight.ambient);
    objectShader->setVec3("uDirLight.diffuse", dirLight.diffuse);
    objectShader->setVec3("uDirLight.specular", dirLight.specular);

    objectShader->setVec3("uPointLights[0].position", 0.0f, 1.0f, 0.0f);
    objectShader->setVec3("uPointLights[0].ambient", dirLight.ambient);
    objectShader->setVec3("uPointLights[0].diffuse", dirLight.diffuse);
    objectShader->setVec3("uPointLights[0].specular", dirLight.specular);
    objectShader->setFloat("uPointLights[0].constant", dirLight.constant);
    objectShader->setFloat("uPointLights[0].linear", dirLight.linear);
    objectShader->setFloat("uPointLights[0].quadratic", dirLight.quadratic);

    objectShader->setFloat("uMaterial.shininess", 32.0f);
//    _mesh->draw(*objectShader);
    _model->draw(*objectShader);

    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00); // disable writing to the stencil buffer
    glDisable(GL_DEPTH_TEST);
    {
        auto outlineShader = ShaderManager::instance().get("single_color");
        outlineShader->activate();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(1.05f));

        outlineShader->setMat4("uMatProjection", _camera->getProjectionMatrix());
        outlineShader->setMat4("uMatView", _camera->getViewMatrix());
        outlineShader->setMat4("uMatModel", model);
        outlineShader->setMat4("uMatNormal", glm::transpose(glm::inverse(model)));

        _model->draw(*outlineShader);
        outlineShader->deactivate();
    }
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glEnable(GL_DEPTH_TEST);
}
