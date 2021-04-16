#pragma once
#include "Node.h"
#include "UFO.h"
#include "Dictionary.h"
#include "GameState.h"
#include "WordAsteroid.h"
#include "HealthPickup.h"
#include "Boss.h"

//this class ensures there are only a set number of enemies in the scene at a given time.
//manages their behaviour
enum EnemyManagerState {
	stage_running,
	idle,
};

class EnemyManager :public Node
{
public:
	EnemyManager();
	GameState state;
	EnemyManagerState emState;
	std::vector<Message> update(float dt, float runtime);
	void createEnemy(std::string word, glm::vec3 startPosition, glm::vec3 targetPosition);
	void startStage(float runtime);
	std::vector<Message> onInputEvent(sf::Event event, float runtime);
	void createAsteroid(std::string word, glm::vec3 startPosition);
	Node* activeTarget;
	float stageStartTime;
	float stageFinishedTime;
	float stageIntervalTime;
	int shotsThisStage = 0;
	int livingEnemies;
};

