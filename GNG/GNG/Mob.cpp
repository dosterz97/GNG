#include "stdafx.h"
#include "Mob.h"
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

Mob::Mob() {
}

Mob::Mob(string textureName, bool repeated, float x, float y, float width, float height) {
	this->repeated = repeated;
	this->setSprite(textureName, x, y, width, height);
}


Mob::~Mob() {
}

void Mob::setSprite(string textureName, float x, float y, float width, float height) {
	Texture texture;
	
	string resourceName = "../Resources/" + textureName;
	if (!texture.loadFromFile(resourceName)) {
		cout << "error loading texture: " << textureName << endl;
	}
	texture.setRepeated(repeated);

	name = textureName;
	size = texture.getSize();
	mobTexture = texture;
	setTexture(mobTexture);
	if (width > 0 && height > 0) {
		setTextureRect(IntRect(x, y, width, height));
		size = Vector2u(width, height);
	}
}

void Mob::moveMob() {
}

void Mob::attack(int step) {
	lastAttack = step;
}

void Mob::setWeapon(Weapon w) {
	weapon = w;
}

Weapon Mob::getWeapon() {
	return weapon;
}

int Mob::getLastAttack() {
	return lastAttack;
}

Direction Mob::getDirection()
{
	return facing;
}


