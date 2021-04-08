#include "UserInterface.h"

std::map<std::string, sf::Text> UserInterface::texts;
std::vector<sf::Text*> UserInterface::textList;
std::map<std::string, sf::RectangleShape> UserInterface::rectangles;
std::map<std::string, sf::Font> UserInterface::fonts;

void UserInterface::addText(std::string name, std::string font, std::string text, sf::Vector2f position) {
	texts.insert({ name, sf::Text() });
	texts[name].setFont(UserInterface::fonts[font]);
	texts[name].setCharacterSize(8);
	texts[name].setFillColor(sf::Color::White);
	texts[name].setPosition(position);
	texts[name].setString(text);
}

void UserInterface::removeText(sf::Text* text) {
	for (int i = 0; i < textList.size(); i++) {
		if (textList[i] == text) {
			textList.erase(textList.begin() + i);
		}
	}
}

sf::Text* UserInterface::addToTextList(std::string font, std::string text, sf::Vector2f position) {
	sf::Text* newText = new sf::Text();
	newText->setFont(UserInterface::fonts[font]);
	newText->setCharacterSize(8);
	newText->setFillColor(sf::Color::White);
	newText->setPosition(position);
	newText->setString(text);
	textList.push_back(newText);
	return newText;
}


void UserInterface::addFont(std::string name, std::string filename) {
	sf::Font f;
	if (!f.loadFromFile(filename))
	{
		std::cout << "Failed to load font: " << filename << std::endl;
	}

	UserInterface::fonts.insert({ name, f });
}

void UserInterface::draw(sf::RenderWindow* window) {
	for (int i = 0; i < textList.size(); i++) {
		window->draw(*textList[i]);
	}

	for (auto const& textIterator : texts) {
		window->draw(textIterator.second);
	}

	for (auto const& rectangleIterator : rectangles) {
		window->draw(rectangleIterator.second);
	}
}