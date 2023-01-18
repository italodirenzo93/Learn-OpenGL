#ifndef MODEL_VIEWER_SCENE_H
#define MODEL_VIEWER_SCENE_H

#include "Scene.h"
#include "Model.h"
#include "Camera.h"

class ModelViewerScene : public Scene
{
public:
	ModelViewerScene(Camera& camera, const char* fileName);

	void render(float deltaTime) override;
	void renderUi() override;

private:
	std::unique_ptr<Model> model;
	Camera& camera;

	float lightIntensity;

private:
	NON_COPYABLE_OR_MOVABLE_CLASS(ModelViewerScene)
};

#endif
