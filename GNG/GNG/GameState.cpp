#include "stdafx.h"
#include "StateManager.h"
#include "GameState.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

GameState::GameState() {
}

//GameState::GameState(StateManager myManager) {
	//manager = myManager;
//}


GameState::~GameState() {
}

void GameState::processEvent(Event e) {
	
}

void GameState::step(int stepCount) {
	if (stepCount == 0) {
		loadLevel(home);
	}
}


void GameState::loadLevel(Level level) {
	switch (level) {
	case home: {
		this->mobs.clear();
		this->background.clear();
		Block* title = new Block("title.png");
		title->setPosition(StateManager::shared().getScreenSize().x / 2 - title->getGlobalBounds().width / 2, StateManager::shared().getScreenSize().y / 4);
		this->blocks.push_back(title);
		break;
	}

	default:
		break;
	}
}
