#include "PlayerShip.h"
PlayerShip::PlayerShip() : Node3D(ResourceManager::getModel("player_ship")) {
	rotationAxis = glm::vec3(0,1.f, 0);
	rotation = 3.14159;
	speed = 3;
	ParticleEmitter* p = new ParticleEmitter(ResourceManager::getModel("particle_star"));
	p->setPosition(glm::vec3(.5, -.5, 0));
	p->emissionInterval = 25;
	addChild(p);
}

std::vector<Message> PlayerShip::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);
	if (!arrived_at_target) {
		position.y = sin(runtime / 2000) * 2;
	}

	for (int i = 0; i < messages.size(); i++)
	{
		if (messages[i].type == arrived_at_target && targetToShoot != NULL) {
			Message m = Message();
			m.caller = this;
			m.other = targetToShoot;
			m.type = shoot;
			messages.push_back(m);
			targetToShoot = NULL;
		}
	}

	return messages;
}

void PlayerShip::draw(glm::mat4 parentModel) {
	__super::draw(parentModel);
}

void PlayerShip::shootTarget(Node* target) {
	setTargetPosition(glm::vec3(
		target->getGlobalPosition().x,
		target->getGlobalPosition().y,
		position.z
	));
	targetToShoot = target;
}