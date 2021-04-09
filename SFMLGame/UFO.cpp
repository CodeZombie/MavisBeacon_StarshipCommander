#include "UFO.h"
UFO::UFO(std::string word) : Node3D(ResourceManager::getModel("ufo")) {
	rotationAxis = glm::vec3(0, 1.f, 0);
	this->word = word;
	speed = 1.1f;

	texts.push_back(new sf::Text());
	texts[0]->setFont(*ResourceManager::getFont("press_start"));
	texts[0]->setCharacterSize(24);
	texts[0]->setFillColor(sf::Color::Red);
	texts[0]->setPosition(sf::Vector2f(64.f, 64.f));
	texts[0]->setString("");

	texts.push_back(new sf::Text());
	texts[1]->setFont(*ResourceManager::getFont("press_start"));
	texts[1]->setCharacterSize(24);
	texts[1]->setFillColor(sf::Color::White);
	texts[1]->setPosition(sf::Vector2f(64.f, 64.f));
	texts[1]->setString(word);
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
	float wholeTextWidth = texts[0]->getLocalBounds().width + texts[1]->getLocalBounds().width;
	texts[0]->setPosition(newPos.x - wholeTextWidth / 2, newPos.y);
	texts[1]->setPosition(texts[0]->getPosition().x + texts[0]->getLocalBounds().width, newPos.y);

	return messages;
}

std::vector<Message> UFO::onInputEvent(sf::Event event) {
	std::vector<Message> messages = __super::onInputEvent(event);
	if (wordCursor < word.size()) {
		if (static_cast<char>(event.text.unicode) == word.at(wordCursor)) {
			wordCursor++;
			texts[0]->setString(word.substr(0, wordCursor));
			texts[1]->setString(word.substr(wordCursor));

			Message m = Message();
			m.caller = this;
			m.type = key_hit;
			messages.push_back(m);
			if (wordCursor >= word.size()) {
				Message m = Message();
				m.caller = this;
				m.type = get_shot_by_ship;
				messages.push_back(m);

				m = Message();
				m.caller = this;
				m.type = typed_word;
				messages.push_back(m);

				m = Message();
				m.caller = this;
				m.type = explode;
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