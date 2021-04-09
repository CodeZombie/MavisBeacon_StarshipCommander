#pragma once
#include "Node3D.h"
#include "ResourceManager.h"
#include "UserInterface.h"
class UFO :public Node3D
{
public:
	UFO(std::string word);
	std::vector<Message> update(float dt, float runtime);
	std::vector<Message> onInputEvent(sf::Event event);
	std::string word;
	int wordCursor = 0;
};

