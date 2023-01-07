#include "MeshLoadingScene.h"

#include <array>

static constexpr uint32_t NUM_ELEMENTS = 36;

static const std::array<float, NUM_ELEMENTS * 8> vertices{
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
    _diffuse = std::make_shared<Texture>("./resources/textures/container2.png");
    _specular = std::make_shared<Texture>("./resources/textures/container2_specular.png");

    std::vector<Mesh::Vertex> vertexData;
    for (uint32_t i = 0; i < NUM_ELEMENTS * 8; i += 8)
    {
        Mesh::Vertex v = {};
        v.position = glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
        v.normal = glm::vec3(vertices[i + 3], vertices[i + 4], vertices[i + 5]);
        v.texCoords = glm::vec2(vertices[i + 6], vertices[i + 7]);
        vertexData.push_back(v);
    }

    std::vector<uint32_t> indexData(indices.begin(), indices.end());

    _material.diffuse = _diffuse;
    _material.specular = _specular;

    _mesh = std::make_unique<Mesh>(vertexData, indexData, _material);
}

MeshLoadingScene::~MeshLoadingScene()
{
}

void MeshLoadingScene::render(float deltaTime)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _program->activate();

    _program->setVec3("uViewPos", _camera->position);

    _program->setMat4("uMatProjection", _camera->getProjectionMatrix());
    _program->setMat4("uMatView", _camera->getViewMatrix());
    _program->setMat4("uMatModel", glm::mat4(1.0f));
    _program->setMat4("uMatNormal", glm::transpose(glm::inverse(glm::mat4(1.0f))));

    _program->setVec3("uDirLight.position", dirLight.position);
    _program->setVec3("uDirLight.ambient", dirLight.ambient);
    _program->setVec3("uDirLight.diffuse", dirLight.diffuse);
    _program->setVec3("uDirLight.specular", dirLight.specular);

    _program->setVec3("uPointLights[0].position", 0.0f, 0.0f, 1.0f);
    _program->setVec3("uPointLights[0].ambient", dirLight.ambient);
    _program->setVec3("uPointLights[0].diffuse", dirLight.diffuse);
    _program->setVec3("uPointLights[0].specular", dirLight.specular);
    _program->setFloat("uPointLights[0].constant", dirLight.constant);
    _program->setFloat("uPointLights[0].linear", dirLight.linear);
    _program->setFloat("uPointLights[0].quadratic", dirLight.quadratic);

    _mesh->draw(*_program);

    _program->deactivate();
}
