#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/game.h"

using std::cout;
using std::endl;

int main(/*int argc, const char** argv*/) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "MAD");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.display();
	}
	return 0;
}
