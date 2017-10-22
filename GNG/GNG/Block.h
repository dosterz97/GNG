#pragma once
#include <SFML\Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Block : public Sprite
{
public:
	Block();
	Block(string textureName, float x = 0, float y = 0, float width = -1, float height = -1);
	~Block();
	

	void setSprite(string textureName, float x = 0, float y = 0, float width = -1, float height = -1);
	void moveBlock();

private:
	string name;
	Texture blockTexture;
	Vector2f velocity = Vector2f(0, 0);
	Vector2u size = Vector2u(0, 0);
	float gravityMultiplier = 0;
};

