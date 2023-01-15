#ifndef MESH_LOADING_SCENE_H
#define MESH_LOADING_SCENE_H

#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
#include "Scene.h"
#include "Shader.h"
#include "Texture.h"

class MeshLoadingScene : public Scene
{
public:
	explicit MeshLoadingScene(const std::shared_ptr<Camera>& camera);

	void render(float deltaTime) override;

private:
	std::shared_ptr<Camera> _camera;
	std::unique_ptr<Mesh> _mesh;
    std::unique_ptr<Model> _model;

    std::shared_ptr<Texture> _diffuse;
    std::shared_ptr<Texture> _specular;
};

#endif
