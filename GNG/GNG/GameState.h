#pragma once

#include <SFML\Graphics.hpp>
#include "Mob.h"
#include <vector>
#include "Block.h"
#include <string>

using namespace sf;
using namespace std; 

enum Level {
	home = 0, 
	level1,	level2, level3,
	level4, level5, level6 
};

enum Background {
	black, grass, dirt
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
	void moveMobs();
	void readMapFromFile(string name);

	vector<Drawable*> background;
	vector<Mob*> mobs;
	vector<Block*> blocks;
	vector<Block*>* screenMessage;
	vector<vector<Block*>> screenRotatingMessages;

	void setLevel(Level newLevel);

	static vector<int> getIntsFromListSeperatedBySpaces(string list);
private: 
	void clearVectors();
	Level level;
	int stepCount;

	int map[400][20] = {};
};

