#include "MeshLoadingScene.h"

#include <array>

static constexpr uint32_t NUM_ELEMENTS = 36;
static constexpr uint32_t STRIDE = 8;

static const std::array<float, NUM_ELEMENTS * STRIDE> vertices{
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
};

static const std::array<uint32_t, NUM_ELEMENTS> indices{0,1,2,0,2,3,4,5,6,4,6,7,8,9,10,8,10,11,12,13,14,12,14,15,16,17,18,16,18,19,20,21,22,20,22,23};

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
    _program = std::make_unique<Shader>("./resources/shaders/mesh.vert", "./resources/shaders/mesh.frag");
    _outlineShader = std::make_unique<Shader>("./resources/shaders/mesh.vert", "./resources/shaders/single_color.frag");
    _model = std::make_unique<Model>("./resources/objects/backpack/backpack.obj");

    glEnable(GL_STENCIL_TEST);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
}

MeshLoadingScene::~MeshLoadingScene()
{
}

void MeshLoadingScene::render(float deltaTime)
{
    glEnable(GL_DEPTH_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    _program->activate();

    glStencilFunc(GL_ALWAYS, 1, 0xFF); // all fragments pass the stencil test
    glStencilMask(0xFF); // enable writing to the stencil buffer

    _program->setVec3("uViewPos", _camera->position);

    _program->setMat4("uMatProjection", _camera->getProjectionMatrix());
    _program->setMat4("uMatView", _camera->getViewMatrix());
    _program->setMat4("uMatModel", glm::mat4(1.0f));
    _program->setMat4("uMatNormal", glm::transpose(glm::inverse(glm::mat4(1.0f))));

    _program->setVec3("uDirLight.direction", dirLight.direction);
    _program->setVec3("uDirLight.ambient", dirLight.ambient);
    _program->setVec3("uDirLight.diffuse", dirLight.diffuse);
    _program->setVec3("uDirLight.specular", dirLight.specular);

    _program->setVec3("uPointLights[0].position", 0.0f, 1.0f, 0.0f);
    _program->setVec3("uPointLights[0].ambient", dirLight.ambient);
    _program->setVec3("uPointLights[0].diffuse", dirLight.diffuse);
    _program->setVec3("uPointLights[0].specular", dirLight.specular);
    _program->setFloat("uPointLights[0].constant", dirLight.constant);
    _program->setFloat("uPointLights[0].linear", dirLight.linear);
    _program->setFloat("uPointLights[0].quadratic", dirLight.quadratic);

    _program->setFloat("uMaterial.shininess", 32.0f);
//    _mesh->draw(*_program);
    _model->draw(*_program);

    _program->deactivate();

    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00); // disable writing to the stencil buffer
    glDisable(GL_DEPTH_TEST);
    {
        _outlineShader->activate();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(1.05f));

        _outlineShader->setMat4("uMatProjection", _camera->getProjectionMatrix());
        _outlineShader->setMat4("uMatView", _camera->getViewMatrix());
        _outlineShader->setMat4("uMatModel", model);
        _outlineShader->setMat4("uMatNormal", glm::transpose(glm::inverse(model)));

        _model->draw(*_outlineShader);
        _outlineShader->deactivate();
    }
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glEnable(GL_DEPTH_TEST);
}
