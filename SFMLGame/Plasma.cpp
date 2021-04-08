#include "Plasma.h"
Plasma::Plasma() :Node3D(ModelManager::getModel("plasma")) {
	setPosition(glm::vec3(-750.f,500.f, -900.f));
	setScale(glm::vec3(400.f, 400.f, 400.f));
}
std::vector<Message> Plasma::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);
	return messages;
}