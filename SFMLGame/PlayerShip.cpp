#include "PlayerShip.h"
PlayerShip::PlayerShip() : Node3D(ModelManager::getModel("player_ship")) {
	rotationAxis = glm::vec3(0,1.f, 0);
	rotation = 3.14159;
	ParticleEmitter* p = new ParticleEmitter(ModelManager::getModel("particle_star"));
	p->setPosition(glm::vec3(.5, -.5, 0));
	p->emissionInterval = 25;
	addChild(p);

	addChild(new Particle(ModelManager::getModel("particle_star")));
}

std::vector<Message> PlayerShip::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);
	position.y = sin(runtime / 2000) * 2;
	//rotation += 5 * dt;


	return messages;
}