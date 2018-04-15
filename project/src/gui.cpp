#include <iostream>
#include <SFML/Graphics.hpp>
#include "gui.h"

vector<int> planning::get_chosen_actions() {
    return chosen_actions;
}

draw_map::draw_map(game_map& map_object) {
    map_height = map_object.get_n_of_lines();
    map_width = map_object.get_n_of_cols();
    TileMap = map_object.get_field();

}

int draw_map::drawing(sf::RenderWindow& win) {
    sf::Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/empty_cell.jpg");//загружаем файл для карты
	sf::Texture map_texture;//текстура карты
	map_texture.loadFromImage(map_image);//заряжаем текстуру картинкой
	sf::Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map_texture);//заливаем текстуру спрайтом
    for (int i = 0; i < map_height; i++) {
        for (int j = 0; j < map_width; j++) {
            s_map.setTextureRect(sf::IntRect(0, 0, 50, 50));
            s_map.setPosition(j * 50, i * 50);
            win.draw(s_map);
        }
    }
    return 0;
}
