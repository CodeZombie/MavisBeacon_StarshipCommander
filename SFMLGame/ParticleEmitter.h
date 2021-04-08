#pragma once
#include "Node.h"
#include "Model.h"
#include "Particle.h"
class ParticleEmitter : public Node
{
public:
	ParticleEmitter(Model* model);
	std::vector<Message> update(float dt, float runtime);
	float emissionInterval;
protected:
	Model* model;
	float lastEmissionTime;

};

