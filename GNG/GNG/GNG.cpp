// GNG.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "StateManager.h"

using namespace sf;

int main()
{
	int exit = StateManager::shared().start();
	return exit;
}


