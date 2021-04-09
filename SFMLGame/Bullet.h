#pragma once
#include "Node.h"
class Bullet : public Node{
public:
	Bullet(Node* source, Node* target);
	void draw(glm::mat4 parentModel);
	std::vector<Message> update(float dt, float runtime);
	Node* source;
	Node* target;
	glm::vec3 sourcePos, targetPos;
	float startTime = 0;
};

