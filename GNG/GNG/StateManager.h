#pragma once
#include <SFML\Graphics.hpp>
#include "GameState.h"
#include <iostream>
#include <string>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace sf;
using namespace std;
using namespace chrono;

class StateManager
{
public:
	static StateManager &shared() {
		static StateManager manager("Ghost N Goblins", 800, 800); return manager;
	}

	int start();
	void quit();
	Vector2u getScreenSize();
	static const int maxFPS = 30;
private:
	StateManager();
	StateManager(string name, int width, int height);
	~StateManager();

	int gameLoop();
	void draw();
	
	GameState* currentState;
	RenderWindow* window;
	View* view;
	high_resolution_clock::time_point startTime;
	int stepCount = 0;

};

