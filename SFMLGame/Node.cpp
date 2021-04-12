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
	for (auto const& x : texts) {
		delete x.second;
	}

	for (auto const& x : rectangles) {
		delete x.second;
	}
}

void Node::destroy() {
	toBeDestroyed = true;
}

void Node::addTargetPosition(glm::vec3 targetPosition) {
	targetPositions.push_back(targetPosition);
}

bool Node::moveTowardPoint(glm::vec3 point, float dt) {
	float distance = glm::length(point - position);
	if (distance > 0.001f) {
		position += glm::normalize(point - position) * distance * dt;
	}
	return distance < 0.01f;
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

glm::vec2 Node::getScreenPosition() {
	float u, v;
	glm::vec4 newPos = glm::vec4(position.x, position.y, position.z -20, 1.f);
	glm::mat4 projectionMatrix = Camera::getProjectionMatrix();
	glm::mat4 viewingMatrix = Camera::getViewingMatrix();
	newPos = projectionMatrix * viewingMatrix * newPos;
	
	
	u = newPos.x / newPos.z;
	v = newPos.y / newPos.z;
	v = -v;
	u = (u + 1.f) * (Camera::screenWidth / 2.f);
	v = (v + 1.f) * (Camera::screenHeight / 2.f );

	if (u > Camera::screenWidth) {
		u = Camera::screenWidth - 8;
	}
	if (u < 0) {
		u = 0;
	}
	if (v > Camera::screenHeight) {
		v = Camera::screenHeight - 8;
	}
	if (v < 0) {
		v = 0;
	}
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
			children[i] = NULL;
			children.erase(children.begin() + i);
			return;
		}
		else {
			children[i]->destroyChild(child);
		}
	}
}

void Node::draw(glm::mat4 parentModel) {
	glm::mat4 mm = this->modelMatrix(parentModel);
	for (const auto& child : children) {
		child->draw(mm);
	}
}

std::vector<Message> Node::update(float dt, float runtime) {
	std::vector<Message> outputMessages;
	for (const auto& child : children) {
		std::vector<Message> messages = child->update(dt, runtime);
		outputMessages.insert(outputMessages.end(), messages.begin(), messages.end());
	}
	if (targetPositions.size() > 0) {
		if (!moveToTarget) {
			initialPosition = position;
			targetDistance = 0;
			moveToTarget = true;
		}
		targetDistance += speed * dt;
		position.x = MathHelper::smoothstep(initialPosition.x, targetPositions[0].x, targetDistance);
		position.y = MathHelper::smoothstep(initialPosition.y, targetPositions[0].y, targetDistance);
		position.z = MathHelper::smoothstep(initialPosition.z, targetPositions[0].z, targetDistance);
		if (targetDistance >= 1.0f) {
			moveToTarget = false;
			targetPositions.erase(targetPositions.begin());
			Message m = Message();
			m.caller = this;
			m.type = arrived_at_target;
			outputMessages.push_back(m);
		}
	}
	else if(moveAlongSpline) {
		if (spline != nullptr) {
			spline->currentLocation += speed * dt;
			position = spline->getPosition();
		}
	}

	if (toBeDestroyed) {
		Message m = Message();
		m.caller = this;
		m.type = destroy_self;
		outputMessages.push_back(m);
	}

	return outputMessages;
}

glm::vec3 Node::getGlobalPosition() {
	return lastParentMatrix * glm::vec4(position, 1.f);
}

std::vector<Message> Node::onInputEvent(sf::Event event, float runtime) {
	std::vector<Message> outputMessages;
	for (const auto& child : children) {
		std::vector<Message> messages = child->onInputEvent(event, runtime);
		outputMessages.insert(outputMessages.end(), messages.begin(), messages.end());
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

std::vector<sf::Text*> Node::getTexts() {
	std::vector<sf::Text*> output;
	//output.insert(output.end(), texts.begin(), texts.end());
	//for (int i = 0; i < children.size(); i++) {
	//	std::vector<sf::Text*> childTexts = children[i]->getTexts();
	//	output.insert(output.end(), childTexts.begin(), childTexts.end());
	//}
	for (auto const& x : texts) {
		output.push_back(x.second);
	}

	return output;
}

void Node::draw2dElements(sf::RenderWindow* window) {
	for (const auto& child : children) {
		child->draw2dElements(window);
	}
	
	for (auto const& x : texts) {
		window->draw(*(x.second));
	}

	for (auto const& x : rectangles) {
		window->draw(*(x.second));
	}
}

void Node::getHurt() {

}