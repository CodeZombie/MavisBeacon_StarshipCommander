#include "DeathScreen.h"
DeathScreen::DeathScreen() {
	//add start button and title
	texts.insert({ "startText", new sf::Text() });
	texts["startText"]->setFont(*ResourceManager::getFont("press_start"));
	texts["startText"]->setCharacterSize(24);
	texts["startText"]->setFillColor(sf::Color::White);
	texts["startText"]->setPosition(sf::Vector2f(420, 456.f));
	texts["startText"]->setString("You DIED. Press SPACE.");
}
std::vector<Message> DeathScreen::onInputEvent(sf::Event event, float runtime) {
	std::vector<Message> messages = __super::onInputEvent(event, runtime);
	if (static_cast<char>(event.text.unicode) == ' ') {
		Message m = Message();
		m.type = press_start;
		m.caller = this;
		messages.push_back(m);
	}
	return messages;
}