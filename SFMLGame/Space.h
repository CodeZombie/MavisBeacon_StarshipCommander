#pragma once
#include "Node.h"
#include "Asteroid.h"
#include "Planet.h"
#include "Plasma.h"
#include "StarField.h"
class Space : public Node
{
public:
	Space();
	std::vector<Message> update(float dt, float runtime);
};

