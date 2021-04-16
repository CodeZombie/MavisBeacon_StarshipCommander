#pragma once
#include <map>
#include "Node.h"
#include <vector>
#include<string.h>
#include "SFML/Graphics.hpp" 
#include <iostream>
#include "ResourceManager.h"
class GameUserInterface : public Node
{
public:
	GameUserInterface();
	std::vector<Message> update(float dt, float runtime);
	void setCPM(float cpm);
	void setHealth(int h);
	int averageCPM;
	int health;
};

