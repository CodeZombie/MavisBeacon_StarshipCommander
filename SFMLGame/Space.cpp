#include "Space.h"

Space::Space() {
	Planet* planet = new Planet();
	planet->setPosition(glm::vec3(400,150,-400));
	addChild(planet);
	addChild(new Plasma());
	addChild(new StarField());

}

std::vector<Message> Space::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);

	//spawn environment:
	/*if (rand() % 1000 > 950) {
		Asteroid* asteroid = new Asteroid();
		asteroid->setPosition(glm::vec3(
			(rand() % 512) - 256.f,
			(rand() % 512) - 256.f,
			-600.f));
		addChild(asteroid);
	}*/

	return messages;
}