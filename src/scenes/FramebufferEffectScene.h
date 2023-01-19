#ifndef FRAMEBUFFER_EFFECT_SCENE_H
#define FRAMEBUFFER_EFFECT_SCENE_H

#include "Scene.h"
#include "Buffer.h"

class FramebufferEffectScene : public Scene
{
public:
	FramebufferEffectScene(const Camera& camera);

	void render(float deltaTime) override;

private:
	const Camera& _camera;

	GLuint fbo = 0;
	GLuint renderTexture = 0;
	GLuint depthTexture = 0;

	VertexBuffer<float> quadVertices;
	GLuint vao = 0;
};

#endif
