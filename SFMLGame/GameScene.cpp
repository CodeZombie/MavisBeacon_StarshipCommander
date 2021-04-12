#include "GameScene.h"
GameScene::GameScene() {
	//set up camera
	Camera::initialize(sf::Vector3f(0, 4, 24.f), sf::Vector3f(0, 12.f, 0.f));

	//add necessary children
	playerShip = new PlayerShip();
	addChild(playerShip);

	enemyManager = new EnemyManager();
	enemyManager->state = asteroid_one;
	addChild(enemyManager);
	addChild(new Space());
	userInterface = new GameUserInterface();
	addChild(userInterface);
}

std::vector<Message> GameScene::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);

	std::vector<Message> newMessages = handleMessages(messages);
	messages.insert(messages.end(), newMessages.begin(), newMessages.end());

	return messages;
}

std::vector<Message> GameScene::onInputEvent(sf::Event event, float runtime) {
	std::vector<Message> messages = __super::onInputEvent(event, runtime);

	std::vector<Message> newMessages = handleMessages(messages);
	messages.insert(messages.end(), newMessages.begin(), newMessages.end());

	return messages;
}

std::vector<Message> GameScene::handleMessages(std::vector<Message> messages) {
	std::vector<Message> outMessages;

	for (int i = 0; i < messages.size(); i++) {
		if (messages[i].type == destroy_self) {
			destroyChild(messages[i].caller);
		}

		if (messages[i].type == shoot) {
			std::cout << "CREATE BULLET" << std::endl;
			addChild(new Bullet(messages[i].caller, messages[i].other));
		}


		if (messages[i].type == shoot_player) {
			addChild(new Bullet(messages[i].caller, playerShip));
			playerShip->getHurt();
			userInterface->setHealth(playerShip->health);
		}

		if (messages[i].type == arrived_at_target_node) {
			addChild(new Bullet(messages[i].caller, messages[i].other));
		}

		if (messages[i].type == stage_finished) {

			float cpm = (charactersTypedDuringStage - errorsTypedDuringStage) / (messages[i].value / 1000.f / 60.f);

			std::cout << "Stages completed: " << stagesCompleted << std::endl;
			std::cout << "stage time: " << (messages[i].value / 1000.f / 60.f) << std::endl;
			std::cout << "CPM: " << cpm << std::endl;
			if (stagesCompleted == 0) {
				averageCPM = cpm;
			}
			else {
				averageCPM = (averageCPM + cpm) / 2.f;
			}
			userInterface->setCPM(floor(averageCPM));
			
			charactersTypedDuringStage = 0;
			errorsTypedDuringStage = 0;
			stagesCompleted++;
			
			if (stagesCompleted > 4) {
				if (enemyManager->state == alien_one && averageCPM > 250) {
					//delete enemy manager and make one with the harder aliens.
					enemyManager->state = alien_two;
					stagesCompleted = 0;
				}
				else if (enemyManager->state == alien_two && averageCPM > 250) {
					enemyManager->state = asteroid_one;
					stagesCompleted = 0;
				}
				else if (enemyManager->state == asteroid_one && averageCPM > 300) {
					//delete enemy manager and make the asteroid manager
				}
				
			}
			
		}

		if (messages[i].type == hurt_player) {
			playerShip->getHurt();
			userInterface->setHealth(playerShip->health);

			std::vector<glm::vec3> c;
			c.push_back(glm::vec3(1, 1, 1));
			c.push_back(glm::vec3(1, 1, 0));
			c.push_back(glm::vec3(1, 0, 0));
			c.push_back(glm::vec3(0, 0, 0));
			addChild(new ParticleEmitter(
				playerShip->getGlobalPosition(),
				ResourceManager::getModel("particle_star"),
				true,			//random direction
				glm::vec3(0),	//direction
				c,				//color vector
				500.f,			//particle lifetime 
				1,			//emitter lifetime
				glm::vec2(12, 45),				//particle speed
				500.f,				//emission interval
				64,			//initial amount
				glm::vec2(.5, 1.25))); //scale range	
		}

		if (messages[i].type == key_hit) {
			std::cout << "Hit Key" << std::endl;
			charactersTypedDuringStage++;
		}

		if (messages[i].type == key_miss) {
			std::cout << "Miss Key" << std::endl;
			errorsTypedDuringStage++;
		}

		if (messages[i].type == typed_word) {
			std::cout << "Typed word!" << std::endl;
			playerShip->shootTarget(messages[i].caller);	
		}

		if (messages[i].type == add_particle) {
			addChild(messages[i].other);
		}

		if (messages[i].type == explode) {
			messages[i].caller->getHurt();
			std::vector<glm::vec3> c;
			c.push_back(glm::vec3(1, 1, 1));
			c.push_back(glm::vec3(1, 1, 0));
			c.push_back(glm::vec3(1, 0, 0));
			c.push_back(glm::vec3(0, 0, 0));
			addChild(new ParticleEmitter(
				messages[i].caller->getGlobalPosition(), 
				ResourceManager::getModel("particle_star"), 
				true,			//random direction
				glm::vec3(0),	//direction
				c,				//color vector
				500.f,			//particle lifetime 
				1,			//emitter lifetime
				glm::vec2(12, 45),				//particle speed
				500.f,				//emission interval
				64,			//initial amount
				glm::vec2(.5,1.25))); //scale range			
		}

		if (messages[i].type == add_particle) {
			//rootNode->addChild(messages[i].other);
		}
	}
	return messages;
}