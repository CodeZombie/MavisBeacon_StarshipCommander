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

		if (messages[i].type == get_shot_by_ship) {
			playerShip->shootTarget(messages[i].caller);
		}

		if (messages[i].type == shoot) {
			std::cout << "CREATE BULLET" << std::endl;
			addChild(new Bullet(messages[i].caller, messages[i].other));
		}

		if (messages[i].type == move_back) {
			messages[i].caller->setTargetPosition(glm::vec3(0, 0, 0));
		}

		if (messages[i].type == key_hit) {
			std::cout << "Hit Key" << std::endl;
		}

		if (messages[i].type == key_miss) {
			std::cout << "Miss Key" << std::endl;
		}

		if (messages[i].type == typed_word) {
			std::cout << "Typed word!" << std::endl;
		}

		if (messages[i].type == explode) {

		}

		if (messages[i].type == add_particle) {
			//rootNode->addChild(messages[i].other);
		}
	}
	return messages;
}