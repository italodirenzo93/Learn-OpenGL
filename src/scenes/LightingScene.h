#ifndef LIGHTINGSCENE_H
#define LIGHTINGSCENE_H

#include "Scene.h"
#include "Material.h"

class LightingScene : public Scene
{
public:
	explicit LightingScene(std::shared_ptr<Camera> camera);
	~LightingScene();

	virtual void render(float deltaTime) override;

private:
	std::shared_ptr<Camera> _camera;
	std::unique_ptr<Shader> _program, _lightProgram;
	Material _material;

	unsigned int _vao, _vbo, _lightVao, _diffuseMap, _specularMap;

	NON_COPYABLE_OR_MOVABLE_CLASS(LightingScene)
};

#endif
