#pragma once
#include "Node.h"
#include "PlayerShip.h"
#include "UFO.h"
#include "EnemyManager.h"
#include "Space.h"
#include "Bullet.h"
#include "GameState.h"
class GameScene :public Node {
public:
	GameScene();
	std::vector<Message> update(float dt, float runtime);
	std::vector<Message> onInputEvent(sf::Event event);
	std::vector<Message> handleMessages(std::vector<Message> messages);

private:
	std::vector<Node*> toBeShot;
	PlayerShip* playerShip;
	EnemyManager* enemyManager;
	GameState gameState;
};

