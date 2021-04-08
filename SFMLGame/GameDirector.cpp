#include "GameDirector.h"

GameDirector::GameDirector() {
	//camera = new Camera(sf::Vector3f(0, -24, 64), sf::Vector3f(0, 0, 0));
	camera = new Camera(sf::Vector3f(0, 4, 12.f), sf::Vector3f(0, 5.f, 0.f));
	ModelManager::addModel("StarSparrow01.objmodel", "StarSparrow_Blue.png", "player_ship");
	ModelManager::addModel("ufo.objmodel", "ufo_texture.png", "ufo");
	ModelManager::addModel("pyramid.objmodel", "light_flare_particle.png", "particle_star");
	ModelManager::addModel("asteroid_a.objmodel", "asteroid.png", "asteroid");
	ModelManager::addModel("planet.objmodel", "planet.png", "planet");
	ModelManager::addModel("plasma_billboard.objmodel", "space_plasma.png", "plasma");
	rootNode = new Node();
	playerShip = new PlayerShip();
	enemyManager = new EnemyManager();
	rootNode->addChild(new StarField());

	Planet* planet = new Planet();
	planet->setPosition(glm::vec3(
		400,
		150,
		-400
	));
	rootNode->addChild(planet);
	rootNode->addChild(new Plasma());
	rootNode->addChild(playerShip);
	rootNode->addChild(enemyManager);
	
}

void GameDirector::KeyPressed(sf::Keyboard::Key key) {
	enemyManager->KeyPressed(key);
}

void GameDirector::Update(float dt, float runtime) {
	std::vector<Node*> nodes = rootNode->getAllChildren();

	//update all entities and get messages
	std::vector<Message> messages = rootNode->update(dt, runtime);

	//check for collisions, and get more messages
	/*for (int i = 0; i < nodes.size(); i++) {
		std::vector<Message> msgs = nodes[i]->checkCollisionGroup(nodes);
		messages.insert(messages.end(), msgs.begin(), msgs.end());
	}*/
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		camera->position.y += 5 * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		camera->position.y -= 5 * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		camera->position.x += 5 * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		camera->position.x -= 5 * dt;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
		camera->position.z += 5 * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		camera->position.z -= 5 * dt;
	}

	//std::cout << camera->position.x << ", " << camera->position.y << ", " << camera->position.z << std::endl;

	//IMPORTANT: perform null checks on all NODES referenced in messages. They might be deleted in an earlier message.

	//cycle through messages and respond to them.
	for (int i = 0; i < messages.size(); i++) {

		if (messages[i].type == destroy_self) {
			for (int k = 0; k < nodes.size(); k++) {
				if (nodes[k] == messages[i].caller) {
					rootNode->destroyChild(nodes[k]);
					nodes.erase(nodes.begin() + k);		
				}
			}
		}

		if (messages[i].type == typed_word) {
			std::cout << "Typed word!" << std::endl;
			enemyManager->activeTarget = NULL;
		}

		if (messages[i].type == explode) {
			
		}

		if (messages[i].type == add_particle) {
			rootNode->addChild(messages[i].other);
		}
	}

	//spawn environment:
	if (rand() % 1000 > 950) {
		Asteroid* asteroid = new Asteroid();
		asteroid->setPosition(glm::vec3(
			(rand() % 512) - 256.f,
			(rand() % 512) - 256.f,
			-300.f));
		rootNode->addChild(asteroid);
	}


	camera->Update(dt, runtime);
}

void GameDirector::Draw(sf::RenderWindow* window) {
	//BEGIN DRAW
	
	rootNode->draw(camera, glm::mat4(1.f));


	/*
	//Render text...
	window.pushGLStates();
	if (gameMode == titlescreen || gameMode == deathscreen) {
		window.draw(pressStartText);
	}
	if (gameMode == game || gameMode == deathscreen) {
		healthText.setString("Health: " + std::to_string(health));
		window.draw(scoreText);
		scoreText.setString("Score: " + std::to_string(score));
		window.draw(healthText);
	}
	*/

	//window->popGLStates();
	window->display();
	
}