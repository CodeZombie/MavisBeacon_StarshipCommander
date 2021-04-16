#include "Boss.h"
Boss::Boss(std::vector<std::string> strings) : Node3D(ResourceManager::getModel("enemy_ship")) {
	this->setRotationAxis(glm::vec3(0, 1, 0));
	this->setRotation(-80);
	float s = 25;
	this->setScale(glm::vec3(s, s, s));
	this->word = strings[0];
	this->words = strings;
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

std::vector<Message> Boss::update(float dt, float runtime) {
	std::vector<Message> messages = __super::update(dt, runtime);

	if (moveToTarget == false && moveAlongSpline == false) {
		//create a new spline for just movin around.
		moveAlongSpline = true;
		spline = new Spline();
		spline->looping = true;
		spline->points.push_back(position);
		spline->points.push_back(glm::vec3(
			position.x + .5,
			position.y + .25,
			position.z + .8));
		spline->points.push_back(glm::vec3(
			position.x + -.2,
			position.y + -.25,
			position.z + -.2));
	}

	//update text position:
	glm::vec2 newPos = getScreenPosition();
	float wholeTextWidth = texts["hitText"]->getLocalBounds().width + texts["unhitText"]->getLocalBounds().width;
	texts["hitText"]->setPosition(newPos.x - wholeTextWidth / 2, newPos.y);
	texts["unhitText"]->setPosition(texts["hitText"]->getPosition().x + texts["hitText"]->getLocalBounds().width, newPos.y);

	return messages;
}

std::vector<Message> Boss::onInputEvent(sf::Event event, float runtime) {
	std::vector<Message> messages = __super::onInputEvent(event, runtime);
	if (wordCursor < word.size()) {
		if (static_cast<char>(event.text.unicode) == word.at(wordCursor)) {
			wordCursor++;
			

			Message m = Message();
			m.caller = this;
			m.type = key_hit;
			messages.push_back(m);

			if (wordCursor >= word.size()) {
				sentenceCursor++;
				if (sentenceCursor < words.size()) {
					word = words[sentenceCursor];
					wordCursor = 0;
				}
				else {
					m = Message();
					m.caller = this;
					m.type = typed_word;
					messages.push_back(m);
				}
				
			}
			texts["hitText"]->setString(word.substr(0, wordCursor));
			texts["unhitText"]->setString(word.substr(wordCursor));

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

void Boss::getHurt() {
	toBeDestroyed = true;
}