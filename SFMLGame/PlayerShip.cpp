#include "PlayerShip.h"
PlayerShip::PlayerShip() : Node3D(ResourceManager::getModel("player_ship")) {
	rotationAxis = glm::vec3(0,1.f, 0);
	rotation = 3.14159;
	speed = 2;
	std::vector< glm::vec3> c;
	c.push_back(glm::vec3(1, 1, 1));
	c.push_back(glm::vec3(1, 1, 0));
	c.push_back(glm::vec3(1, 0, 0));
	c.push_back(glm::vec3(1, 0, 0));
	c.push_back(glm::vec3(0, 0, 0));
	ParticleEmitter* p = new ParticleEmitter(glm::vec3(0, 0, -8), ResourceManager::getModel("particle_star"), false, glm::vec3(0, 0, 1), c, 1000, -1, glm::vec2(14, 16), .5, 0, glm::vec2(.3, .7));
	p->emissionInterval = 25;
	addChild(p);
}

std::vector<Message> PlayerShip::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);
	if (targetPositions.size() == 0) {
		moveTowardPoint(glm::vec3(position.x, sin(runtime / 2000) * 2, position.z), dt);
		//position.y = sin(runtime / 2000) * 2;
	}

	if (targetPositions.size() == 0) {

		if (targetNodeDistance == 0 && targetNodes.size() > 0) {
			targetNodeDistance += speed * dt;
			targetNodeStartPosition = position;
		}
		if (targetNodeDistance > 0) {
			position.x = MathHelper::smoothstep(targetNodeStartPosition.x, targetNodes[0]->getGlobalPosition().x, targetNodeDistance);
			position.y = MathHelper::smoothstep(targetNodeStartPosition.y, targetNodes[0]->getGlobalPosition().y, targetNodeDistance);
			targetNodeDistance += speed * dt;
			if (targetNodeDistance >= 1.0f) {
				Message m = Message();
				m.caller = this;
				m.type = arrived_at_target_node;
				m.other = targetNodes[0];
				messages.push_back(m);
				targetNodeDistance = 0.f;
				targetNodes.erase(targetNodes.begin());

				if (targetNodes.size() == 0) {
					addTargetPosition(glm::vec3(0));
				}
			}
		}

	}

	return messages;
}

void PlayerShip::draw(glm::mat4 parentModel) {
	__super::draw(parentModel);
}

void PlayerShip::shootTarget(Node* target) {
	targetNodes.push_back(target);
}

void PlayerShip::getHurt() {
	health -= 10;
}