#pragma once
#include "Node3D.h"
#include "ResourceManager.h"
class Planet : public Node3D
{
public:
	Planet();
	std::vector<Message> update(float dt, float runtime);
};

