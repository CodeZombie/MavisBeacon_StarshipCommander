#pragma once
#include <vector>
#include "SFML/Graphics.hpp" 
#include "glm/ext.hpp"
class Spline
{
public:
	Spline();
	glm::vec3 getPosition();
	float currentLocation = 0;
	std::vector<glm::vec3> points;
	bool reachedEnd();
	bool looping = false;
	
};

