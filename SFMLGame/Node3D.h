#pragma once
#include "Node.h"
#include "Model.h"
class Node3D : public Node
{
public:
	Node3D(Model* model);
	void draw(glm::mat4 parentModel);
protected:
	Model* model;
};

