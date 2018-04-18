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
    sf::Image map_image;
	map_image.loadFromFile("images/empty_cell.png");
	sf::Texture map_texture;
	map_texture.loadFromImage(map_image);
	sf::Sprite s_map;
	s_map.setTexture(map_texture);
    for (int i = 0; i < map_height; i++) {
        for (int j = 0; j < map_width; j++) {
            s_map.setTextureRect(sf::IntRect(0, 0, 50, 50));
            s_map.setPosition(j * 50, i * 50);
            win.draw(s_map);
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
    Texture scrollTexture;
    scrollTexture.loadFromFile("images/scroll.png");
    Sprite scrollSprite(scrollTexture);
    scrollSprite.setPosition(0, ycoord);
    window.draw(scrollSprite);
    return 0;
}
