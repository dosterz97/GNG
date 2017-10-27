#pragma once

#include <SFML\Graphics.hpp>
#include "Mob.h"
#include <vector>
#include "Block.h"
#include "Quadtree.h"
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
	void step(int stepCount, View* view);
	void loadLevel(Level level = home);
	void updateHomeScreen(int stepCount);
	void moveMobs();
	void readMapFromFile(string name);
	void updateCenter(View* view);
	void checkCollisions();
	void fixCollision(Mob* m, Block* b);
	void fixCollision(Mob* m, Sprite* b);
	void updateQuadtree();

	vector<Drawable*> background;
	vector<Mob*> mobs;
	vector<Block*> blocks;
	vector<Block*>* screenMessage;
	vector<vector<Block*>> screenRotatingMessages;

	void setLevel(Level newLevel);

	static vector<int> getIntsFromListSeperatedBySpaces(string list);
	static const int mapWidthInBlocks = 200;
	static const int mapHeightInBlocks = 16;
	static const int sizeOfQuadtree = 10000;
	static const int sizeOfBlock = 50;
private: 
	Quadtree* quadtree;
	void clearVectors();
	Mob* player;
	Level level;
	int stepCount;
	Vector2f centerOfView = Vector2f(400, 400);
	int map[mapWidthInBlocks][mapHeightInBlocks] = {};
	bool canMove = false;
	int levelEnd = 0, levelBeginning = 0;
};

