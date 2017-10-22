#include "stdafx.h"
#include "Block.h"
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

Block::Block() {
}

Block::Block(string textureName, float x, float y, float width, float height) {
	setSprite(textureName, x, y, width, height);
}


Block::~Block() {
}


void Block::setSprite(string textureName, float x, float y, float width, float height) {
	sf::Texture texture;
	string resourceName = "../Resources/" + textureName;
	if (!texture.loadFromFile(resourceName)) {
		cout << "error loading texture: " << textureName << endl;
	}

	name = textureName;
	size = texture.getSize();
	blockTexture = texture;
	setTexture(blockTexture);
	if (width > 0 || height > 0) {
		setTextureRect(IntRect(x, y, width, height));
		size = Vector2u(width, height);
	}
}

void Block::moveBlock() {
}