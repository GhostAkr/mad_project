#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "gui.h"

using namespace sf;

vector<int> planning::get_chosen_actions() {
    return chosen_actions;
}

draw_map::draw_map(game_map& map_object) {
    map_height = map_object.get_n_of_lines();
    map_width = map_object.get_n_of_cols();
    TileMap = map_object.get_field();
}

int draw_map::drawing(sf::RenderWindow& win) {
    //sf::Image map_image;
	//map_image.loadFromFile("images/empty_cell.png");
	//sf::Texture map_texture;
	//map_texture.loadFromImage(map_image);
	//sf::Sprite s_map;
	//s_map.setTexture(map_texture);
    for (size_t i = 0; i < map_height; i++) {
        for (size_t j = 0; j < map_width; j++) {
            Texture cellTexture;
            switch (TileMap.get(i + 1, j + 1)) {
                case WALL:
                    cellTexture.loadFromFile("images/wall.png");
                    break;
                default:
                    cellTexture.loadFromFile("images/empty_cell.png");
                    break;
            }
            Sprite cellSprite(cellTexture);
            cellSprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
            cellSprite.setPosition(j * 50, i * 50);
            win.draw(cellSprite);
        }
    }
    return 0;
}

buttons::buttons(int xc, int yc, string path) {
    xcoord = xc;
    ycoord = yc;
    image_path = path;
}

int buttons::draw_button(sf::RenderWindow& window) {
    Texture buttonTexture;
    buttonTexture.loadFromFile(image_path);
    Sprite buttonSprite(buttonTexture);
    buttonSprite.setPosition(xcoord, ycoord);
    window.draw(buttonSprite);
    return 0;
}
action_window::action_window(sf::RenderWindow& window, game_map& field) {
    draw_map field_draw(field);
    field_draw.drawing(window);
    buttons beginButton(10, 530, "images/buttons/begin_button.png");
    beginButton.draw_button(window);
    buttons endButton(230, 530, "images/buttons/end_button.png");
    endButton.draw_button(window);
}

Action_Button action_window::get_button(sf::RenderWindow& window) {
    if (Mouse::isButtonPressed(Mouse::Left)) {
        while (true) {
            if (!Mouse::isButtonPressed(Mouse::Left)) {
                break;
            }
        }
        if (IntRect(10, 530, 200, 32).contains(Mouse::getPosition(window))) {
            return BEGBTN;
        }
        if (IntRect(230, 530, 200, 32).contains(Mouse::getPosition(window))) {
            return ENDBTN;
        }
    }
    return VOID;
}

int planning::draw_scroll(sf::RenderWindow& window, size_t ycoord) {
    size_t xcoord = 130;
    size_t delta_x = 110;
    size_t delta_y = 200;
    scrollSprite.setPosition(0, ycoord);
    card1Sprite.setPosition(xcoord, ycoord + delta_y);
    card2Sprite.setPosition(xcoord += delta_x, ycoord + delta_y);
    card3Sprite.setPosition(xcoord += delta_x, ycoord + delta_y);
    card4Sprite.setPosition(xcoord += delta_x, ycoord + delta_y);
    card5Sprite.setPosition(xcoord += delta_x, ycoord + delta_y);
    window.draw(scrollSprite);
    window.draw(card1Sprite);
    window.draw(card2Sprite);
    window.draw(card3Sprite);
    window.draw(card4Sprite);
    window.draw(card5Sprite);
    return 0;
}

planning::planning(/*vector<CardID> avalible_cards*/) {
    //NEED TO IMPROVE
    card* ability;
    ability = new firebolt;
    //ability->create_card(FIREBOLT);
    card1Texture.loadFromFile(ability->get_shirt_image_path());
    card2Texture.loadFromFile(ability->get_shirt_image_path());
    card3Texture.loadFromFile(ability->get_shirt_image_path());
    card4Texture.loadFromFile(ability->get_shirt_image_path());
    card5Texture.loadFromFile(ability->get_shirt_image_path());
    card1Sprite.setTexture(card1Texture, true);
    card2Sprite.setTexture(card2Texture, true);
    card3Sprite.setTexture(card3Texture, true);
    card4Sprite.setTexture(card4Texture, true);
    card5Sprite.setTexture(card5Texture, true);
    //NEED TO IMPROVE
    scrollTexture.loadFromFile("images/scroll.png");
    scrollSprite.setTexture(scrollTexture, true);
}

