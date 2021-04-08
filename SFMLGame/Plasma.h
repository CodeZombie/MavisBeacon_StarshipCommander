#pragma once
#include "Node3D.h"
#include "ModelManager.h"
class Plasma :
	public Node3D
{
public:
	Plasma();
	std::vector<Message> update(float dt, float runtime);
};

