#include "WordAsteroid.h"
WordAsteroid::WordAsteroid(std::string word) : Node3D(ResourceManager::getModel("asteroid")) {
	rotationAxis = MathHelper::getRandomDirectionVector();
	float s = ((rand() % 10) / 3.f) + 2.f;
	setScale(glm::vec3(s, s, s));
	speed = ((rand() % 150) + 15.f);

	this->word = word;

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

std::vector<Message> WordAsteroid::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);
	rotation += 1 * dt;

	position.z += speed * dt;
	//update text position:
	glm::vec2 newPos = getScreenPosition();
	float wholeTextWidth = texts["hitText"]->getLocalBounds().width + texts["unhitText"]->getLocalBounds().width;
	texts["hitText"]->setPosition(newPos.x - wholeTextWidth / 2, newPos.y);
	texts["unhitText"]->setPosition(texts["hitText"]->getPosition().x + texts["hitText"]->getLocalBounds().width, newPos.y);

	if (position.z > 0 && wordCursor < word.size()) {
		Message m = Message();
		m.type = hurt_player;
		m.caller = this;
		messages.push_back(m);

		m = Message();
		m.type = destroy_self;
		m.caller = this;
		messages.push_back(m);

		m = Message();
		m.type = missed_word;
		m.caller = this;
		messages.push_back(m);
	}

	return messages;
}

std::vector<Message> WordAsteroid::onInputEvent(sf::Event event, float runtime) {
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

void WordAsteroid::getHurt() {
	toBeDestroyed = true;
}