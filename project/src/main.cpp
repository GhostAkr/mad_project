#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "gui.h"

using std::cout;
using std::endl;

int main(/*int argc, const char** argv*/) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "MAD");
    game_map field("/mnt/d/test-map");
	while (window.isOpen())
	{
        /*action_window act_win(window, field);*/
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
