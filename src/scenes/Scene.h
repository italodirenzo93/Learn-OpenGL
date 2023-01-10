#ifndef SCENE_H
#define SCENE_H

#include "CommonInclude.h"
#include "Shader.h"
#include "Camera.h"

class Scene
{
public:
	virtual void render(float deltaTime) {}
    virtual void renderUi() {}
};

class BasicScene : public Scene
{
public:
	explicit BasicScene(std::shared_ptr<Camera> camera);
	~BasicScene();

	virtual void render(float deltaTime) override;

private:
	std::shared_ptr<Camera> camera;
	std::unique_ptr<Shader> program;
	unsigned int VBO, VAO, EBO, texture1, texture2;

	NON_COPYABLE_OR_MOVABLE_CLASS(BasicScene)
};

#endif
