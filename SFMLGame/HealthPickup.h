#pragma once
#include "ResourceManager.h"
#include "GameUserInterface.h"
#include "Node3D.h"
class HealthPickup :public Node3D
{
public:
	HealthPickup(std::string word);
	std::vector<Message> update(float dt, float runtime);
	std::vector<Message> onInputEvent(sf::Event event, float runtime);
	void getHurt();
	std::string word;
	int wordCursor = 0;
};

