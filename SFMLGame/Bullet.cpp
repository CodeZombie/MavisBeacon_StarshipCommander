#include "Bullet.h"

Bullet::Bullet(Node* source, Node* target) {
	this->source = source;
	this->target = target;
}

std::vector<Message> Bullet::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);

	if (startTime == 0) {
		startTime = runtime;
	}

	if (runtime >= startTime + 500) {
		target->destroy();

		// Message: Create explosion at Target

		Message m = Message();
		m.caller = this;
		m.type = destroy_self;
		messages.push_back(m);

		m = Message();
		m.caller = source;
		m.type = move_back;
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
			glm::vec3 col = MathHelper::getRandomDirectionVector();
			glColor3f(col.x, col.y, col.z);
			glVertex3f(
				source->getGlobalPosition().x + MathHelper::getRandomRange(-.5, .5), 
				source->getGlobalPosition().y + MathHelper::getRandomRange(-.5, .5), 
				source->getGlobalPosition().z + MathHelper::getRandomRange(-.5, .5));
			glVertex3f(
				target->getGlobalPosition().x + MathHelper::getRandomRange(-.5, .5), 
				target->getGlobalPosition().y + MathHelper::getRandomRange(-.5, .5), 
				target->getGlobalPosition().z + MathHelper::getRandomRange(-.5, .5));
		}
		glEnd();
	}
}