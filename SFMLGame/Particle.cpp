#include "Particle.h"

Particle::Particle(Model* model, glm::vec3 direction, std::vector<glm::vec3> colors, float lifeTime, float speed) : Node3D(model){
	this->scale = glm::vec3(.25f, .25f, .25f);
	this->lifetime = lifeTime;
	this->colors = colors;
	this->direction = direction;
	this->model->useTexture = false;
	this->speed = speed;
}

std::vector<Message> Particle::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);

	scale.x -= .5 * dt;
	scale.y -= .5 * dt;
	scale.z -= .5 * dt;
	position += direction * speed * dt;


	if (startTime == 0) {
		startTime = runtime;
	}

	float normalizedTime = MathHelper::clamp(((runtime - startTime) / (lifetime)), 0.f, 1.f);
	if (normalizedTime == 0) {
		normalizedTime = 0.0001f;
	}
	
	int c1 = floor((colors.size()-1) * normalizedTime);
	int c2 = ceil((colors.size()-1) * normalizedTime);
	
/*	if (c1 < 0) {
		c1 = 0;
	}
	if (normalizedTime > 1.f) {
		c2 = colors.size() - 1;
	}*/
	//std::cout << "c1: " << c1 << " c2: " << c2 << " nV: " << normalizedTime << std::endl;
	color.x = MathHelper::lerp(colors[c1].x, colors[c2].x, normalizedTime);
	color.y = MathHelper::lerp(colors[c1].y, colors[c2].y, normalizedTime);
	color.z = MathHelper::lerp(colors[c1].z, colors[c2].z, normalizedTime);
	
	if (runtime > startTime + lifetime) {
		Message m = Message();
		m.caller = this;
		m.type = destroy_self;
		messages.push_back(m);
	}

	return messages;
}