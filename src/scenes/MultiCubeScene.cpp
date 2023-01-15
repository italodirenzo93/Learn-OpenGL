//
// Created by Italo Di Renzo on 2023-01-10.
//

#include "MultiCubeScene.h"
#include "ShaderManager.h"

using namespace std;

MultiCubeScene::MultiCubeScene(const Camera& camera) : _camera(camera)
{
    _cubes.emplace_back(glm::vec3(1.26f, -1.0f, -2.0f));
    _cubes.emplace_back(glm::vec3(-1.0f, 1.0f, -1.0f));
    _cubes.emplace_back(glm::vec3(0.0f, 1.0f, 2.0f));

    _lightDir = glm::vec3(-0.2f, -1.0f, -0.3f);

//    ShaderManager::getInstance().preloadShaders();
}

void MultiCubeScene::render(float deltaTime)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto shader = ShaderManager::getInstance().get("single_color");

    shader->activate();

    _camera.project(*shader);

    shader->setVec3("uDirLight.direction", _lightDir);
    shader->setVec3("uDirLight.ambient", glm::vec3(0.2f));
    shader->setVec3("uDirLight.diffuse", glm::vec3(0.5f));
    shader->setVec3("uDirLight.specular", glm::vec3(1.0f));

    for (auto& cube : _cubes)
        cube.draw(*shader);
}

void MultiCubeScene::renderUi()
{
    for (unsigned int i = 0; i < _cubes.size(); i++)
    {
        ImGui::DragFloat3(("Cube Position " + to_string(i)).c_str(), glm::value_ptr(_cubes[i].transform.translation), 0.1f);
        ImGui::DragFloat3(("Cube Rotation " + to_string(i)).c_str(), glm::value_ptr(_cubes[i].transform.rotation));
    }

    ImGui::Separator();

    ImGui::DragFloat3("Light Direction", glm::value_ptr(_lightDir), 0.1);
}
