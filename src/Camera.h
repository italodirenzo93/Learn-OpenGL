#ifndef CAMERA_H
#define CAMERA_H

#include "CommonInclude.h"
#include "Shader.h"

class Camera
{
public:
	Camera(float aspectRatio, const glm::vec3 &pos, const glm::vec3 &up);

	float fieldOfView = 45.0f;
	float aspectRatio;

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float pitch = 0.0f;
	float yaw = -90.0f;

	glm::mat4 getProjectionMatrix() const;
	glm::mat4 getViewMatrix() const;

    void project(const Shader& shader) const;
    void unproject(const Shader& shader) const;

	void update();

private:
	NON_COPYABLE_OR_MOVABLE_CLASS(Camera)
};

#endif
