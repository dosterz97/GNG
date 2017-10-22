#pragma once

#include <SFML\Graphics.hpp>
#include "Mob.h"
#include <vector>

using namespace sf;
using namespace std; 

class GameState
{
public:
	GameState();
	~GameState();

	vector<Drawable> background;
	vector<Mob> mobs;
};

