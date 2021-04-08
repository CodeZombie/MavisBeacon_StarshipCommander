#include "Planet.h"
Planet::Planet() : Node3D(ModelManager::getModel("planet")) {
	setScale(glm::vec3(
		250,
		250,
		250
	));
	rotationAxis = glm::vec3(0, 1, 0);
}
std::vector<Message> Planet::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);

	rotation += .025 * dt;
	position.z += speed * dt;
	return messages;
}