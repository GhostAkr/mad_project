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
    bool scroll_draw_anim = false;
    bool scroll_remove_anim = false;
    bool is_scroll = false;
    bool is_action_window = true;
    bool is_options = false;
    bool draw_options = false;
    bool is_battle = false;
    size_t step = 0;
    size_t scroll_coord = win_coords.y + 10;
    // NEED TO IMPROVE
    player warrior("data/player");
    // NEED TO IMPROVE
    warrior.set_avalible_cards();
    // NEED TO IMPROVE
    Action_Button act_choice = VOID;
	while (window.isOpen())
	{
        Texture npcTexture;
        npcTexture.loadFromFile("images/timmy.png");
        Sprite npcSprite(npcTexture);
        npcSprite.setPosition(250, 50);
        Texture mageTexture;
        mageTexture.loadFromFile("images/mage.png");
        Sprite mageSprite(mageTexture);
        mageSprite.setPosition(warrior.get_xcoord() * 50, warrior.get_ycoord() * 50);
        float tick = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        tick = tick/800;
        window.draw(bgSprite); //background
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
        action_window act_win(window, field);
        window.draw(mageSprite);
        window.draw(npcSprite);
        if (is_action_window) {
            act_choice = act_win.get_button(window);
        }
        if (act_choice == BEGBTN && scroll_draw_anim == false) {
            scroll_draw_anim = true;
        }
        // NEED TO IMPROVE
        planning scroll;
        // NEED TO IMPROVE
        /*Scroll animation*/
        if (scroll_draw_anim) {
            if (scroll_coord > 20) {
                scroll.draw_scroll(window, scroll_coord);
                scroll_coord -= 0.1 * tick;
            } else {
                scroll_draw_anim = false;
                is_scroll = true;
                is_action_window = false;
            }
        }
        if (is_scroll) {
            scroll.get_button(window);
            scroll.get_button(window);
            scroll.get_button(window);
            is_scroll = false;
            scroll_remove_anim = true;
        }
        //scroll.get_chosen_cards();
        if (!is_action_window) {
            scroll.draw_scroll(window, scroll_coord);
        }
        if (scroll_remove_anim) {
            if (scroll_coord < 610) {
                scroll_coord += 0.1 * tick;
                scroll.remove_scroll(window, scroll_coord);
            } else {
                scroll_remove_anim = false;
                is_action_window = true;
                draw_options = true;
            }
        }
        if (draw_options) {
            scroll.draw_options(window);
            is_options = true;
        }
        window.display();
        if (is_options) {
            scroll.choosing(window);
            scroll.choosing(window);
            scroll.choosing(window);
            scroll.choosing(window);
            scroll.choosing(window);
            scroll.choosing(window);
            is_battle = true;
            is_options = false;
        }
        if (is_battle) {
            float tick = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            tick = tick/800;
            while (true) {
                //float tick = clock.getElapsedTime().asMicroseconds();
                //clock.restart();
                //tick = tick/800;
                //cout << "Tick is " << tick << endl;
                battle mad;
                vector<int> chosen_actions = scroll.get_chosen_actions();
                mad.fighting(chosen_actions[step], warrior, field);
                cout << "Step is " << step << endl;
                if (chosen_actions[step] == 0 || chosen_actions[step] == 1 || chosen_actions[step] == 2 || chosen_actions[step] == 3) {
                    //cout << "Test" << endl;
                    //pers_anim pp;
                    size_t x_begin = mageSprite.getPosition().x;
                    size_t y_begin = mageSprite.getPosition().y;
                    cout << "x_begin = " << x_begin << endl;
                    cout << "y_begin = " << y_begin << endl;
                    cout << "to x = " << warrior.get_xcoord() * 50 << endl;
                    cout << "to y = " << warrior.get_ycoord() * 50 << endl;
                    while ((x_begin != warrior.get_xcoord() * 50) || (y_begin != warrior.get_ycoord() * 50)) {
                        switch (chosen_actions[step]) {
                            case 0:
                                y_begin -= 1;// * tick;
                                break;
                            case 1:
                                x_begin += 1;// * tick;
                                break;
                            case 2:
                                y_begin += 1;// * tick;
                                break;
                            case 3:
                                x_begin -= 1;// * tick;
                                break;
                        }
                        mageSprite.setPosition(x_begin, y_begin);
                        action_window act_win(window, field);
                        window.draw(npcSprite);
                        window.draw(mageSprite);
                        window.display();
                    }
                }
                if (step == 6) {
                    step = 0;
                    is_battle = false;
                    act_choice = VOID;
                    draw_options = false;
                    break;
                }
                step++;
            }
        }
		window.display();
        window.clear();
	}
	return 0;
}
