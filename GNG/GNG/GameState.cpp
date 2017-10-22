#include "stdafx.h"
#include "GameState.h"
#include <iostream>

using namespace sf;
using namespace std;

GameState::GameState() {
}


GameState::~GameState() {
}

void GameState::processEvent(Event e) {
	
}

void GameState::step(int stepCount) {
	cout << stepCount << endl;
}