//NEED TO IMPROVE
int planning::get_button(sf::RenderWindow& window) {
    while (true) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            while (true) {
                if (!Mouse::isButtonPressed(Mouse::Left)) {
                    break;
                }
            }
            if (IntRect(130, 200, 80, 180).contains(Mouse::getPosition(window))) {
                cout << "1" << endl;
                chosen_cards.push_back(1);
                return 0;
            }
            if (IntRect(240, 200, 80, 180).contains(Mouse::getPosition(window))) {
                cout << "2" << endl;
                chosen_cards.push_back(2);
                return 0;
            }
            if (IntRect(350, 200, 80, 180).contains(Mouse::getPosition(window))) {
                cout << "3" << endl;
                chosen_cards.push_back(3);
                return 0;
            }
            if (IntRect(460, 200, 80, 180).contains(Mouse::getPosition(window))) {
                cout << "4" << endl;
                chosen_cards.push_back(4);
                return 0;
            }
            if (IntRect(570, 200, 80, 180).contains(Mouse::getPosition(window))) {
                cout << "5" << endl;
                chosen_cards.push_back(5);
                return 0;
            }
        }
    }
    return 0;
}
//NEED TO IMPROVE

int planning::get_chosen_cards() {
    for (size_t i = 0; i < 3; i++) {
        cout << chosen_cards[i] << " ";
    }
    cout << endl;
    return 0;
}

int planning::remove_scroll(sf::RenderWindow& window, size_t ycoord) {
    size_t xcoord = 130;
    size_t delta_x = 110;
    size_t delta_y = 200;
    scrollSprite.setPosition(0, ycoord);
    card1Sprite.setPosition(xcoord, ycoord + delta_y);
    card2Sprite.setPosition(xcoord += delta_x, ycoord + delta_y);
    card3Sprite.setPosition(xcoord += delta_x, ycoord + delta_y);
    card4Sprite.setPosition(xcoord += delta_x, ycoord + delta_y);
    card5Sprite.setPosition(xcoord += delta_x, ycoord + delta_y);
    window.draw(scrollSprite);
    window.draw(card1Sprite);
    window.draw(card2Sprite);
    window.draw(card3Sprite);
    window.draw(card4Sprite);
    window.draw(card5Sprite);
    return 0;
}

int planning::choosing(sf::RenderWindow& window) {
    while (true) {
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            while (true) {
                if (!Keyboard::isKeyPressed(Keyboard::W)) {
                    break;
                }
            }
            cout << "0" << endl;
            chosen_actions.push_back(0);
            return 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            while (true) {
                if (!Keyboard::isKeyPressed(Keyboard::D)) {
                    break;
                }
            }
            cout << "1" << endl;
            chosen_actions.push_back(1);
            return 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            while (true) {
                if (!Keyboard::isKeyPressed(Keyboard::S)) {
                    break;
                }
            }
            cout << "2" << endl;
            chosen_actions.push_back(2);
            return 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            while (true) {
                if (!Keyboard::isKeyPressed(Keyboard::A)) {
                    break;
                }
            }
            cout << "3" << endl;
            chosen_actions.push_back(3);
            return 0;
        }
        if (Mouse::isButtonPressed(Mouse::Left)) {
            while (true) {
                if (!Mouse::isButtonPressed(Mouse::Left)) {
                    break;
                }
            }
            if (IntRect(510, 10, 80, 180).contains(Mouse::getPosition(window))) {
                cout << "10" << endl;
                chosen_actions.push_back(10);
                return 0;
            }
            if (IntRect(510, 200, 80, 180).contains(Mouse::getPosition(window))) {
                cout << "10" << endl;
                chosen_actions.push_back(10);
                return 0;
            }
            if (IntRect(510, 390, 80, 180).contains(Mouse::getPosition(window))) {
                cout << "10" << endl;
                chosen_actions.push_back(10);
                return 0;
            }
        }
    }
    return 0;
}

int planning::draw_options(sf::RenderWindow& window) {
    Sprite option1Sprite, option2Sprite, option3Sprite;
    Texture optionTexture;
    optionTexture.loadFromFile("images/cards/shirts/firebolt.png");
    option1Sprite.setTexture(optionTexture, true);
    option2Sprite.setTexture(optionTexture, true);
    option3Sprite.setTexture(optionTexture, true);
    option1Sprite.setPosition(510, 10);
    option2Sprite.setPosition(510, 200);
    option3Sprite.setPosition(510, 390);
    window.draw(option1Sprite);
    window.draw(option2Sprite);
    window.draw(option3Sprite);
    return 0;
}

int pers_anim::draw_pers(sf::RenderWindow& window, size_t x, size_t y) {
    Texture persTexture;
    persTexture.loadFromFile("images/mage.png");
    Sprite persSprite(persTexture);
    persSprite.setPosition(x, y);
    window.draw(persSprite);
    return 0;
}
