#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(Model* model) {
	this->model = model;
}
std::vector<Message> ParticleEmitter::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);
	if (runtime > lastEmissionTime + emissionInterval) {
		Message m = Message();
		m.caller = this;
		m.type = add_particle;
		m.other = new Particle(model);
		m.other->color = glm::vec3(1.f, 1.f, 0.f);
		float s = ((rand() % 100) / 400.f) + .25f;
		m.other->setScale(glm::vec3(s, s, s));
		m.other->setRotationAxis(glm::vec3(((rand() % 100) / 100.f), ((rand() % 100) / 100.f), ((rand() % 100) / 100.f)));
		m.other->setRotation((rand() % 100) / 31.415f);
		m.other->setPosition(lastParentMatrix * glm::vec4( ((rand() % 100)/100.f) - .5f, 0.f, -6.f, 1.f));
		messages.push_back(m);
		lastEmissionTime = runtime;
	}
	return messages;
}