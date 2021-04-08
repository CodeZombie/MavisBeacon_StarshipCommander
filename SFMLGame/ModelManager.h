#pragma once
#include <map>
#include <string>
#include "Model.h"
class ModelManager
{
public:
	static std::map<std::string, Model*> models;
	static void addModel(std::string model_filename, std::string texture_filename, std::string id);
	static Model* getModel(std::string id);
};

