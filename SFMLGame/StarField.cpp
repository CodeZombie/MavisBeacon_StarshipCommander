#include "StarField.h"
StarField::StarField() {
	for (int i = 0; i < 1024; i++) {
		float rand_value = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float phi = rand_value * (2 * glm::pi<float>());
		float z = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 2) - 1;
		float x = sqrt(1 - (z*z)) * cos(phi);
		float y = sqrt(1 - (z*z)) * sin(phi);

		stars.push_back(glm::vec3(x, y, z) * 750.f);
	}
}
void StarField::draw(Camera* camera, glm::mat4 parentModel) {
	__super::draw(camera, parentModel);
	glm::mat4 mm = modelMatrix(parentModel);
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity(); //Reset the transform matrix
	camera->DefineViewingMatrix(); //Apply the camera matrix
	glMultMatrixf(glm::value_ptr(mm)); //Apply the model matrix (including this model's parent's matrix)
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(1,1,1);
	for (int i = 0; i < stars.size(); i++) {
		glVertex3f(stars[i].x, stars[i].y, stars[i].z);
	}
	glEnd();
}