#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "GL/glut.h"
#include <iostream> 
#include "Camera.h"
#include "MessageTypes.h"
#include "Message.h"
#include<string>
#include "GameDirector.h"
#include "UserInterface.h"
#include <string>

GameDirector* gameDirector;

int main()
{
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
	glMatrixMode(GL_PROJECTION);
	glMultMatrixf(glm::value_ptr(glm::perspective(glm::radians(90.f), (GLfloat)width / (GLfloat)height, 1.0f, 1000.f)));
	//gluPerspective(90.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);
	
	// Create a clock for measuring time elapsed and delta time   


	UserInterface::addFont("press_start", "PressStart.ttf");

	//initialize game director
	gameDirector = new GameDirector();

	//start clocks
	sf::Clock Clock;
	sf::Clock runtimeClock;
	// Start game loop 
	while (window.isOpen())
	{
		//Handle some non-entity specific inputs:
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			if (Event.type == sf::Event::KeyPressed) {
				gameDirector->KeyPressed(Event.key.code);
			}
			if (Event.type == sf::Event::Closed)
				window.close();
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();
		}

		float dt = Clock.restart().asSeconds(); //calculate delta time.

		
		gameDirector->Update(dt, runtimeClock.getElapsedTime().asMilliseconds());
		//std::cout << 1/dt << std::endl;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glDepthMask(GL_TRUE);

		gameDirector->Draw(&window);

		window.pushGLStates();
		UserInterface::draw(&window);
		window.popGLStates();
		window.display();


	}
	return EXIT_SUCCESS;
}