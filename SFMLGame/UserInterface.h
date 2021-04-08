#pragma once
#include <map>
#include<string.h>
#include "SFML/Graphics.hpp" 
#include <iostream>
class UserInterface
{
public:
	static void addText(std::string name, std::string font, std::string text, sf::Vector2f position);
	static void removeText(sf::Text* text);
	static sf::Text* addToTextList(std::string font, std::string text, sf::Vector2f position);
	static void addFont(std::string name, std::string filename);
	static void draw(sf::RenderWindow* window);
	static std::vector<sf::Text*> textList;
	static std::map<std::string, sf::Text> texts;
	static std::map<std::string, sf::RectangleShape> rectangles;
	static std::map<std::string, sf::Font> fonts;
	
};

