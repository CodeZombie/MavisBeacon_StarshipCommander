#pragma once
#include "Node3D.h"
#include "ResourceManager.h"
#include "MathHelper.h"
class Asteroid : public Node3D
{
public:
	Asteroid();
	std::vector<Message> update(float dt, float runtime);
};

