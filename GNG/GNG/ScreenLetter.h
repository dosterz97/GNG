#pragma once
#include <SFML\Graphics.hpp>
#include "Block.h"

using namespace sf;

enum Letter {
	A, B, C, D, E, F, G,
	H, I, J, K, L, M, N,
	O, P, Q, R, S, T, U,
	V, W, X, Y, Z,
	one, two, three,
	four, five, six,
	seven, eight, nine,
	zero, topscore, TIME,
	player1, space,
	equals, and, comma,
	PLUS
};


class ScreenLetter : public Block
{
public:
	ScreenLetter();
	ScreenLetter(Letter);
	~ScreenLetter();

	void setLetter(Letter);
	double scaler = 3;
	Texture letterTexture;
};

