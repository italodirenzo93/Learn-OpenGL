#include "Camera.h"

Camera::Camera(float aspectRatio, const glm::vec3 &pos, const glm::vec3 &eulerAngles)
	: aspectRatio(aspectRatio), position(pos), _yaw(eulerAngles.x), _pitch(eulerAngles.y)
{
	updateDirection();
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

void Camera::project(const Shader& shader) const
{
    shader.setVec3("uViewPos", position);
    shader.setMat4("uMatProjection", getProjectionMatrix());
    shader.setMat4("uMatView", getViewMatrix());
}

void Camera::unproject(const Shader& shader) const
{
    shader.setVec3("uViewPos", glm::vec3(0.0f));
    shader.setMat4("uMatProjection", glm::identity<glm::mat4>());
    shader.setMat4("uMatView", glm::identity<glm::mat4>());
}
