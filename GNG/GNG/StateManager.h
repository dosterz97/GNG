#pragma once
#include <SFML\Graphics.hpp>
#include "GameState.h"
#include <string>

using namespace sf;
using namespace std;

class StateManager
{
public:
	StateManager();
	StateManager(string name, int width, int height);
	~StateManager();

	void start();
	void quit();
	int gameLoop();
	void draw();

private:
	GameState* currentState;
	RenderWindow* window;

};

