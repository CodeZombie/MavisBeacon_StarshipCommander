#pragma once
#include "Node.h"
#include "objloader.h"
#include <string>
class Model :
	public Node
{
public:
	Model(std::string model_filename, std::string texture_filename);
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> textureCoords;
	sf::Image texture;
	GLuint texture_id;
	bool useTexture = true;
private:

};

