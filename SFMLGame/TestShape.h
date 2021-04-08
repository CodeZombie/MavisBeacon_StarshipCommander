#pragma once
#include "Node.h"
#include "Model.h"
class TestShape : public Node
{
public:
	TestShape(Model* model);
	void draw(Camera* camera, glm::mat4 parentModel);
	std::vector<Message> update(float dt, float runtime);
	Model* model;
private:


};

