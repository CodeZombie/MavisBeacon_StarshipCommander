#pragma once
#include "Node3D.h"
#include "ParticleEmitter.h"
#include "ResourceManager.h"
class PlayerShip : public Node3D
{
public:
	PlayerShip();
	std::vector<Message> update(float dt, float runtime);
	void draw(glm::mat4 parentModel);
	void shootTarget(Node* target);
private:
	Node* targetToShoot;
};

