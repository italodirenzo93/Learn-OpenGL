//
// Created by Italo Di Renzo on 2023-01-10.
//

#ifndef CMAKEGRAPHICSPROJECT_MULTICUBESCENE_H
#define CMAKEGRAPHICSPROJECT_MULTICUBESCENE_H

#include "Scene.h"
#include "../objects/Cube.h"

class MultiCubeScene : public Scene
{
public:
    explicit MultiCubeScene(const Camera& camera);

    void render(float deltaTime) override;
    void renderUi() override;

private:
    std::vector<Cube> _cubes;
    const Camera& _camera;
    Shader _shader;

    float _clearColor[3];
    float _depthValue = 1.0f;

    NON_COPYABLE_OR_MOVABLE_CLASS(MultiCubeScene)
};


#endif //CMAKEGRAPHICSPROJECT_MULTICUBESCENE_H
