#include "stdafx.h"
#include "ScreenLetter.h"
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

ScreenLetter::ScreenLetter() {
}

ScreenLetter::ScreenLetter(Letter letter) {
	setLetter(letter);
}


ScreenLetter::~ScreenLetter() {
}

void ScreenLetter::setLetter(Letter letter) {
	int x, y;
	
	switch (letter) {
	case A:
		x = 9;
		y = 110;
		break;
	case B:
		x = 18;
		y = 110;
		break;
	case C:
		x = 27;
		y = 110;
		break;
	case D:
		x = 36;
		y = 110;
		break;
	case E:
		x = 45;
		y = 110;
		break;
	case F:
		x = 54;
		y = 110;
		break;
	case G:
		x = 63;
		y = 110;
		break;
	case H:
		x = 72;
		y = 110;
		break;
	case I:
		x = 81;
		y = 110;
		break;
	case J:
		x = 90;
		y = 110;
		break;
	case K:
		x = 99;
		y = 110;
		break;
	case L:
		x = 108;
		y = 110;
		break;
	case M:
		x = 117;
		y = 110;
		break;
	case N:
		x = 126;
		y = 110;
		break;
	case O:
		x = 135;
		y = 110;
		break;
	case P:
		x = 0;
		y = 118;
		break;
	case Q:
		x = 9;
		y = 118;
		break;
	case R:
		x = 18;
		y = 118;
		break;
	case S:
		x = 27;
		y = 118;
		break;
	case T:
		x = 36;
		y = 118;
		break;
	case U:
		x = 45;
		y = 118;
		break;
	case V:
		x = 54;
		y = 118;
		break;
	case W:
		x = 63;
		y = 118;
		break;
	case X:
		x = 72;
		y = 118;
		break;
	case Y:
		x = 81;
		y = 118;
		break;
	case Z:
		x = 90;
		y = 118;
		break;
	default:
		break;
	}

	sf::Texture texture;
	string misc = "../Resources/misc.png";
	if (!texture.loadFromFile(misc, IntRect(x, y, 8 , 8))) {
		cout << "error loading texture: " << misc << endl;
	}
	letterTexture = texture;
	setTexture(letterTexture);
	setScale(sf::Vector2f(4, 4));
}