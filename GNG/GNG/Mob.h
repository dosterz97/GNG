#pragma once

#include <SFML\Graphics.hpp>
#include <string.h>
#include "Block.h"

using namespace std;
using namespace sf;

enum Weapon {
	empty, axe, spear, knife, fire, shield
};

enum Direction {
	left, right, down, up
};

class Mob : public Block
{
public:
	Mob();
	Mob(string textureName, bool repeated = false, float x = 0, float y = 0, float width = -1, float height = -1);
	~Mob();

	void setSprite(string textureName, float x = 0, float y = 0, float width = -1, float height = -1);
	void moveMob();
	void attack(int step);

	void setWeapon(Weapon w);
	Weapon getWeapon();
	int getLastAttack();
	Direction getDirection();
	void loseLife(int l = 1);
	int getLife();
private:
	bool repeated = false;
	Weapon weapon = Weapon::empty;
	Direction facing = Direction::right;
	Texture mobTexture;
	int life = 1;
	int lastAttack = 0;
};

