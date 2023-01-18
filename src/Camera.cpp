#include "Camera.h"

Camera::Camera(float aspectRatio, const glm::vec3 &pos, const glm::vec3 &up)
	: aspectRatio(aspectRatio), position(pos), up(up), worldUp(up)
{
	update();
}

glm::mat4 Camera::getProjectionMatrix() const
{
	return glm::perspective(glm::radians(fieldOfView), aspectRatio, 0.1f, 100.0f);
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(position, position + front, up);
}

void Camera::update()
{
	front = glm::vec3(1.0f);

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
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
