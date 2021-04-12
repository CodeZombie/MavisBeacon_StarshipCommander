#include "GameUserInterface.h"

GameUserInterface::GameUserInterface() : Node() {
	health = 100;
	//create some text and rects for displaying the UI
	sf::Text* scoreText = new sf::Text;
	scoreText->setFont(*ResourceManager::getFont("press_start"));
	scoreText->setString("0");
	scoreText->setCharacterSize(18);
	scoreText->setPosition(sf::Vector2f(32, 32));
	scoreText->setFillColor(sf::Color::White);
	
	texts.insert({"score", scoreText});

	sf::Text* healthText = new sf::Text;
	healthText->setFont(*ResourceManager::getFont("press_start"));
	healthText->setCharacterSize(18);
	healthText->setString("100%");
	healthText->setPosition(sf::Vector2f(32, 64));
	healthText->setFillColor(sf::Color::Red);

	texts.insert({ "score", scoreText });
	texts.insert({ "health", healthText });
}

void GameUserInterface::setCPM(int cpm) {
	averageCPM = cpm;
	texts["score"]->setString(std::to_string(cpm));
}

void GameUserInterface::setHealth(int h) {
	health = h;
	texts["health"]->setString(std::to_string(health) + "%");
}


std::vector<Message> GameUserInterface::update(float dt, float runtime) {
	std::vector<Message> messages;
	
	return messages;
}