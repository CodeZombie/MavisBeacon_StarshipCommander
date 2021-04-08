#include "Asteroid.h"


Asteroid::Asteroid() : Node3D(ModelManager::getModel("asteroid")) {
	rotationAxis = glm::vec3(0, 1.f, 0);
	float s = ((rand() % 10) / 5.f) + 1.f;
	setScale(glm::vec3(s, s, s));
	speed = ((rand() % 150) + 15.f);
}

std::vector<Message> Asteroid::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);

	rotation += 1 * dt;
	position.z += speed * dt;

	if (position.z > 15) {
		Message m = Message();
		m.caller = this;
		m.type = destroy_self;
		messages.push_back(m);
	}
	return messages;
}