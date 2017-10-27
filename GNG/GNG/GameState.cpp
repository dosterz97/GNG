#include "stdafx.h"
#include "StateManager.h"
#include "GameState.h"
#include "ScreenLetter.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>

using namespace sf;
using namespace std;

GameState::GameState() {
}

GameState::~GameState() {
}

void GameState::processEvent(Event e) {
	switch (e.type) {
	case Event::KeyPressed: {
		switch (e.key.code) {
		case Keyboard::Return:
			if (level == home && level != level1) {
				setLevel(level1);
				canMove = true;
			}
			break;
		case Keyboard::W:
		case Keyboard::Up:
			if (canMove) {
				player->setYVelocity(-20);
			}
			break;
		case Keyboard::A:
		case Keyboard::Left:
			if (canMove) {
				player->setXVelocity(-20);
			}
			break;
		case Keyboard::S:
		case Keyboard::Down:
			if (canMove) {
				player->setYVelocity(20);
			}
			break;
		case Keyboard::D:
		case Keyboard::Right:
			if (canMove) {
				player->setXVelocity(20);
			}
			break;
		case Keyboard::Space:
			break;
		}
		break;
	}
	case Event::KeyReleased: {
		switch (e.key.code) {
		case Keyboard::Return:
			break;
		case Keyboard::W:
		case Keyboard::Up:
			player->addToVelocity(Vector2f(0, -player->getVelocity().y));
			break;
		case Keyboard::A:
		case Keyboard::Left:
			player->addToVelocity(Vector2f(-player->getVelocity().x, 0));
			break;
		case Keyboard::S:
		case Keyboard::Down:
			player->addToVelocity(Vector2f(0, -player->getVelocity().y));
			break;
		case Keyboard::D:
		case Keyboard::Right:
			player->addToVelocity(Vector2f(-player->getVelocity().x, 0));
			break;
		case Keyboard::Space:
			break;
		}
		break;
	}
	}
}

void GameState::step(int stepCount, View* view) {
	if (stepCount == 0) {
		loadLevel(home);
	}
	moveMobs();
	updateQuadtree();
	checkCollisions();
	if (level == home) {
		updateHomeScreen(stepCount);
	}
	
	updateCenter(view);
}


