// GNG.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Mob.h"
#include "ScreenLetter.h"

using namespace sf;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Ghost N Goblins");
	
	Mob me = Mob("arthur.png");
	ScreenLetter a = ScreenLetter(V);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		//window.draw(me);
		window.draw(a);
		window.display();
	}

	return 0;
}


