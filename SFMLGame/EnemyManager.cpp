#include "EnemyManager.h"

EnemyManager::EnemyManager() : Node::Node(){
	createEnemies();
}

std::vector<Message> EnemyManager::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);
	for (int i = 0; i < messages.size(); i++) {
		for (int i = 0; i < messages.size(); i++) {
			if (messages[i].type == destroy_self && messages[i].caller == activeTarget) {
				activeTarget = NULL;
			}
		}
	}

	if (children.size() == 0) {
		createEnemies();
	}

	//std::cout << activeTarget << std::endl;
	return messages;
}

void EnemyManager::createEnemies() {
	createEnemy("computer", glm::vec3(100, 200, -64), glm::vec3(-32, 0, -20));
	createEnemy("thermometer", glm::vec3(-100, 200, -64), glm::vec3(32.f, 50.f, -35.f));
	createEnemy("rhododendron", glm::vec3(0, 200, -300), glm::vec3(0, 10.f, -12.f));
}

void EnemyManager::createEnemy(std::string word, glm::vec3 startPosition, glm::vec3 targetPosition) {
	UFO* ufo = new UFO(word);
	ufo->setPosition(startPosition);
	ufo->setTargetPosition(targetPosition);
	ufo->moveToTarget = true;
	addChild(ufo);
}

std::vector<Message> EnemyManager::onInputEvent(sf::Event event) {
	//if there is no ActiveNode, forward the keypress to all children.
	//if a child sends back a "hit" message, we set that one to the active node.
	//if there IS an activeNode set, we only forward the key events to that one, nothing else.
	//if a child is destroyed, we set activeNode back to null

	std::vector<Message> messages;

	if (activeTarget == NULL) {						//theres no current active target
		bool hit = false;
		messages = __super::onInputEvent(event);			//forward the key event to all children.
		for (int i = 0; i < messages.size(); i++) {		//cycle through the recieved messages...
			if (messages[i].type == key_hit) {				//if any of them are a key_hit:
				activeTarget = messages[i].caller;				//Set activeTarget to the enemy we just hit
				hit = true;
				break;
			}
		}
		if (!hit) {
			//clear all hit messages but one
		}
	}
	else{
		messages = activeTarget->onInputEvent(event);
	}

	for (int i = 0; i < messages.size(); i++) {
		if (messages[i].type == destroy_self && messages[i].caller == activeTarget) {
			activeTarget = NULL;
		}
	}
	return messages;
}