void GameState::loadLevel(Level level) {
	switch (level) {
	case home: {
		double screenW = StateManager::shared().getScreenSize().x;
		double screenH = StateManager::shared().getScreenSize().y;
		clearVectors();
		levelEnd = StateManager::shared().getScreenSize().x;

		//Set up arthur
		player = new Mob("arthur.png", false, 134, 600, 18, 30);
		player->setTeam(friendly);
		player->setScale(2.75, 2.75);

		//set up quadtree
		quadtree = new Quadtree(0, FloatRect(0, -sizeOfQuadtree/2, sizeOfQuadtree, sizeOfQuadtree));

		//player 1 + score
		int startX = 40;
		ScreenLetter* player = new ScreenLetter(player1);
		player->setPosition(startX, 5);
		background.push_back(player);

		//top score + score
		startX = screenW / 2;
		ScreenLetter* topScore = new ScreenLetter(topscore); 
		topScore->setPosition(startX, 5);
		background.push_back(topScore);

		//title
		Block* title = new Block("title.png");
		title->setScale(2, 2);
		title->setPosition(screenW / 2 - title->getGlobalBounds().width / 2, screenH / 4);
		this->background.push_back(title);

		//press enter to start
		int arraySize = 20;
		int letterSpacing = 1;
		Letter pressEnterToStartLetters[] = { P,R,E,S,S,space,E,N,T,E,R,space,T,O,space,S,T,A,R,T };
		for (int i = 0; i < arraySize; i++) {
			ScreenLetter* letter = new ScreenLetter(pressEnterToStartLetters[i]);
			int offset = (i - arraySize / 2) * (letterSpacing + letter->getGlobalBounds().width);
			letter->setPosition(screenW / 2 + (offset), screenH / 4 + title->getGlobalBounds().height + 40);
			this->background.push_back(letter);
		}

		//1 coin 1 play
		arraySize = 12;
		Letter oneCoinOnePlay[] = { one,C,O,I,N,space,space,one,P,L,A,Y };
		for (int i = 0; i < arraySize; i++) {
			ScreenLetter* letter = new ScreenLetter(oneCoinOnePlay[i]);
			int offset = (i - arraySize / 2) * (letterSpacing + letter->getGlobalBounds().width);
			letter->setPosition(screenW / 2 + (offset), screenH / 2);
			this->background.push_back(letter);
		}

		//credit 1
		arraySize = 8;
		Letter credit1[] = { C,R,E,D,I,T,space,one };
		for (int i = 0; i < arraySize; i++) {
			ScreenLetter* letter = new ScreenLetter(credit1[i]);
			int offset = (letterSpacing + letter->getGlobalBounds().width) * i;
			letter->setPosition(40 + offset , screenH - letter->getGlobalBounds().height - 5);
			this->background.push_back(letter);
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
	
	case level1: {
		clearVectors();
		levelEnd = 8650;
		levelBeginning = 50;
		//set up arthur
		player->setPosition(200, (StateManager::shared().getScreenSize().y / 16 * 14 - player->getGlobalBounds().height));
		mobs.push_back(player);

		readMapFromFile("1.txt");
		for (int y = 0; y < mapHeightInBlocks; y++) {
			for (int x = 0; x < mapWidthInBlocks; x++) {
				Block* temp = nullptr;
				Block* temp2 = nullptr;
				Block* temp3 = nullptr;
				switch (map[x][y]) {
				case 0:
					break;
				case 1: 
					temp = new Block("/blocks/dirt.bmp");
					break;
				case 2:
					temp = new Block("/blocks/grassdirt.bmp");
					temp->setTeam(none);
					break;
				case 3:
					temp = new Block("/blocks/fence.png");
					break;
				case 4:
					temp = new Block("/blocks/grave1.png");
					break;
				case 5:
					temp = new Block("/blocks/grave2.png");
					break;
				case 6: {
					temp = new Block("/blocks/fence.png");
					temp2 = new Block("/blocks/tree1.png");
					temp2->setScale(0.5, 0.5);
					temp2->setPosition(x * temp2->getGlobalBounds().width, y * temp2->getGlobalBounds().height - temp2->getGlobalBounds().height * 2);
					temp2->setScale(1.5, 1.5);
					temp2->setTeam(Team::background);
					break;
				}
				case 7: {
					temp3 = new Block("/blocks/fence.png");
					temp2 = new Block("/blocks/tree2.png");
					temp2->setScale(0.5, 0.5);
					temp2->setPosition(x * temp2->getGlobalBounds().width, y * temp2->getGlobalBounds().height - temp2->getGlobalBounds().height * 1.5);
					temp2->setScale(1.25, 1.25);
					temp2->setTeam(Team::background);
					break;
				}
				case 8: {
					temp3 = new Block("/blocks/fence.png");
					temp2 = new Block("/blocks/tree1.png");
					temp2->setScale(0.5, 0.5);
					temp2->setPosition(x * temp2->getGlobalBounds().width, y * temp2->getGlobalBounds().height - temp2->getGlobalBounds().height * 2);
					temp2->setScale(-1.5, 1.5);
					temp2->setTeam(Team::background);
					break;
				}
				case 9: {
					temp3 = new Block("/blocks/fence.png");
					temp2 = new Block("/blocks/tree2.png");
					temp2->setScale(0.5, 0.5);
					temp2->setPosition(x * temp2->getGlobalBounds().width, y * temp2->getGlobalBounds().height - temp2->getGlobalBounds().height * 1.5);
					temp2->setScale(-1.25, 1.25);
					temp2->setTeam(Team::background);
					break;
				}
				case 10:
					temp = new Block("/blocks/water.png");
					break;
				case 11:
					temp2 = new Block("/blocks/largeDirt.png");
					temp2->setScale(0.5, 0.5);
					temp2->setPosition(x * sizeOfBlock, y * sizeOfBlock);
					temp2->setTeam(none);
					break;
				case 12:
					temp2 = new Block("/blocks/largeGrassdirt.png");
					temp2->setScale(0.5, 0.5);
					temp2->setPosition(x * sizeOfBlock, y * sizeOfBlock);
					temp2->setTeam(none);
					break;
				case 13:
					temp = new Block("/blocks/grave.png");
					temp->setTeam(none);
					break;
				case 14:
					temp = new Block("/blocks/vinerock.png");
					break;
				case 15:
					temp = new Block("/blocks/grassrock.png");
					temp->setTeam(none);
					break;
				case 16:
					temp = new Block("/blocks/rock.png");
					break;
				case 17:
					temp = new Block("/blocks/rock.png");
					temp2 = new Block("/blocks/grass.png");
					temp2->setScale(0.5, 0.5);
					temp2->setPosition(x * sizeOfBlock, y * sizeOfBlock);
					break;
				case 18:
					temp = new Block("/blocks/grass.png");
					break;
				case 19:
					temp = new Block("/blocks/grassrock.png");
					temp2 = new Block("/blocks/ladder.png");
					temp2->setScale(0.5, 0.5);
					temp2->setPosition(x * sizeOfBlock, y * sizeOfBlock);
					break;
				case 20:
					temp = new Block("/blocks/rock.png");
					temp2 = new Block("/blocks/ladder.png");
					temp2->setScale(0.5, 0.5);
					temp2->setPosition(x * sizeOfBlock, y * sizeOfBlock);
					break;
				case 21:
					temp = new Block("/blocks/rock.png");
					temp2 = new Block("/blocks/ladder.png");
					temp2->setScale(0.5, 0.5);
					temp2->setPosition(x * sizeOfBlock, y * sizeOfBlock);
					temp3 = new Block("/blocks/grass.png");
					break;
				case 22:
					temp3 = new Block("/blocks/grave.png");
					temp3->setTeam(none);
					temp = new Block("/blocks/rock.png");
					break;
				case 23:
					temp = new Block("/blocks/stone.png");		
					temp3 = new Block("/blocks/vines.png");
					temp3->setTeam(Team::background);
					break;
				case 24:
					temp2 = new Block("/blocks/metaldoor.png");
					temp2->setPosition(x * sizeOfBlock, y * sizeOfBlock);
					temp2->setScale(0.5, 1);
					break;
				case 25:
					temp = new Block("/blocks/stone.png");
					temp3 = new Block("/blocks/grass.png");
					temp2 = new Block("/blocks/vines.png");
					temp2->setScale(0.5, 0.5);
					temp2->setPosition(x * sizeOfBlock, y * sizeOfBlock);
					temp2->setTeam(Team::background);
					break;
				default:
					break;
				}

				if (temp != nullptr) {
					temp->setScale(0.5, 0.5);
					temp->setPosition(x * sizeOfBlock, y * sizeOfBlock);
					if (temp->getTeam() == 0)
						background.push_back(temp);
					else 
						blocks.push_back(temp);
				}
				if (temp2 != nullptr) {
					if (temp2->getTeam() == Team::background)
						background.push_back(temp2);
					else
						blocks.push_back(temp2);
				}
				if (temp3 != nullptr) {
					temp3->setScale(0.5, 0.5);
					temp3->setPosition(x * sizeOfBlock, y * sizeOfBlock);
					if (temp3->getTeam() == Team::background)
						background.push_back(temp3);
					else
						blocks.push_back(temp3);
				}
			}
		}
		break;
	}
	default:
		break;
	}
}

//rotates the message on the home screen about every 2 seconds
void GameState::updateHomeScreen(int stepCount) {
	screenMessage = &screenRotatingMessages.at((stepCount / (StateManager::maxFPS * 2)) % 3);
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


void GameState::moveMobs() {
	for (int i = 0; i < mobs.size(); i++) {
		mobs.at(i)->move(mobs.at(i)->getVelocity().x, mobs.at(i)->getVelocity().y);
	}
}

void GameState::setLevel(Level newLevel) {
	level = newLevel;
	loadLevel(level);
}

vector<int> GameState::getIntsFromListSeperatedBySpaces(string list) {
	vector<int> temp;

	int start = 0;
	int index = 0;
	string subStr = "";
	while (index < list.length()) {
		if (list.at(index) == ' ') {
			temp.push_back(atoi(subStr.c_str()));
			start = index + 1;//index gets incremented after this
		}
		else {
			subStr = list.substr(start, 1 + index - start);
		}
		index++;
	}
	return temp;
}

void GameState::readMapFromFile(string name) {
	int lineNum = 0;
	string line;
	ifstream myfile("../Resources/maps/" + name);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			vector<int> temp = getIntsFromListSeperatedBySpaces(line);
			for (int i = 0; i < temp.size(); i++) {
				this->map[i][lineNum] = temp.at(i);
			}
			lineNum++;
		}
		myfile.close();
	}
}

void GameState::updateCenter(View* view) {
	Vector2f center = Vector2f(player->getGlobalBounds().left + player->getGlobalBounds().width / 2, StateManager::shared().getScreenSize().y / 2);

	if(level == home)
		center = Vector2f(StateManager::shared().getScreenSize().x / 2, StateManager::shared().getScreenSize().y / 2);
	else if (center.x < StateManager::shared().getScreenSize().x / 2 + levelBeginning) 
		center.x = StateManager::shared().getScreenSize().x / 2 + levelBeginning;
	else if (center.x + StateManager::shared().getScreenSize().x / 2 > levelEnd) 
		center.x = levelEnd - StateManager::shared().getScreenSize().x / 2;

	view->setCenter(center);
}

//uses quad tree to check for intersections between sprites
void GameState::checkCollisions() {
	vector<Sprite*>* returnObjects = new vector<Sprite*>();
	for (int i = 0; i < mobs.size(); i++) {
		returnObjects->clear();
		returnObjects = quadtree->retrieve(returnObjects, mobs.at(i));
		if (returnObjects == NULL) {
			for (int k = 0; k < blocks.size(); k++) 
				if (blocks.at(i)->getTeam() == none) 
					if (blocks.at(k)->getGlobalBounds().intersects(mobs.at(i)->getGlobalBounds()))
						fixCollision(mobs.at(i), blocks.at(k));
		}
		else {
			for (int x = 0; x < returnObjects->size(); x++) 
				if (mobs.at(i)->getGlobalBounds().intersects(returnObjects->at(x)->getGlobalBounds()))
					fixCollision(mobs.at(i), returnObjects->at(x));
		}
	}
	if (returnObjects != NULL) {
		returnObjects->clear();
		delete returnObjects;
	}
}

//in orientation in respect to the mob
void GameState::fixCollision(Mob* m, Block* b) {
	FloatRect mRect = m->getGlobalBounds();
	FloatRect bRect = b->getGlobalBounds();

	float rightDistance = bRect.left -(mRect.left + mRect.width);
	float leftDistance = mRect.left - (bRect.left + bRect.width);
	float topDistance = mRect.top - (bRect.top + bRect.height);
	float bottomDistance = bRect.top - (mRect.top + mRect.height);

	bool rightCollision = rightDistance < 0 && abs(rightDistance) <= abs(m->getVelocity().x) && m->getVelocity().x > 0;
	bool leftCollision = leftDistance < 0 && abs(leftDistance) <= abs(m->getVelocity().x) && m->getVelocity().x < 0;
	bool bottomCollision = bottomDistance < 0 && abs(bottomDistance) <= abs(m->getVelocity().y) && m->getVelocity().y > 0;
	bool topCollision = topDistance < 0 && abs(topDistance) <= abs(m->getVelocity().y) && m->getVelocity().y < 0;

	if (bottomCollision) 
		m->move(0, bottomDistance);
	else if (topCollision)
		m->move(0, -topDistance);
	if (rightCollision) 
		m->move(rightDistance, 0);
	else if (leftCollision)
		m->move(-leftDistance, 0);
}

//in orientation in respect to the mob
void GameState::fixCollision(Mob* m, Sprite* b) {
	FloatRect mRect = m->getGlobalBounds();
	FloatRect bRect = b->getGlobalBounds();

	float rightDistance = bRect.left - (mRect.left + mRect.width);
	float leftDistance = mRect.left - (bRect.left + bRect.width);
	float topDistance = mRect.top - (bRect.top + bRect.height);
	float bottomDistance = bRect.top - (mRect.top + mRect.height);

	bool rightCollision = rightDistance < 0 && abs(rightDistance) <= abs(m->getVelocity().x) && m->getVelocity().x > 0;
	bool leftCollision = leftDistance < 0 && abs(leftDistance) <= abs(m->getVelocity().x) && m->getVelocity().x < 0;
	bool bottomCollision = bottomDistance < 0 && abs(bottomDistance) <= abs(m->getVelocity().y) && m->getVelocity().y > 0;
	bool topCollision = topDistance < 0 && abs(topDistance) <= abs(m->getVelocity().y) && m->getVelocity().y < 0;

	if (bottomCollision)
		m->move(0, bottomDistance);
	else if (topCollision)
		m->move(0, -topDistance);
	if (rightCollision)
		m->move(rightDistance, 0);
	else if (leftCollision)
		m->move(-leftDistance, 0);
}

void GameState::updateQuadtree() {
	quadtree->clear();
	for (int i = 0; i < mobs.size(); i++) 
		quadtree->insert(mobs.at(i));
	for (int i = 0; i < blocks.size(); i++) 
		quadtree->insert(blocks.at(i));

}


