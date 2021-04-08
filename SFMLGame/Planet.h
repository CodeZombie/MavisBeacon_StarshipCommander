#pragma once
#include "Node3D.h"
#include "ModelManager.h"
class Planet : public Node3D
{
public:
	Planet();
	std::vector<Message> update(float dt, float runtime);
};

