#pragma once
#include "Node.h"
#include "UFO.h"
#include "UserInterface.h"
//this class ensures there are only a set number of enemies in the scene at a given time.
//manages their behaviour
enum EnemyManagerState {
	idle,
	attacking
};

class EnemyManager :public Node
{
public:
	EnemyManager();
	std::vector<Message> update(float dt, float runtime);
	void draw(Camera* camera, glm::mat4 parentModel);
	void createEnemy(std::string word, glm::vec3 startPosition, glm::vec3 targetPosition);
	void KeyPressed(sf::Keyboard::Key key);
	void createEnemies();
	std::vector<UFO*> enemies;
	UFO* activeTarget;
private:
	std::map<sf::Keyboard::Key, char> keys;
};

