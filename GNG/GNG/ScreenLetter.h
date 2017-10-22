#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

enum Letter {
	A, B, C, D, E, F, G,
	H, I, J, K, L, M, N,
	O, P, Q, R, S, T, U,
	V, W, X, Y, Z
};


class ScreenLetter : public Sprite
{
public:
	ScreenLetter();
	ScreenLetter(Letter);
	~ScreenLetter();

	void setLetter(Letter);

	Texture letterTexture;
};

