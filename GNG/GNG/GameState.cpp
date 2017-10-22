#include "stdafx.h"
#include "StateManager.h"
#include "GameState.h"
#include "ScreenLetter.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

GameState::GameState() {
}

GameState::~GameState() {
}

void GameState::processEvent(Event e) {
	
}

void GameState::step(int stepCount) {
	if (stepCount == 0) {
		loadLevel(home);
	}
	if (level == home) {
		updateHomeScreen(stepCount);
	}
}


void GameState::loadLevel(Level level) {
	switch (level) {
	case home: {
		double screenW = StateManager::shared().getScreenSize().x;
		double screenH = StateManager::shared().getScreenSize().y;
		clearVectors();

		//player 1 + score
		int startX = 40;
		ScreenLetter* player = new ScreenLetter(player1);
		player->setPosition(startX, 5);
		blocks.push_back(player);

		//top score + score
		startX = screenW / 2;
		ScreenLetter* topScore = new ScreenLetter(topscore); 
		topScore->setPosition(startX, 5);
		blocks.push_back(topScore);

		//title
		Block* title = new Block("title.png");
		title->setScale(2, 2);
		title->setPosition(screenW / 2 - title->getGlobalBounds().width / 2, screenH / 4);
		this->blocks.push_back(title);

		//press enter to start
		int arraySize = 20;
		int letterSpacing = 1;
		Letter pressEnterToStartLetters[] = { P,R,E,S,S,space,E,N,T,E,R,space,T,O,space,S,T,A,R,T };
		for (int i = 0; i < arraySize; i++) {
			ScreenLetter* letter = new ScreenLetter(pressEnterToStartLetters[i]);
			int offset = (i - arraySize / 2) * (letterSpacing + letter->getGlobalBounds().width);
			letter->setPosition(screenW / 2 + (offset), screenH / 4 + title->getGlobalBounds().height + 40);
			this->blocks.push_back(letter);
		}

		//1 coin 1 play
		arraySize = 12;
		Letter oneCoinOnePlay[] = { one,C,O,I,N,space,space,one,P,L,A,Y };
		for (int i = 0; i < arraySize; i++) {
			ScreenLetter* letter = new ScreenLetter(oneCoinOnePlay[i]);
			int offset = (i - arraySize / 2) * (letterSpacing + letter->getGlobalBounds().width);
			letter->setPosition(screenW / 2 + (offset), screenH / 2);
			this->blocks.push_back(letter);
		}


		//credit 1
		arraySize = 8;
		Letter credit1[] = { C,R,E,D,I,T,space,one };
		for (int i = 0; i < arraySize; i++) {
			ScreenLetter* letter = new ScreenLetter(credit1[i]);
			int offset = (letterSpacing + letter->getGlobalBounds().width) * i;
			letter->setPosition(40 + offset , screenH - letter->getGlobalBounds().height - 5);
			this->blocks.push_back(letter);
		}

		//rotating messages
		screenRotatingMessages.resize(3);

		arraySize = 25;
		Letter toMove[] = { A,R,R,O,W,space, K,E,Y,S,space, equals,space, M,O,V,E,space,and,space,C,L,I,M,B };
		for (int i = 0; i < arraySize; i++) {
			ScreenLetter* letter = new ScreenLetter(toMove[i]);
			int offset = (i - arraySize / 2) * (letterSpacing + letter->getGlobalBounds().width);
			letter->setPosition(screenW / 2 + (offset), screenH / 4 * 3);
			this->screenRotatingMessages.at(0).push_back(letter);
		}

		arraySize = 22;
		Letter jumptAndAttack[] = { S,P,A,C,E,space,equals,space,J,U,M,P,comma,space,F,space,equals,space,F,I,R,E };
		for (int i = 0; i < arraySize; i++) {
			ScreenLetter* letter = new ScreenLetter(jumptAndAttack[i]);
			int offset = (i - arraySize / 2) * (letterSpacing + letter->getGlobalBounds().width);
			letter->setPosition(screenW / 2 + (offset), screenH / 4 * 3);
			this->screenRotatingMessages.at(1).push_back(letter);
		}
		arraySize = 24;
		Letter madeBy[] = { C,PLUS,PLUS,space,V,E,R,S,I,O,N,space,M,A,D,E,space,B,Y,space,Z,A,C,H };
		for (int i = 0; i < arraySize; i++) {
			ScreenLetter* letter = new ScreenLetter(madeBy[i]);
			int offset = (i - arraySize / 2) * (letterSpacing + letter->getGlobalBounds().width);
			letter->setPosition(screenW / 2 + (offset), screenH / 4 * 3);
			this->screenRotatingMessages.at(2).push_back(letter);
		}
		break;
	}

	default:
		break;
	}
}

void GameState::updateHomeScreen(int stepCount) {
	screenMessage = &screenRotatingMessages.at((stepCount / StateManager::maxFPS % 3));
}

//clears the vectors that are used for drawing
//deletes all the pointers inside
void GameState::clearVectors() {
	for (int i = 0; i < mobs.size(); i++)
		delete mobs.at(i);
	for (int i = 0; i < blocks.size(); i++)
		delete blocks.at(i);
	for (int i = 0; i < background.size(); i++)
		delete background.at(i);
	for (int i = 0; i < screenRotatingMessages.size(); i++)
		for (int k = 0; k < screenRotatingMessages.at(i).size(); k++) 
			delete screenRotatingMessages.at(i).at(k);

	mobs.clear();
	blocks.clear();
	background.clear();
	screenRotatingMessages.clear();
}
