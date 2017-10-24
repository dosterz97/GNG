#pragma once

#include <SFML\Graphics.hpp>
#include <string.h>
#include "Block.h"

using namespace std;
using namespace sf;

class Mob : public Block
{
public:
	Mob();
	Mob(string textureName, float x = 0, float y = 0, float width = -1, float height = -1);
	~Mob();

	void setSprite(string textureName, float x = 0, float y = 0, float width = -1, float height = -1);
	void moveMob();

private:
	Texture mobTexture;
	int life = 1;
};

