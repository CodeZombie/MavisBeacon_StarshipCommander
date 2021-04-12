#include "Bullet.h"

Bullet::Bullet(Node* source, Node* target) {
	this->source = source;
	this->target = target;
	sourcePos = source->getGlobalPosition();
	targetPos = target->getGlobalPosition();
	color = glm::vec3(1, 1, 0);
}

std::vector<Message> Bullet::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);

	if (startTime == 0) {
		startTime = runtime;
	}

	color = glm::vec3(1, 1, 0) * (1 -(runtime - startTime) / 250.f);

	if (runtime >= startTime + 250) {
		Message m = Message();
		m.caller = target;
		m.type = explode;
		messages.push_back(m);

		/*m = Message();
		m.caller = target;
		m.type = destroy_self;
		messages.push_back(m);*/

		m = Message();
		m.caller = this;
		m.type = destroy_self;
		messages.push_back(m);
	}

	if (target == NULL || source == NULL) {
		Message m = Message();
		m.caller = this;
		m.type = destroy_self;
		messages.push_back(m);
	}
	return messages;
}

void Bullet::draw(glm::mat4 parentModel) {
	__super::draw(parentModel);
	if (target != NULL || source != NULL) {
		glm::mat4 mm = modelMatrix(parentModel);

		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity(); //Reset the transform matrix
		Camera::DefineViewingMatrix(); //Apply the camera matrix
		glMultMatrixf(glm::value_ptr(mm)); //Apply the model matrix (including this model's parent's matrix)	

		
		glBegin(GL_LINES);
		for (int i = 0; i < 32; i++) {

			glColor3f(color.x, color.y, color.z);
			glVertex3f(
				sourcePos.x + MathHelper::getRandomRange(-.5, .5),
				sourcePos.y + MathHelper::getRandomRange(-.5, .5),
				sourcePos.z + MathHelper::getRandomRange(-.5, .5));
			glVertex3f(
				targetPos.x + MathHelper::getRandomRange(-.5, .5), 
				targetPos.y + MathHelper::getRandomRange(-.5, .5),
				targetPos.z + MathHelper::getRandomRange(-.5, .5));
		}
		glEnd();
	}
}