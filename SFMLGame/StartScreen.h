#pragma once
#include "Node.h"
#include "ResourceManager.h"
#include "Space.h"

class StartScreen : public Node
{
public:
	StartScreen();
	std::vector<Message> onInputEvent(sf::Event event, float runtime);
	std::vector<Message> update(float dt, float runtime);
};

