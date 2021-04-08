#include "EnemyManager.h"

EnemyManager::EnemyManager() : Node::Node(){
	keys.insert({ sf::Keyboard::Q, 'q' });
	keys.insert({ sf::Keyboard::W, 'w' });
	keys.insert({ sf::Keyboard::E, 'e' });
	keys.insert({ sf::Keyboard::R, 'r' });
	keys.insert({ sf::Keyboard::T, 't' });
	keys.insert({ sf::Keyboard::Y, 'y' });
	keys.insert({ sf::Keyboard::U, 'u' });
	keys.insert({ sf::Keyboard::I, 'i' });
	keys.insert({ sf::Keyboard::O, 'o' });
	keys.insert({ sf::Keyboard::P, 'p' });
	keys.insert({ sf::Keyboard::A, 'a' });
	keys.insert({ sf::Keyboard::S, 's' });
	keys.insert({ sf::Keyboard::D, 'd' });
	keys.insert({ sf::Keyboard::F, 'f' });
	keys.insert({ sf::Keyboard::G, 'g' });
	keys.insert({ sf::Keyboard::H, 'h' });
	keys.insert({ sf::Keyboard::J, 'j' });
	keys.insert({ sf::Keyboard::K, 'k' });
	keys.insert({ sf::Keyboard::L, 'l' });
	keys.insert({ sf::Keyboard::Z, 'z' });
	keys.insert({ sf::Keyboard::X, 'x' });
	keys.insert({ sf::Keyboard::C, 'c' });
	keys.insert({ sf::Keyboard::V, 'v' });
	keys.insert({ sf::Keyboard::B, 'b' });
	keys.insert({ sf::Keyboard::N, 'n' });
	keys.insert({ sf::Keyboard::M, 'm' });
	keys.insert({ sf::Keyboard::Space, ' ' });


	createEnemies();
}

std::vector<Message> EnemyManager::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);
	for (int i = 0; i < messages.size(); i++) {
		if (messages[i].type == destroy_self) {
			for (int k = 0; k < enemies.size(); k++) {
				if (enemies[k] == messages[i].caller) {
					enemies.erase(enemies.begin() + k);
				}
			}
		}
	}
	return messages;
}

void EnemyManager::draw(Camera* camera, glm::mat4 parentModel)  {
	__super::draw(camera, parentModel);
	
}

void EnemyManager::createEnemies() {
	createEnemy("computer", glm::vec3(100, 200, -64), glm::vec3(-32, 0, -20));
	createEnemy("thermometer", glm::vec3(-100, 200, -64), glm::vec3(32.f, 17.f, -35.f));
	createEnemy("rhododendron", glm::vec3(0, 200, -300), glm::vec3(0, 10.f, -12.f));
}

void EnemyManager::createEnemy(std::string word, glm::vec3 startPosition, glm::vec3 targetPosition) {
	UFO* ufo = new UFO(word);
	ufo->setPosition(startPosition);
	ufo->setTargetPosition(targetPosition);
	ufo->moveToTarget = true;
	addChild(ufo);
	enemies.push_back(ufo);
}

void EnemyManager::KeyPressed(sf::Keyboard::Key key) {
	if (keys.count(key) > 0) {
		if (activeTarget == NULL) {
			for (int i = 0; i < enemies.size(); i++) {
				if (enemies[i]->word.at(enemies[i]->wordCursor) == keys[key]) {
					enemies[i]->letterHit();
					activeTarget = enemies[i];
					std::cout << "HIT" << std::endl;
					return;
				}
			}
			std::cout << "MISS" << std::endl;
		}
		else {
			if (activeTarget == NULL) {
				return;
			}
			if (activeTarget->word.at(activeTarget->wordCursor) == keys[key]) {
				activeTarget->letterHit();
				std::cout << "HIT" << std::endl;
			}
			else {
				std::cout << "MISS" << std::endl;
			}
		}
	}
}