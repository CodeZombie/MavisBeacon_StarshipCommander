#include "UFO.h"
UFO::UFO(std::string word) : Node3D(ModelManager::getModel("ufo")) {
	rotationAxis = glm::vec3(0, 1.f, 0);
	this->word = word;
	speed = 2;

	text = UserInterface::addToTextList("press_start", word, sf::Vector2f(64.f, 64.f));
	text->setCharacterSize(32);

	hitText = UserInterface::addToTextList("press_start", "", sf::Vector2f(64.f, 64.f));
	hitText->setCharacterSize(32);
	hitText->setFillColor(sf::Color::Red);
}

UFO::~UFO() {
	UserInterface::removeText(hitText);
	UserInterface::removeText(text);
	delete hitText;
	delete text;
}

void UFO::letterHit() {
	wordCursor++;
	hitText->setString(word.substr(0, wordCursor));
	text->setString(word.substr(wordCursor));
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

	if (wordCursor >= word.size()) {
		Message m = Message();
		m.caller = this;
		m.type = destroy_self;
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

	return messages;
}

void UFO::draw(Camera* camera, glm::mat4 parentModel) {
	__super::draw(camera, parentModel);
	glm::vec2 newPos = getScreenPosition(camera);
	float wholeTextWidth = hitText->getLocalBounds().width + text->getLocalBounds().width;
	hitText->setPosition(newPos.x - wholeTextWidth/2, newPos.y);
	text->setPosition(hitText->getPosition().x + hitText->getLocalBounds().width, newPos.y);
}