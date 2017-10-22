// GNG.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "StateManager.h"
using namespace sf;

int main()
{
	StateManager gng = StateManager("Ghost N Goblins", 800, 800);

	int exit = gng.gameLoop();

	return exit;
}


