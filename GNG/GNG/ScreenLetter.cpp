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
	int x, y, width = 8, height = 8;
	
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
		y = 119;
		break;
	case Q:
		x = 9;
		y = 119;
		break;
	case R:
		x = 18;
		y = 119;
		break;
	case S:
		x = 27;
		y = 119;
		break;
	case T:
		x = 36;
		y = 119;
		break;
	case U:
		x = 45;
		y = 119;
		break;
	case V:
		x = 54;
		y = 119;
		break;
	case W:
		x = 63;
		y = 119;
		break;
	case X:
		x = 72;
		y = 119;
		break;
	case Y:
		x = 81;
		y = 119;
		break;
	case Z:
		x = 90;
		y = 119;
		break;
	case zero:
		x = 99;
		y = 30;
		break;
	case one:
		x = 108;
		y = 30;
		break;
	case two:
		x = 117;
		y = 30;
		break;
	case three:
		x = 126;
		y = 30;
		break;
	case four:
		x = 135;
		y = 30;
		break;
	case five:
		x = 144;
		y = 30;
		break;
	case six:
		x = 153;
		y = 30;
		break;
	case seven:
		x = 162;
		y = 30;
		break;
	case eight:
		x = 171;
		y = 30;
		break;
	case nine:
		x = 180;
		y = 30;
		break;
	case topscore:
		x = 100;
		y = 22;
		width = 75;
		break;
	case TIME:
		x = 64;
		y = 22;
		width = 34;
		break;
	case player1:
		x = 4;
		y = 22;
		width = 55;
		break;
	case space:
		x = 100;
		y = 0;
		break;
	case equals:
		x = 117;
		y = 101;
		break;
	case and:
		x = 54;
		y = 92;
		break;
	case comma:
		x = 108;
		y = 93;
		break;
	case PLUS:
		x = 99;
		y = 93;
		break;
	default:
		//x = 0;
		//y = 0;
		break;
	}

	sf::Texture texture;
	string misc = "../Resources/misc.png";
	if (!texture.loadFromFile(misc, IntRect(x, y, width, height))) {
		cout << "error loading texture: " << misc << endl;
	}
	letterTexture = texture;
	setTexture(letterTexture);
	setScale(sf::Vector2f(scaler, scaler));
}