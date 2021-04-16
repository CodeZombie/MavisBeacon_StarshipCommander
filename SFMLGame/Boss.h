#pragma once
#include "Node3D.h"
#include "ResourceManager.h"
#include "GameUserInterface.h"
class Boss :public Node3D
{
public:
	Boss(std::vector<std::string> strings);
	std::vector<Message> update(float dt, float runtime);
	std::vector<Message> onInputEvent(sf::Event event, float runtime);
	void getHurt();
	std::vector<std::string> words;
	int sentenceCursor = 0;
	std::string word;
	int wordCursor = 0;
};

