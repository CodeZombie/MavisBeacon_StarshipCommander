#include "Camera.h"
Camera::Camera(sf::Vector3f position, sf::Vector3f lookAt) {
	this->position = position;
	this->lookAt = lookAt;
	moveStartTime = 0;
}

void Camera::Update(float dt, double time) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		// left key is pressed: move our character
		position.z += 16 * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		// left key is pressed: move our character
		position.z -= 16 * dt;
	}
	if (moveStartTime > 0 && (time - moveStartTime) / 2000 < 1.0f) {
		position.x = lerp(initialPosition.x, targetPosition.x, (time - moveStartTime) / 2000);
		position.y = lerp(initialPosition.y, targetPosition.y, (time - moveStartTime) / 2000);
		position.z = lerp(initialPosition.z, targetPosition.z, (time - moveStartTime) / 2000);
	}
	DefineViewingMatrix();
}
void Camera::DefineViewingMatrix() {
	//gluLookAt(position.x, position.y, position.z, lookAt.x, lookAt.y, lookAt.z, 0, 1, 0);
	//glMultMatrixf(glm::value_ptr(glm::perspective(glm::radians(90.f), (GLfloat)1366.f / (GLfloat)900.f, 1.0f, 10000.f)));
	glMultMatrixf(glm::value_ptr(glm::lookAt(glm::vec3(position.x, position.y, position.z), glm::vec3(lookAt.x, lookAt.y, lookAt.z), glm::vec3(0, 1, 0))));
	//glTranslatef(position.x, position.y, position.z);
}

glm::mat4 Camera::getViewingMatrix() {
	return glm::lookAt(glm::vec3(position.x, position.y, position.z), glm::vec3(lookAt.x, lookAt.y, lookAt.z), glm::vec3(0, 1, 0));
}

float Camera::lerp(float a, float b, float f)
{
	return a + f * (b - a);
}

void Camera::Move(sf::Vector3f pos, double time) {
	initialPosition = position;
	targetPosition = pos;
	moveStartTime = time;
}