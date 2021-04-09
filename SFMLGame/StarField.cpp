#include "StarField.h"
StarField::StarField() {
	for (int i = 0; i < 1024; i++) {
		stars.push_back(MathHelper::getRandomDirectionVector() * 750.f);
	}
}
void StarField::draw(glm::mat4 parentModel) {
	__super::draw(parentModel);
	glm::mat4 mm = modelMatrix(parentModel);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity(); //Reset the transform matrix
	Camera::DefineViewingMatrix(); //Apply the camera matrix
	glMultMatrixf(glm::value_ptr(mm)); //Apply the model matrix (including this model's parent's matrix)
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(1,1,1);
	for (int i = 0; i < stars.size(); i++) {
		glVertex3f(stars[i].x, stars[i].y, stars[i].z);
	}
	glEnd();
}