#pragma once
#include "Node.h"
#include "ResourceManager.h"
class DeathScreen :
	public Node
{
public:
	DeathScreen();
	std::vector<Message> onInputEvent(sf::Event event, float runtime);
};

