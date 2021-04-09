#pragma once
#include "Node.h"
#include "Model.h"
#include "Particle.h"
class ParticleEmitter : public Node
{
public:
	ParticleEmitter(glm::vec3 position, Model* model, bool randomDirection, glm::vec3 direction, std::vector<glm::vec3> colors, float particleLifeTime, float emitterLifeTime, glm::vec2 speedRange, float emissionInterval, int initialAmount, glm::vec2 scaleRange);
	std::vector<Message> update(float dt, float runtime);
	Message getCreateParticleMessage();
	float emissionInterval;
protected:
	Model* model;
	float lastEmissionTime;
	float emitterLifeTime;
	float particleLifeTime;
	std::vector<glm::vec3> colors;
	bool randomDirection; 
	glm::vec3 direction;
	float emitterStartTime = 0;
	int initialAmount;
	glm::vec2 scaleRange;
	glm::vec2 speedRange;
};

