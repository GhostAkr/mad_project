#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "gui.h"

using namespace sf;
using std::cout;
using std::endl;

int main(/*int argc, const char** argv*/) {
    Clock clock;
    sf::RenderWindow window(sf::VideoMode(800, 600), "MAD");
    Vector2u win_coords = window.getSize();
    window.setVerticalSyncEnabled(true);
    /*background*/
    Texture bgTexture;
    bgTexture.loadFromFile("images/background.jpg");
    Sprite bgSprite(bgTexture);
    bgSprite.setPosition(0, 0);
    game_map field("/mnt/d/test-map");
    bool scroll_anim = false;
    size_t scroll_coord = win_coords.y + 10;
    // NEED TO IMPROVE
    player warrior("data/player");
    // NEED TO IMPROVE
    warrior.set_avalible_cards();
    // NEED TO IMPROVE
	while (window.isOpen())
	{
        float tick = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        tick = tick/100;
        window.draw(bgSprite); //background
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
        action_window act_win(window, field);
        Action_Button act_choice = act_win.get_button(window);
        if (act_choice == BEGBTN && scroll_anim == false) {
            scroll_anim = true;
        }
        // NEED TO IMPROVE
        planning scroll;
        // NEED TO IMPROVE
        /*Scroll animation*/
        if (scroll_anim) {
            if (scroll_coord > 20) {
                scroll.draw_scroll(window, scroll_coord);
                scroll_coord -= 0.1 * tick;
            } else {
                scroll_anim = false;
            }
        }
        scroll.draw_scroll(window, scroll_coord);
		window.display();
        //window.clear();
	}
	return 0;
}
