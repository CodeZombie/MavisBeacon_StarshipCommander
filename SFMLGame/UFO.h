#pragma once
#include "Node3D.h"
#include "ModelManager.h"
#include "UserInterface.h"
class UFO :public Node3D
{
public:
	UFO(std::string word);
	~UFO();
	std::vector<Message> update(float dt, float runtime);
	void draw(Camera* camera, glm::mat4 parentModel);
	void letterHit();
	std::string word;
	int wordCursor = 0;
	sf::Text* hitText;
	sf::Text* text;
};

