#pragma once
#include "Node3D.h"
#include "ParticleEmitter.h"
#include "ModelManager.h"
class PlayerShip : public Node3D
{
public:
	PlayerShip();
	std::vector<Message> update(float dt, float runtime);
};

