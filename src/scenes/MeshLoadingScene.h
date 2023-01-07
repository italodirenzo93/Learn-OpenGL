#ifndef MESH_LOADING_SCENE_H
#define MESH_LOADING_SCENE_H

#include "Camera.h"
#include "Mesh.h"
#include "Scene.h"
#include "Shader.h"
#include "Texture.h"

class MeshLoadingScene : public Scene
{
public:
	explicit MeshLoadingScene(const std::shared_ptr<Camera>& camera);
    ~MeshLoadingScene();

	void render(float deltaTime) override;

private:
	std::shared_ptr<Camera> _camera;
	std::unique_ptr<Shader> _program;
	std::unique_ptr<Mesh> _mesh;

    std::shared_ptr<Texture> _diffuse;
    std::shared_ptr<Texture> _specular;
    Material _material;
};

#endif