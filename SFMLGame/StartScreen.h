#pragma once
#include "Node.h"
#include "ResourceManager.h"
class StartScreen : public Node
{
public:
	StartScreen();
	std::vector<Message> onInputEvent(sf::Event event, float runtime);
};

