#include "stdafx.h"
#include "StateManager.h"
#include "Mob.h"
#include "ScreenLetter.h"

#include <ctime>
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;


StateManager::StateManager() {
	this->window = new RenderWindow(sf::VideoMode(800, 600), "My window");
	this->currentState = new GameState();
}

StateManager::StateManager(string name, int width, int height) {
	this->window = new RenderWindow(sf::VideoMode(width, height), name);
	this->currentState = new GameState();
}

StateManager::~StateManager() {
}

int StateManager::start() {
	startTime = clock();

	return gameLoop();
}

void StateManager::quit() {

}

Vector2u StateManager::getScreenSize()
{
	return this->window->getSize();
}

void StateManager::draw() {
	window->clear();

	for (int i = 0; i < currentState->mobs.size(); i++) {
		window->draw(*currentState->mobs.at(i));
	}

	for (int i = 0; i < currentState->background.size(); i++) {
		window->draw(*currentState->background.at(i));
	}

	for (int i = 0; i < currentState->blocks.size(); i++) {
		window->draw(*currentState->blocks.at(i));
	}

	window->display();
}


//returns an exit code
int StateManager::gameLoop() {

	while (window->isOpen())
	{
		clock_t t = clock() - startTime;
		if ((double)t > maxFPS * stepCount) {
			Event event;
			while (window->pollEvent(event))
			{
				if (event.type == Event::Closed)
					window->close();
				else
					currentState->processEvent(event);
			}

			currentState->step(stepCount);
			draw();
			stepCount++;
		}
	}

	return 0;
}
