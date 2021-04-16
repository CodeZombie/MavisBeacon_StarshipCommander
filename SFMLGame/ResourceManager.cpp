#include "ResourceManager.h"

std::map<std::string, Model*> ResourceManager::models;
std::map<std::string, sf::Font> ResourceManager::fonts;

void ResourceManager::addModel(std::string model_filename, std::string texture_filename, std::string id) {
	Model* m = new Model(model_filename, texture_filename);
	ResourceManager::models.insert({id, m});
}

Model* ResourceManager::getModel(std::string id) {
	return ResourceManager::models[id];
}

sf::Font* ResourceManager::getFont(std::string id) {
	return &ResourceManager::fonts[id];
}

void ResourceManager::addFont(std::string font_filename, std::string font_id) {
	sf::Font f;
	if (!f.loadFromFile(font_filename))
	{
		std::cout << "Failed to load font: " << font_filename << std::endl;
	}
	fonts.insert({ font_id, f });
}