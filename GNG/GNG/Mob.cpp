#include "stdafx.h"
#include "Mob.h"
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

Mob::Mob() {
}

Mob::Mob(string textureName, float x, float y, float width, float height) {
	setSprite(textureName, x, y, width, height);
}

Mob::~Mob() {
}

void Mob::setSprite(string textureName, float x, float y, float width, float height) {
	sf::Texture texture;
	string resourceName = "../Resources/" + textureName;
	if (!texture.loadFromFile(resourceName)) {
		cout << "error loading texture: " << textureName << endl;
	}
	
	this->name = textureName;
	this->size = texture.getSize();
	setTexture(texture);
	if (width > 0 || height > 0) {
		setTextureRect(IntRect(x, y, width, height));
	}
}

void Mob::moveMob() {
}


