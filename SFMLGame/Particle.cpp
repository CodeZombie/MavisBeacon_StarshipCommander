#include "Particle.h"

Particle::Particle(Model* model) : Node3D(model){
	scale = glm::vec3(.25f, .25f, .25f);
	lifetime = 1000;
	model->useTexture = false;
	speed = 12;
}

std::vector<Message> Particle::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);
	color.x -= 1.f * dt;
	color.y -= 1.f * dt;
	color.z -= 1.f * dt;

	scale.x -= .5 * dt;
	scale.y -= .5 * dt;
	scale.z -= .5 * dt;
	if (startTime == 0) {
		startTime = runtime;
	}
	
	if (runtime > startTime + lifetime) {
		Message m = Message();
		m.caller = this;
		m.type = destroy_self;
		messages.push_back(m);
	}
	
	position.z += speed * dt;
	return messages;
}