#pragma once

#include <SFML\Graphics.hpp>
#include <string.h>

using namespace std;
using namespace sf;

class Mob : public Sprite
{
public:
	Mob();
	Mob(string textureName, float x = 0, float y = 0, float width = -1, float height = -1);
	~Mob();

	void setSprite(string textureName, float x = 0, float y = 0, float width = -1, float height = -1);
	void moveMob();

private:
	string name;
	Texture mobTexture;
	Vector2f velocity = Vector2f(0, 0);
	Vector2u size = Vector2u(0, 0);
	int life = 1;
	float gravityMultiplier;
};

