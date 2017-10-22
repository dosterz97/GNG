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
	StateManager();
	StateManager(string name, int width, int height);
	~StateManager();

	int start();
	void quit();

private:
	int gameLoop();
	void draw();

	int maxFPS = 30;
	GameState* currentState;
	RenderWindow* window;
	clock_t startTime;
	int stepCount = 0;
};

