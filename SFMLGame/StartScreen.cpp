#include "StartScreen.h"
StartScreen::StartScreen() {
	//add start button and title
	Camera::initialize(sf::Vector3f(0, 0, 100.f), sf::Vector3f(0, 200.f, 0.f));
	texts.insert({ "startText", new sf::Text() });
	texts["startText"]->setFont(*ResourceManager::getFont("press_start"));
	texts["startText"]->setCharacterSize(24);
	texts["startText"]->setFillColor(sf::Color::White);
	texts["startText"]->setPosition(sf::Vector2f(420, 456.f));
	texts["startText"]->setString("Press SPACE To Start");

	addChild(new Space(true));
}
std::vector<Message> StartScreen::onInputEvent(sf::Event event, float runtime) {
	std::vector<Message> messages = __super::onInputEvent(event, runtime);
	if (static_cast<char>(event.text.unicode) == ' ') {
		Message m = Message();
		m.type = press_start;
		m.caller = this;
		messages.push_back(m);
	}
	return messages;
}


std::vector<Message> StartScreen::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);
	Camera::position.y += 5 * dt;

	return messages;
}