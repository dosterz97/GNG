#include "stdafx.h"
#include "Mob.h"
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

Mob::Mob() {
}

Mob::Mob(string textureName, bool repeated, float x, float y, float width, float height, int creationStep) {
	this->creationStep = creationStep;
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
	setOrigin(Vector2f(getGlobalBounds().width / 2, getGlobalBounds().height / 2));
}

void Mob::attack(int step) {
	lastAttack = step;
}

void Mob::stepAnimation(int animationStep) {
	switch (animation.getAnimationType()) {
	case stand:
		animation.setFrame(0);
		setTextureRect(animation.getCurrentFrame());
		break;
	case walking:
		if (animationStep % 5 == 3) {
			animation.nextFrame();
			setTextureRect(animation.getCurrentFrame());
		}
		break;
	default:
		break;
	}
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

void Mob::setDirection(Direction d) {
	if(d != facing)
		setScale(-getScale().x,getScale().y);
	facing = d;
}

Direction Mob::getDirection() {
	return facing;
}

void Mob::loseLife(int l) {
	life -= l;
}

int Mob::getLife() {
	return life;
}

MobType Mob::getMobType() {
	return type;
}

void Mob::setMobType(MobType t) {
	type = t;
	animation = Animation(type);
}

int Mob::getCreationStep() {
	return creationStep;
}

void Mob::setXVelocity(float t) {
	Block::setXVelocity(t);
	
	if (t != 0) 
		animation.setAnimationType(AnimationType::walking);
	else
		animation.setAnimationType(AnimationType::stand);
}

void Mob::setVelocity(Vector2f t) {
	Block::setVelocity(t);

	if (t.x != 0) 
		animation.setAnimationType(AnimationType::walking);
	else
		animation.setAnimationType(AnimationType::stand);
}


