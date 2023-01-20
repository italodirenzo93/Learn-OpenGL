#ifndef MODEL_VIEWER_SCENE_H
#define MODEL_VIEWER_SCENE_H

#include "Scene.h"
#include "Model.h"
#include "Camera.h"
#include "Buffer.h"
#include "VertexArrayLayout.h"
#include "Texture.h"


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

    uint32_t cubemapID;

    VertexBuffer<float> cubemapVBO;
    IndexBuffer cubemapIBO;
    VertexArrayLayout cubemapVAO;

    std::unique_ptr<Texture> boxTexture;

private:
	NON_COPYABLE_OR_MOVABLE_CLASS(ModelViewerScene)
};

#endif
