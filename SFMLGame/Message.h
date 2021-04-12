#pragma once
#include "MessageTypes.h"
#include "Node.h"

class Node;

class Message {
public:
	messageType type;
	Node* caller;
	Node* other;
	float value;
};