#pragma once
#include "Camera.h"
#include "Node.h"
#include "Message.h"
#include "PlayerShip.h"
#include "Asteroid.h"
#include "ModelManager.h"
#include "UFO.h"
#include "EnemyManager.h"
#include "UserInterface.h"
#include "Planet.h"
#include "Plasma.h"
#include "StarField.h"
class GameDirector
{
public:
	GameDirector();
	void Update(float dt, float runtime);
	void Draw(sf::RenderWindow* window);
	void KeyPressed(sf::Keyboard::Key key);
private:
	Node* rootNode;
	Camera* camera;
	PlayerShip* playerShip;
	EnemyManager* enemyManager;
};

