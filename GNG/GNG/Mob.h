#pragma once

#include <SFML\Graphics.hpp>
#include <string.h>
#include "Block.h"
#include "Animation.h"

using namespace std;
using namespace sf;



class Mob : public Block
{
public:
	Mob();
	Mob(string textureName, bool repeated = false, float x = 0, float y = 0, float width = -1, float height = -1, int creationStep = 0);
	~Mob();

	void setSprite(string textureName, float x = 0, float y = 0, float width = -1, float height = -1);
	void attack(int step);
	void stepAnimation(int animationStep);

	void setWeapon(Weapon w);
	Weapon getWeapon();
	int getLastAttack();
	void setDirection(Direction d);
	Direction getDirection();
	void loseLife(int l = 1);
	int getLife();
	MobType getMobType();
	void setMobType(MobType t);
	int getCreationStep();
	void setXVelocity(float t);
	void setVelocity(Vector2f t);
private:
	bool repeated = false;
	Weapon weapon = Weapon::empty;
	Direction facing = Direction::right;
	Texture mobTexture;
	MobType type;
	Animation animation;
	int life = 1;
	int lastAttack = 0;
	int creationStep = 0;
};

