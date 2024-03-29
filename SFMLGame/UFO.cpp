#include "UFO.h"
UFO::UFO(std::string word) : Node3D(ResourceManager::getModel("ufo")) {
	rotationAxis = glm::vec3(0, 1.f, 0);
	this->word = word;
	speed = 1.1f;

	texts.insert({ "hitText", new sf::Text() });
	texts["hitText"]->setFont(*ResourceManager::getFont("press_start"));
	texts["hitText"]->setCharacterSize(24);
	texts["hitText"]->setFillColor(sf::Color::Red);
	texts["hitText"]->setPosition(sf::Vector2f(64.f, 64.f));
	texts["hitText"]->setString("");

	texts.insert({ "unhitText", new sf::Text() });
	texts["unhitText"]->setFont(*ResourceManager::getFont("press_start"));
	texts["unhitText"]->setCharacterSize(24);
	texts["unhitText"]->setFillColor(sf::Color::White);
	texts["unhitText"]->setPosition(sf::Vector2f(64.f, 64.f));
	texts["unhitText"]->setString(word);
}

std::vector<Message> UFO::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);
	rotation += 5 * dt;
	
	if (moveToTarget == false && moveAlongSpline == false) {
		//create a new spline for just movin around.
		moveAlongSpline = true;
		spline = new Spline();
		spline->looping = true;
		spline->points.push_back(position);
		for (int i = 0; i < 64; i++) {
			spline->points.push_back(glm::vec3(
				position.x + (((rand() % 64) / 64.f)*16.f - 4.f),
				position.y + (((rand() % 64) / 64.f)*16.f - 4.f),
				position.z + (((rand() % 64) / 64.f)*8.f - 4.f)));
		}
	}

	//update text position:
	glm::vec2 newPos = getScreenPosition();
	float wholeTextWidth = texts["hitText"]->getLocalBounds().width + texts["unhitText"]->getLocalBounds().width;
	texts["hitText"]->setPosition(newPos.x - wholeTextWidth / 2, newPos.y);
	texts["unhitText"]->setPosition(texts["hitText"]->getPosition().x + texts["hitText"]->getLocalBounds().width, newPos.y);

	return messages;
}

std::vector<Message> UFO::onInputEvent(sf::Event event, float runtime) {
	std::vector<Message> messages = __super::onInputEvent(event, runtime);
	if (wordCursor < word.size()) {
		if (static_cast<char>(event.text.unicode) == word.at(wordCursor)) {
			wordCursor++;
			texts["hitText"]->setString(word.substr(0, wordCursor));
			texts["unhitText"]->setString(word.substr(wordCursor));

			Message m = Message();
			m.caller = this;
			m.type = key_hit;
			messages.push_back(m);

			if (wordCursor >= word.size()) {
				m = Message();
				m.caller = this;
				m.type = typed_word;
				messages.push_back(m);
			}

		}
		else {
			Message m = Message();
			m.caller = this;
			m.type = key_miss;
			messages.push_back(m);
		}
	}
	return messages;
}

void UFO::getHurt() {
	toBeDestroyed = true;
}