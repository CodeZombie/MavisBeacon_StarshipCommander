#pragma once
#include <map>
#include <string>
#include "Model.h"
class ResourceManager
{
public:
	static std::map<std::string, Model*> models;
	static std::map<std::string, sf::Font> fonts;
	static void addModel(std::string model_filename, std::string texture_filename, std::string id);
	static void addFont(std::string font_filename, std::string font_id);
	static Model* getModel(std::string id);
	static sf::Font* getFont(std::string id);
};

