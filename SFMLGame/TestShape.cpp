#include "TestShape.h"

TestShape::TestShape(Model* model) {
	this->position = glm::vec3(7.f, 0.f, 0.f);
	this->scale = glm::vec3(3.f);
	this->rotationAxis = glm::vec3(1.f, 0.f, 0.f);
	this->model = model;
}

std::vector<Message> TestShape::update(float dt, float runtime) {
	position.z += 5 * dt;

	return std::vector<Message>();
}

void TestShape::draw(glm::mat4 parentModel) {
	glm::mat4 mm = modelMatrix(parentModel);
	draw(mm);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity(); //Reset the transform matrix
	Camera::DefineViewingMatrix(); //Apply the camera matrix
	glMultMatrixf(glm::value_ptr(mm)); //Apply the model matrix (including this model's parent's matrix)	

	//create a light
	GLfloat lightpos[] = { 1.0f, 2.0f, 3.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	glColor3f(1.f, 1.f, 1.f);
	
	glBindTexture(GL_TEXTURE_2D, model->texture_id); //tells opengl to draw with this texture.

	glBegin(GL_TRIANGLES);
	glVertexPointer(3, GL_FLOAT, 5 * sizeof(float), (void *)0);
	for (int i = 0; i < model->vertices.size(); i++) {
		glTexCoord2f(model->textureCoords[i].x, model->textureCoords[i].y);
		glVertex3f(model->vertices[i].x, model->vertices[i].y, model->vertices[i].z);
	}
	glEnd();
	/*
	glBegin(GL_QUADS);
	
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-.5f, -.5f, -.5f);
	glVertex3f(-.5f, .5f, -.5f);
	glVertex3f(.5f, .5f, -.5f);
	glVertex3f(.5f, -.5f, -.5f);

	glVertex3f(-.5f, -.5f, .5f);
	glVertex3f(-.5f, .5f, .5f);
	glVertex3f(.5f, .5f, .5f);
	glVertex3f(.5f, -.5f, .5f);

	glVertex3f(-.5f, -.5f, -.5f);
	glVertex3f(-.5f, .5f, -.5f);
	glVertex3f(-.5f, .5f, .5f);
	glVertex3f(-.5f, -.5f, .5f);

	glVertex3f(.5f, -.5f, -.5f);
	glVertex3f(.5f, .5f, -.5f);
	glVertex3f(.5f, .5f, .5f);
	glVertex3f(.5f, -.5f, .5f);

	glVertex3f(-.5f, -.5f, .5f);
	glVertex3f(-.5f, -.5f, -.5f);
	glVertex3f(.5f, -.5f, -.5f);
	glVertex3f(.5f, -.5f, .5f);

	glVertex3f(-.5f, .5f, .5f);
	glVertex3f(-.5f, .5f, -.5f);
	glVertex3f(.5f, .5f, -.5f);
	glVertex3f(.5f, .5f, .5f);

	glEnd();*/
}