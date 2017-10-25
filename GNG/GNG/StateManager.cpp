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

	for (int i = 0; i < currentState->background.size(); i++) 
		window->draw(*currentState->background.at(i));
	for (int i = 0; i < currentState->blocks.size(); i++) 
		window->draw(*currentState->blocks.at(i));
	for (int i = 0; i < currentState->screenMessage->size(); i++)
		window->draw(*currentState->screenMessage->at(i));
	for (int i = 0; i < currentState->mobs.size(); i++)
		if (currentState->mobs.at(i) != nullptr)
			window->draw(*currentState->mobs.at(i));

	RectangleShape rectangle(sf::Vector2f(1600, 1));
	rectangle.setPosition(sf::Vector2f(0, 200));
	window->draw(rectangle);
	RectangleShape rectangle2(sf::Vector2f(1600, 1));
	rectangle2.setPosition(sf::Vector2f(0, 400));
	window->draw(rectangle2);
	RectangleShape rectangle3(sf::Vector2f(1600, 1));
	rectangle3.setPosition(sf::Vector2f(0, 600));
	window->draw(rectangle3);
	RectangleShape rectangle4(sf::Vector2f(1, 800));
	rectangle4.setPosition(sf::Vector2f(800 ,0));
	window->draw(rectangle4);
	RectangleShape rectangle5(sf::Vector2f(1, 800));
	rectangle5.setPosition(sf::Vector2f(400, 0));
	window->draw(rectangle5);
	RectangleShape rectangle6(sf::Vector2f(1, 800));
	rectangle6.setPosition(sf::Vector2f(1200, 0));
	window->draw(rectangle6);

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
			window->setView(*view);
			draw();
			stepCount++;
		}
		else {
			//cout << "TOO FAST" << endl;
		}
	}

	return 0;
}
