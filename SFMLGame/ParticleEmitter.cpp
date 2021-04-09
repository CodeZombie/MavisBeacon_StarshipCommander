#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(glm::vec3 position, Model* model, bool randomDirection, glm::vec3 direction, std::vector<glm::vec3> colors, float particleLifeTime, float emitterLifeTime, glm::vec2 speedRange, float emissionInterval, int initialAmount, glm::vec2 scaleRange) {
	this->model = model;
	this->position = position;
	this->randomDirection = randomDirection;
	this->direction = direction;
	this->colors = colors;
	this->particleLifeTime = particleLifeTime;
	this->emitterLifeTime = emitterLifeTime;
	this->speedRange = speedRange;
	this->emissionInterval = emissionInterval;
	this->initialAmount = initialAmount;
	this->scaleRange = scaleRange;
}

Message ParticleEmitter::getCreateParticleMessage() {
	Message m = Message();
	m.caller = this;
	m.type = add_particle;
	glm::vec3 d = direction;
	if (randomDirection) {
		d = MathHelper::getRandomDirectionVector();
	}
	m.other = new Particle(model, d, colors, particleLifeTime, MathHelper::getRandomRange(speedRange.x, speedRange.y));

	float s = MathHelper::getRandomRange(scaleRange.x, scaleRange.y);
	m.other->setScale(glm::vec3(s, s, s));

	m.other->setRotationAxis(MathHelper::getRandomDirectionVector());
	m.other->setRotation((rand() % 100) / 31.415f);
	m.other->setPosition(getGlobalPosition());
	//m.other->setPosition(lastParentMatrix * glm::vec4( ((rand() % 100)/100.f) - .5f, 0.f, -6.f, 1.f));
	return m;
}

std::vector<Message> ParticleEmitter::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);

		if (emitterStartTime == 0) {
			emitterStartTime = runtime;
			for (int i = 0; i < initialAmount; i++) {
				messages.push_back(getCreateParticleMessage());
			}
		}
		if (emitterLifeTime != -1) {
			if (runtime > emitterStartTime + emitterLifeTime) {
				Message m = Message();
				m.caller = this;
				m.type = destroy_self;
				messages.push_back(m);
			}
		}

	if (runtime > lastEmissionTime + emissionInterval) {
		messages.push_back(getCreateParticleMessage());
		lastEmissionTime = runtime;
	}
	return messages;
}