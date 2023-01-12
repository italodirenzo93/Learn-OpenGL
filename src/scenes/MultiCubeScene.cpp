//
// Created by Italo Di Renzo on 2023-01-10.
//

#include "MultiCubeScene.h"

MultiCubeScene::MultiCubeScene(const Camera& camera) : _camera(camera), _shader("./resources/shaders/mesh.vert", "./resources/shaders/single_color.frag")
{
    memset(_clearColor, 0, 3);

    _cubes.emplace_back(glm::vec3(0.26f, 0.0f, 0.0f));
    _cubes.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f));
    _cubes.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));
}

void MultiCubeScene::render(float deltaTime)
{
//    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
    glClearColor(_clearColor[0], _clearColor[1], _clearColor[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shader.activate();

    _camera.project(_shader);

    for (auto& cube : _cubes)
        cube.draw(_shader);
}

void MultiCubeScene::renderUi()
{
//    ImGui::Begin("Clear");
//
//    ImGui::BeginGroup();
//    ImGui::ColorPicker3("Clear Color", _clearColor);
//    ImGui::EndGroup();
//
//    ImGui::BeginGroup();
//    ImGui::DragFloat("Depth Value", &_depthValue, 0.01f, 0.0f, 1.0f);
//    ImGui::EndGroup();
//
//    ImGui::End();
}
