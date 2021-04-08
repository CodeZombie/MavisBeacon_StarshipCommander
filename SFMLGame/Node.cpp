#include "Node.h"

Node::Node() {
	this->position = glm::vec3(0.f);
	this->rotationAxis = glm::vec3(1.f);
	this->scale = glm::vec3(1.f);
	this->rotation = 0.f;
	this->size = glm::vec3(0.f);
	this->color = glm::vec3(1.f);
	spline = new Spline();
}

Node::~Node() {
	for (const auto& child : children) {
		delete child;
	}
}

void Node::setTargetPosition(glm::vec3 targetPosition) {
	std::cout << position.x << ", " << position.y << ", " << position.z << std::endl;
	this->initialPosition = position;
	this->targetPosition = targetPosition;
	this->targetDistance = 0;
}

/*
The core of the math in this application is done here.
This creates a matrix from the position, rotation and scale vectors, and multiplies a parent matrix by it.
  This allows all scaling/transform/rotation applied to a parent to apply to its children.
The result is a matrix which represents position, rotation and scale of both this node and its parent.
*/

glm::mat4 Node::modelMatrix(glm::mat4 parentModel) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, this->position);
	model = glm::scale(model, this->scale);
	model = glm::rotate(model, this->rotation, this->rotationAxis);
	this->lastParentMatrix = parentModel;
	return parentModel * model;
}

glm::vec2 Node::getScreenPosition(Camera* camera) {
	float u, v;
	float width = 1366.f;
	float height = 900.f;

	glm::vec4 newPos = glm::vec4(position.x, position.y, position.z -20, 1.f);
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(90.f), (GLfloat)width / (GLfloat)height, 1.0f, 1000.f);
	glm::mat4 viewingMatrix = camera->getViewingMatrix();
	newPos = projectionMatrix * viewingMatrix * newPos;
	
	
	u = newPos.x / newPos.z;
	v = newPos.y / newPos.z;
	v = -v;
	u = (u + 1.f) * (width / 2.f);
	v = (v + 1.f) * (height / 2.f );

	if (u > width) {
		u = width - 32;
	}
	if (u < 0) {
		u = 0;
	}
	if (v > height) {
		v = height - 32;
	}
	if (v < 0) {
		v = 0;
	}

	//u = (1366 / 10) * (newPos.x + 1.0f) / 2.0f + (1366 / 2);
	//v = (900 / 10) * (1.0f - ((newPos.y + 1.0f) / 2.0f)) + (900 / 2);

	return glm::vec2(u, v);
}

void Node::setPosition(glm::vec3 position) {
	this->position = position;
}

glm::vec3 Node::getPosition() {
	return this->position;
}

float Node::getOpacity() {
	return opacity;
}

void Node::setRotationAxis(glm::vec3 rotationAxis) {
	this->rotationAxis = rotationAxis;
}

void Node::setRotation(float rotation) {
	this->rotation = rotation;
}

void Node::setScale(glm::vec3 scale) {
	this->scale = scale;
}

void Node::addChild(Node* child) {
	this->children.push_back(child);
}

void Node::destroyChild(Node* child) {
	for (int i = 0; i < children.size(); i++) {
		if (child == children[i]) {
			delete children[i];
			children.erase(children.begin() + i);
			return;
		}
		else {
			children[i]->destroyChild(child);
		}
	}
}

void Node::drawChildren(Camera* camera, glm::mat4 parentModel) {
	for (const auto& child : children) {
		child->draw(camera, parentModel);
	}
}

void Node::sendMessage(int message) {

}

void Node::draw(Camera* camera, glm::mat4 parentModel) {
	drawChildren(camera, this->modelMatrix(parentModel));
}

std::vector<Message> Node::update(float dt, float runtime) {
	
	std::vector<Message> outputMessages;
	for (const auto& child : children) {
		std::vector<Message> messages = child->update(dt, runtime);
		outputMessages.insert(outputMessages.end(), messages.begin(), messages.end());
	}
	if (moveToTarget) {
		targetDistance += .4f * dt;
		position.x = smoothstep(initialPosition.x, targetPosition.x, targetDistance);
		position.y = smoothstep(initialPosition.y, targetPosition.y, targetDistance);
		position.z = smoothstep(initialPosition.z, targetPosition.z, targetDistance);
		if (targetDistance >= 1.f) {
			moveToTarget = false;
		}
	}
	else if(moveAlongSpline) {
		if (spline != nullptr) {
			spline->currentLocation += speed * dt;
			position = spline->getPosition();
		}
	}

	return outputMessages;
}

std::vector<Message> Node::checkCollisionGroup(std::vector<Node*> others) {
	std::vector<Message> outputMessages;
	for (int i = 0; i < others.size(); i++) {
		if (others[i]->nodeType == asteroid) {
			std::vector<Message> messages = checkCollision(others[i]);
			outputMessages.insert(outputMessages.end(), messages.begin(), messages.end());
		}
	}
	return outputMessages;
}

std::vector<Message> Node::checkCollision(Node* other) {
	std::vector<Message> outputMessages;

	//AABB vs AABB collision check:
	if (position.x - (size.x/2) <= other->position.x + (other->size.x/2) && position.x + (size.x/2) >= other->position.x - (other->size.x/2)) {
		if (position.y - (size.y/2) <= other->position.y + (other->size.y/2) && position.y + (size.y/2) >= other->position.y - (other->size.y/2)) {
			if (position.z - (size.z/2) <= other->position.z + (other->size.z/2) && position.z + (size.z/2) >= other->position.z - (other->size.z/2)) {
				Message m = Message();
				m.caller = this;
				m.other = other;
				m.type = collision;
				outputMessages.push_back(m);
			}
		}
	}
	return outputMessages;
}

std::vector<Node*> Node::getAllChildren() {
	std::vector<Node*> output;

	output.push_back(this);

	for (int i = 0; i < children.size(); i++) {
		std::vector<Node*> cc = children[i]->getAllChildren();
		output.insert(output.end(), cc.begin(), cc.end());
	}

	return output;
}

float Node::smoothstep(float edge0, float edge1, float x) {
	x = clamp(x, 0.f, 1.f);
	float mu2 = (1.f - cos(x * 3.14159)) / 2.f;
	return (edge0 * (1.f - mu2) + edge1 * x);
}

float Node::clamp(float x, float lowerlimit, float upperlimit) {
	if (x < lowerlimit)
		x = lowerlimit;
	if (x > upperlimit)
		x = upperlimit;
	return x;
}