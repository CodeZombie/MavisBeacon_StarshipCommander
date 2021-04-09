#pragma once
#include "Node3D.h"
#include "ResourceManager.h"
class Plasma :
	public Node3D
{
public:
	Plasma();
	std::vector<Message> update(float dt, float runtime);
};

