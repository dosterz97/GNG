#include "stdafx.h"
#include "StateManager.h"
#include <SFML\Graphics.hpp>
#include "Mob.h"
#include "ScreenLetter.h"

using namespace sf;

StateManager::StateManager() {
	this->window = new RenderWindow(sf::VideoMode(800, 600), "My window");
}

StateManager::StateManager(string name, int width, int height) {
	this->window = new RenderWindow(sf::VideoMode(width, height), name);
}

StateManager::~StateManager() {
}

void StateManager::start() {

}

void StateManager::quit() {

}

void StateManager::draw() {
	window->clear();

	for (int i = 0; i < currentState->mobs.size(); i++) {
		window->draw(currentState->mobs.at(i));
	}

	for (int i = 0; i < currentState->background.size(); i++) {
		window->draw(currentState->background.at(i));
	}

	window->display();
}


//returns an exit code
int StateManager::gameLoop() {

	while (window->isOpen())
	{
		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
		}

		draw();
	}

	return 0;
}
