#include "ModelManager.h"

std::map<std::string, Model*> ModelManager::models;

void ModelManager::addModel(std::string model_filename, std::string texture_filename, std::string id) {
	Model* m = new Model(model_filename, texture_filename);
	ModelManager::models.insert({id, m});
}

Model* ModelManager::getModel(std::string id) {
	return ModelManager::models[id];
}