#pragma once
#include "GL/glut.h"
#include "SFML/Graphics.hpp"
#include "glm/ext.hpp"
class Camera
{
public:
	static void initialize(sf::Vector3f position, sf::Vector3f lookAt);
	static void DefineViewingMatrix();
	static glm::mat4 getViewingMatrix();
	static glm::mat4 getProjectionMatrix();
	static sf::Vector3f position;
	static sf::Vector3f lookAt;
	static float FoV;
	static float projectionNear;
	static float projectionFar;
	static float screenWidth;
	static float screenHeight;
};

