#pragma once
#include <iostream>  // console I/O
#include <math.h>
#include <GL/freeglut.h>
#include <glm/vec2.hpp> // glm::vec3
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Camera.h"
#include "NodeType.h"
#include "Message.h"
#include "Spline.h"
#include "MathHelper.h"

class Message;

class Node
{
protected:
	glm::vec3 position, rotationAxis, scale, size;
	float rotation;
	float opacity;
	float speed = 0;

	std::vector<Node*> children;
	std::vector<int> collisionGroup;
	glm::mat4 lastParentMatrix;

	glm::vec3 initialPosition;
	float targetDistance;
	std::map<std::string, sf::Text*> texts;
	std::map<std::string, sf::RectangleShape*> rectangles;

	bool toBeDestroyed = false;
public:
	Node();
	virtual ~Node();
	virtual void getHurt();
	glm::vec3 color;
	NodeType nodeType;
	Spline* spline;
	std::vector<glm::vec3> targetPositions;
	std::vector<sf::Text*> getTexts();
	bool moveToTarget = false;
	bool moveAlongSpline = false;
	void setPosition(glm::vec3 position);
	glm::vec3 getGlobalPosition();
	glm::vec3 getPosition();
	glm::vec2 getScreenPosition();
	void setRotationAxis(glm::vec3 rotationAxis);
	void addTargetPosition(glm::vec3 targetPosition);
	void setRotation(float rotation);
	void setScale(glm::vec3 scale);
	void addChild(Node *child);
	bool moveTowardPoint(glm::vec3 point, float dt);
	void destroyChild(Node* child);
	void destroy();
	float getOpacity();
	virtual void draw(glm::mat4 parentModel);
	virtual std::vector<Message> update(float dt, float runtime);
	virtual std::vector<Message> onInputEvent(sf::Event event, float runtime);
	std::vector<Message> checkCollisionGroup(std::vector<Node*> others);
	std::vector<Message> checkCollision(Node* other);

	void draw2dElements(sf::RenderWindow* window);

	std::vector<Node*> getAllChildren();

	glm::mat4 modelMatrix(glm::mat4 parentModel);
};

