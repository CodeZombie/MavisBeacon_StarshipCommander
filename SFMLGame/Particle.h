#pragma once
#include "Node3D.h"
class Particle : public Node3D
{
public:
	Particle(Model* model);
	std::vector<Message> update(float dt, float runtime);
protected:
	float startTime;
	float lifetime;
};

