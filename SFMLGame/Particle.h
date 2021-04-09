#pragma once
#include "Node3D.h"
class Particle : public Node3D
{
public:
	Particle(Model* model, glm::vec3 direction, std::vector<glm::vec3> colors, float lifeTime, float speed);
	std::vector<Message> update(float dt, float runtime);
protected:
	float startTime;
	float lifetime;
	glm::vec3 direction;
	std::vector<glm::vec3> colors;
};

