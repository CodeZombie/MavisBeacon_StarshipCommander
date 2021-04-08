#pragma once
#include "Node3D.h"
#include "ModelManager.h"
class Asteroid : public Node3D
{
public:
	Asteroid();
	std::vector<Message> update(float dt, float runtime);
};

