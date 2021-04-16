#include "EnemyManager.h"

EnemyManager::EnemyManager() : Node::Node(){
	stageIntervalTime = 2000;
	emState = idle;
	state = alien_one;
}

std::vector<Message> EnemyManager::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);

	for (int i = 0; i < messages.size(); i++) {
		if (messages[i].type == missed_word) {
			if (activeTarget == messages[i].caller) {
				activeTarget = NULL;
			}
			livingEnemies--;
		}
	}

	if (emState == idle && runtime > stageFinishedTime + stageIntervalTime) {
		Message m = Message();
		m.caller = this;
		m.type = stage_started;
		messages.push_back(m);
		startStage(runtime);
		emState = stage_running;
		shotsThisStage = 2;
		stageFinishedTime = 0;

	}

	if (livingEnemies == 0) {
		if(emState == stage_running){
			std::cout << "CALLING STAGE_FINISHED : Runtime: " << runtime << std::endl;
			stageFinishedTime = runtime;
			emState = idle;

			Message m = Message();
			m.caller = this;
			m.type = stage_finished;
			m.value = stageFinishedTime - stageStartTime;
			messages.push_back(m);
		}
	}

	if (emState == stage_running && runtime > stageStartTime + (shotsThisStage * 5000)) {
		if (state == alien_one || state == alien_two || asteroid_two) {
			//pick a random enemy
			Node* u = children[rand() % children.size()];
			shotsThisStage++;
			//have them shoot the player.
			Message m = Message();
			m.type = shoot_player;
			m.caller = u;
			messages.push_back(m);
		}
	}


	return messages;
}

void EnemyManager::startStage(float runtime) {
	if (state == alien_one) {
		std::vector<std::string> words = Dictionary::getWords(7, 3);
		createEnemy(words[0], glm::vec3(100, 200, -64), glm::vec3(-32, 0, -20));
		createEnemy(words[1], glm::vec3(-100, 200, -64), glm::vec3(32.f, 50.f, -35.f));
		createEnemy(words[2], glm::vec3(0, 200, -300), glm::vec3(0, 10.f, -12.f));

	}
	else if (state == alien_two) {
		if (MathHelper::getRandomRange(0, 10) > 1.f) {
			std::vector<std::string> words = Dictionary::getWords(MathHelper::randomRange(8, 9), 4);
			createEnemy(words[0], glm::vec3(100, 200, -64), glm::vec3(-32, 0, -20));
			createEnemy(words[1], glm::vec3(-100, 200, -64), glm::vec3(32.f, 50.f, -35.f));
			createEnemy(words[2], glm::vec3(0, 200, -64), glm::vec3(0, 10.f, -12.f));
			createEnemy(words[3], glm::vec3(400, 300, -200), glm::vec3(-40, 25.f, -19.f));
		}
	}
	else if(state == asteroid_one){
		std::vector<std::string> words = Dictionary::getWords(MathHelper::randomRange(10, 11), 4);
		createAsteroid(words[0], glm::vec3(-200, 150, -600));
		createAsteroid(words[1], glm::vec3(50, 0, -600));
		createAsteroid(words[2], glm::vec3(-300, 500, -600));
		//createAsteroid(words[3], glm::vec3(300, 500, -600));
	}
	else if (state == asteroid_two) {
		std::vector<std::string> words = Dictionary::getWords(MathHelper::randomRange(9, 11), 6);
		createAsteroid(words[0], glm::vec3(-200, 150, -600));
		createAsteroid(words[1], glm::vec3(50, 0, -600));
		createEnemy(words[2], glm::vec3(100, 200, -64), glm::vec3(-32, 0, -20));
		createEnemy(words[3], glm::vec3(-100, 200, -64), glm::vec3(32.f, 50.f, -35.f));
		createEnemy(words[4], glm::vec3(0, 200, -64), glm::vec3(0, 10.f, -12.f));
		createEnemy(words[5], glm::vec3(-200, 100, -64), glm::vec3(0, 10.f, -12.f));
	}
	else if (state == boss) {
		std::vector<std::string> strings;
		strings.push_back(Dictionary::getRandomText());
		strings.push_back(Dictionary::getRandomText());
		strings.push_back(Dictionary::getRandomText());
		strings.push_back(Dictionary::getRandomText());
		Boss* boss = new Boss(strings);
		boss->setPosition(glm::vec3(100, 200, -205));
		boss->addTargetPosition(glm::vec3(0,16, -10));
		addChild(boss);
		livingEnemies++;

	}
	if (MathHelper::getRandomRange(0, 10) > 9.f) {
		std::vector<std::string> w = Dictionary::getWords(10, 1);
		HealthPickup* hp = new HealthPickup(w[0]);
		addChild(hp);
		livingEnemies++;
		hp->setPosition(glm::vec3(0, 200, -600));
	}	
	stageStartTime = runtime;
}

void EnemyManager::createEnemy(std::string word, glm::vec3 startPosition, glm::vec3 targetPosition) {
	UFO* ufo = new UFO(word);
	ufo->setPosition(startPosition);
	ufo->addTargetPosition(targetPosition);
	//ufo->moveToTarget = true;
	addChild(ufo);
	livingEnemies++;
}

void EnemyManager::createAsteroid(std::string word, glm::vec3 startPosition) {
	WordAsteroid* wa = new WordAsteroid(word);
	wa->setPosition(startPosition);
	addChild(wa);
	livingEnemies++;
}
std::vector<Message> EnemyManager::onInputEvent(sf::Event event, float runtime) {
	//if there is no ActiveNode, forward the keypress to all children.
	//if a child sends back a "hit" message, we set that one to the active node.
	//if there IS an activeNode set, we only forward the key events to that one, nothing else.
	//if a child is destroyed, we set activeNode back to null

	std::vector<Message> messages;
	if (!activeTarget) {						//theres no current active target
		bool hit = false;
		messages = __super::onInputEvent(event, runtime);			//forward the key event to all children.
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
		messages = activeTarget->onInputEvent(event, runtime);
		for (int i = 0; i < messages.size(); i++) {
			if (messages[i].type == typed_word ){
				activeTarget = nullptr;
				livingEnemies--;
				break;
			}
		}
	}
	return messages;
}
