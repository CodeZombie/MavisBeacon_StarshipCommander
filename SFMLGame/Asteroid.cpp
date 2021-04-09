#include "Asteroid.h"


Asteroid::Asteroid() : Node3D(ResourceManager::getModel("asteroid")) {
	rotationAxis = MathHelper::getRandomDirectionVector();
	float s = ((rand() % 10) / 3.f) + 2.f;
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