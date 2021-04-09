#include "Camera.h"

sf::Vector3f Camera::position;
sf::Vector3f Camera::lookAt;
float Camera::FoV;
float Camera::projectionNear;
float Camera::projectionFar;
float Camera::screenWidth;
float Camera::screenHeight;

void Camera::initialize(sf::Vector3f position, sf::Vector3f lookAt) {
	Camera::position = position;
	Camera::lookAt = lookAt;
}

void Camera::DefineViewingMatrix() {
	glMultMatrixf(glm::value_ptr(glm::lookAt(glm::vec3(position.x, position.y, position.z), glm::vec3(lookAt.x, lookAt.y, lookAt.z), glm::vec3(0, 1, 0))));
}

glm::mat4 Camera::getViewingMatrix() {
	return glm::lookAt(glm::vec3(position.x, position.y, position.z), glm::vec3(lookAt.x, lookAt.y, lookAt.z), glm::vec3(0, 1, 0));
}

glm::mat4 Camera::getProjectionMatrix() {
	return glm::perspective(glm::radians(FoV), (GLfloat)screenWidth / (GLfloat)screenHeight, projectionNear, projectionFar);
}