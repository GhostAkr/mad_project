#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "gui.h"

using std::cout;
using std::endl;
using namespace sf;

int main(/*int argc, const char** argv*/) {

    game_map field("/mnt/d/test-map");
    draw_map draw_field(field);
    sf::RenderWindow window(sf::VideoMode(800, 600), "MAD");
    Texture herotexture;
	herotexture.loadFromFile("images/hero.jpg");
	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(0, 0, 50, 50));//получили нужный нам прямоугольник с котом
    int x = 250, y = 250;
	herosprite.setPosition(x, y); //выводим спрайт в позицию x y
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
            herosprite.move(-50, 0);
            while (true) {
                if (!Keyboard::isKeyPressed(Keyboard::Left)) {
                    break;
                }
            }
        }
		window.clear();
        draw_field.drawing(window);
        window.draw(herosprite);
		window.display();
	}
	return 0;
}
