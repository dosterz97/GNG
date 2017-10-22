#pragma once

#include <SFML\Graphics.hpp>
#include "Mob.h"
#include <vector>
#include "Block.h"

using namespace sf;
using namespace std; 

enum Level {
	home,
	one1,
	one2,
	one3
};

class GameState
{
public:
	GameState();
	~GameState();

	void processEvent(Event e);
	void step(int stepCount);
	void loadLevel(Level level = home);
	void updateHomeScreen(int stepCount);
	vector<Drawable*> background;
	vector<Mob*> mobs;
	vector<Block*> blocks;
	vector<Block*>* screenMessage;
	vector<vector<Block*>> screenRotatingMessages;
	

private: 
	void clearVectors();
	Level level;
	int stepCount;
};

