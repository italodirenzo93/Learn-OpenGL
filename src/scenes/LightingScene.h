#ifndef LIGHTINGSCENE_H
#define LIGHTINGSCENE_H

#include "Scene.h"
#include "Material.h"
#include "Texture.h"
#include "Buffer.h"

struct Vertex
{
	float x, y, z;
	float normalX, normalY, normalZ;
	float texCoordX, texCoordY;

	Vertex()
		: x(0.0f), y(0.0f), z(0.0f),
		  normalX(0.0f), normalY(0.0f), normalZ(0.0f),
		  texCoordX(0.0f), texCoordY(0.0f) {}

	Vertex(float x, float y, float z, float normalX, float normalY, float normalZ, float texCoordX, float texCoordY)
		: x(x), y(y), z(z),
		  normalX(normalX), normalY(normalY), normalZ(normalZ),
		  texCoordX(texCoordX), texCoordY(texCoordY) {}
};

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
	Texture _diffuseMap, _specularMap;
	ArrayBuffer<Vertex> _vbo;

	uint32_t _vao, _lightVao;

	NON_COPYABLE_OR_MOVABLE_CLASS(LightingScene)
};

#endif
