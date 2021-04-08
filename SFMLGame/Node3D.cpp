#include "Node3D.h"
#include "ModelManager.h"
Node3D::Node3D(Model* model) {
	this->model = model;
}

void Node3D::draw(Camera* camera, glm::mat4 parentModel){
	__super::draw(camera, parentModel);
	glm::mat4 mm = modelMatrix(parentModel);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity(); //Reset the transform matrix
	camera->DefineViewingMatrix(); //Apply the camera matrix
	glMultMatrixf(glm::value_ptr(mm)); //Apply the model matrix (including this model's parent's matrix)	

	//create a light

	GLfloat lightpos[] = { 1.0f, 2.0f, 3.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	
	if (model->useTexture) {
		glBindTexture(GL_TEXTURE_2D, model->texture_id); //tells opengl to draw with this texture.
	}
	glBegin(GL_TRIANGLES);
	glColor3f(color.x, color.y, color.z);
	//	glVertexPointer(3, GL_FLOAT, 5 * sizeof(float), (void *)0);
	for (int i = 0; i < model->vertices.size(); i++) {
		if (model->useTexture) {
			glTexCoord2f(model->textureCoords[i].x, model->textureCoords[i].y);
		}
		glVertex3f(model->vertices[i].x, model->vertices[i].y, model->vertices[i].z);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}
