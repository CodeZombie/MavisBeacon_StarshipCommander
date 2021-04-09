#include "GameScene.h"
GameScene::GameScene() {
	//set up camera
	Camera::initialize(sf::Vector3f(0, 4, 24.f), sf::Vector3f(0, 12.f, 0.f));

	//add necessary children
	playerShip = new PlayerShip();
	addChild(playerShip);

	enemyManager = new EnemyManager();
	addChild(enemyManager);
	addChild(new Space());

}

std::vector<Message> GameScene::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);

	std::vector<Message> newMessages = handleMessages(messages);
	messages.insert(messages.end(), newMessages.begin(), newMessages.end());

	return messages;
}

std::vector<Message> GameScene::onInputEvent(sf::Event event) {
	std::vector<Message> messages = __super::onInputEvent(event);

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
			
		}

		if (messages[i].type == arrived_at_target_node) {
			addChild(new Bullet(messages[i].caller, messages[i].other));
		}


		if (messages[i].type == key_hit) {
			std::cout << "Hit Key" << std::endl;
		}

		if (messages[i].type == key_miss) {
			std::cout << "Miss Key" << std::endl;
		}

		if (messages[i].type == typed_word) {
			std::cout << "Typed word!" << std::endl;
			enemyManager->activeTarget = NULL;
			playerShip->shootTarget(messages[i].caller);	
		}

		if (messages[i].type == add_particle) {
			addChild(messages[i].other);
		}

		if (messages[i].type == explode) {
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