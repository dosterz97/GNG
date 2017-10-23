#include "stdafx.h"
#include "StateManager.h"
#include "Mob.h"
#include "ScreenLetter.h"

#include <ctime>
#include <ratio>
#include <chrono>
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;
using namespace chrono;

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
	startTime = high_resolution_clock::now();
	view = new View(sf::FloatRect(0, 0, getScreenSize().x, getScreenSize().y));
	window->setView(*view);
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

	for (int i = 0; i < currentState->mobs.size(); i++) 
		window->draw(*currentState->mobs.at(i));
	for (int i = 0; i < currentState->background.size(); i++) 
		window->draw(*currentState->background.at(i));
	for (int i = 0; i < currentState->blocks.size(); i++) 
		window->draw(*currentState->blocks.at(i));
	for (int i = 0; i < currentState->screenMessage->size(); i++)
		window->draw(*currentState->screenMessage->at(i));

	window->display();
}


//returns an exit code
int StateManager::gameLoop() {

	while (window->isOpen())
	{
		duration<double> time_span = duration_cast<duration<double>>(high_resolution_clock::now() - startTime);
		if (time_span.count() >  1.0 / maxFPS * stepCount) {
			//cout << time_span.count() << endl;
			//cout << "steps: " << stepCount << endl;
			Event event;
			while (window->pollEvent(event))
			{
				if (event.type == Event::Closed)
					window->close();
				else
					currentState->processEvent(event);
			}
			currentState->step(stepCount, view);
			draw();
			window->setView(*view);
			stepCount++;
		}
		else {
			//cout << "TOO FAST" << endl;
		}
	}

	return 0;
}
