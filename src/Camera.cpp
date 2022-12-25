#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float aspectRatio, const glm::vec3 &pos)
	: aspectRatio(aspectRatio), position(pos), _direction(0.0f, 0.0f, -1.0f)
{
}

glm::vec3 Camera::getForwardVector() const
{
	return glm::normalize(_direction);
}

glm::vec3 Camera::getUpVector() const
{
	return glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::getProjectionMatrix() const
{
	return glm::perspective(glm::radians(fieldOfView), aspectRatio, 0.1f, 100.0f);
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(position, position + getForwardVector(), getUpVector());
}

void Camera::setPitch(float pitch)
{
	_pitch = pitch;
	updateDirection();
}

void Camera::setYaw(float yaw)
{
	_yaw = yaw;
	updateDirection();
}

void Camera::updateDirection()
{
	_direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_direction.y = sin(glm::radians(_pitch));
	_direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
}
