#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "GL/glut.h"
#include <iostream> 
#include "MessageTypes.h"
#include "Message.h"
#include<string>
#include "GameScene.h"
#include "GameUserInterface.h"
#include "StartScreen.h"
#include <string>

Node* activeNode;

int main()
{
	srand(time(NULL));

	// INITIALIZE THE WINDOW 
	int width = 1366, height = 900;

	//Window video settings
	sf::ContextSettings window_settings;
	window_settings.depthBits = 24;
	window_settings.stencilBits = 8;
	window_settings.antialiasingLevel = 8;

	//initialize the window and set up some OPENGL things
	sf::RenderWindow window(sf::VideoMode(width, height, 32), "NO MANS KEYBOARD", sf::Style::Resize | sf::Style::Close, window_settings);
	glClearDepth(1.f);
	glClearColor(0.05f, 0.05f, 0.05f, 0.f);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glDepthMask(GL_TRUE);

	//set up camera & projection matrix
	Camera::screenWidth = width;
	Camera::screenHeight = height;
	Camera::FoV = 90.0f;
	Camera::projectionNear = 1.0f;
	Camera::projectionFar = 1500.f;

	glMatrixMode(GL_PROJECTION);
	glMultMatrixf(glm::value_ptr(Camera::getProjectionMatrix()));
	//gluPerspective(90.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);
	
	// Create a clock for measuring time elapsed and delta time   

	ResourceManager::addFont("PressStart.ttf", "press_start");
	ResourceManager::addModel("models/StarSparrow01.obj", "StarSparrow_Blue.png", "player_ship");
	ResourceManager::addModel("models/pyramid.obj", "light_flare_particle.png", "particle_star");
	ResourceManager::addModel("models/ufo.obj", "ufo_texture.png", "ufo");
	ResourceManager::addModel("models/asteroid_a.obj", "asteroid.png", "asteroid");
	ResourceManager::addModel("models/planet.obj", "planet.png", "planet");
	ResourceManager::addModel("models/plasma_billboard.obj", "space_plasma.png", "plasma");
	ResourceManager::addModel("models/health.obj", "health.png", "health");
	//initialize game director
	activeNode = new StartScreen();//new GameScene();

	//start clocks
	sf::Clock Clock;
	sf::Clock runtimeClock;
	// Start game loop 
	while (window.isOpen())
	{
		std::vector<Message> messages;

		float runtime = runtimeClock.getElapsedTime().asMilliseconds();
		float dt = Clock.restart().asSeconds(); //calculate delta time.

		//Handle some non-entity specific inputs:
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Resized) {
				sf::FloatRect visibleArea(0, 0, Event.size.width, Event.size.height);
				window.setView(sf::View(visibleArea));
				Camera::screenWidth = Event.size.width;
				Camera::screenHeight = Event.size.height;
				glViewport(0, 0, Event.size.width, Event.size.height);
			}
			if (Event.type == sf::Event::TextEntered) {
				std::vector<Message> inputMessages = activeNode->onInputEvent(Event, runtime);
				messages.insert(messages.end(), inputMessages.begin(), inputMessages.end());
			}
			if (Event.type == sf::Event::Closed)
				window.close();
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();
		}

		
		std::vector<Message> updateMessages = activeNode->update(dt, runtime);
		messages.insert(messages.end(), updateMessages.begin(), updateMessages.end());

		//std::cout << 1/dt << std::endl;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glDepthMask(GL_TRUE);

		activeNode->draw(glm::mat4(1.f));

		window.pushGLStates();
		activeNode->draw2dElements(&window);
		window.popGLStates();
		window.display();

		for (int i = 0; i < messages.size(); i++) {
			if (messages[i].type == press_start) {
				delete activeNode;
				activeNode = new GameScene();
			}
		}


	}
	return EXIT_SUCCESS;
}