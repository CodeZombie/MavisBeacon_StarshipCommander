#pragma once
#include "Node.h"
#include "glm/ext.hpp"
#include "MathHelper.h"
#include "SFML/System.hpp"
class StarField :public Node
{
public:
	StarField();
	void draw(glm::mat4 parentModel);
	std::vector<glm::vec3> stars;
};

