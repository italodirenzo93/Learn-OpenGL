#ifndef CAMERA_H
#define CAMERA_H

#include "CommonInclude.h"

class Camera
{
public:
	explicit Camera(float aspectRatio, const glm::vec3 &pos, const glm::vec3 &eulerAngles);

	float fieldOfView = 45.0f;
	float aspectRatio;

	glm::vec3 position;

	glm::mat4 getProjectionMatrix() const;
	glm::mat4 getViewMatrix() const;

	glm::vec3 getForwardVector() const;
	glm::vec3 getUpVector() const;

	float getPitch() const { return _pitch; }
	float getYaw() const { return _yaw; }

	void setPitch(float pitch);
	void setYaw(float yaw);

protected:
	glm::vec3 _direction;
	float _pitch;
	float _yaw;

	void updateDirection();

private:
	NON_COPYABLE_OR_MOVABLE_CLASS(Camera)
};

#endif
