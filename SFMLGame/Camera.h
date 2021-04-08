#pragma once
#include "GL/glut.h"
#include "SFML/Graphics.hpp"
#include "glm/ext.hpp"
class Camera
{
public:
	Camera(sf::Vector3f position, sf::Vector3f lookAt);
	void DefineViewingMatrix();
	glm::mat4 getViewingMatrix();
	void Update(float dt, double time);
	sf::Vector3f position;
	sf::Vector3f lookAt;
	sf::Vector3f initialPosition;
	sf::Vector3f targetPosition;
	double moveStartTime;
	void Move(sf::Vector3f pos, double time);
private:
	float lerp(float a, float b, float f);
};

