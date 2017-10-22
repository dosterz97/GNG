#pragma once
#include <SFML\Graphics.hpp>
#include "GameState.h"
#include <string>
#include <ctime>

using namespace sf;
using namespace std;

class StateManager
{
public:
public:
	static StateManager &shared() {
		static StateManager manager; return manager;
	}

	int start();
	void quit();
	Vector2u getScreenSize();

private:
	StateManager();
	StateManager(string name, int width, int height);
	~StateManager();

	int gameLoop();
	void draw();
	
	int maxFPS = 30;
	GameState* currentState;
	RenderWindow* window;
	clock_t startTime;
	int stepCount = 0;

};

