#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "gui.h"

using std::cout;
using std::endl;

int main(/*int argc, const char** argv*/) {

    game_map field("/mnt/d/test-map");
    draw_map draw_field(field);
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
        draw_field.drawing(window);
		window.display();
	}
	return 0;
}
