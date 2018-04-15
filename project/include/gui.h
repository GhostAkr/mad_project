#ifndef PROJECT_INCLUDE_GUI_H_
#define PROJECT_INCLUDE_GUI_H_

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "game.h"

using std::vector;
using std::string;

class planning {
private:
    vector<int> chosen_actions;  // Надо заполнить
public:
    vector<int> get_chosen_actions();
};

class draw_map {
private:
    int map_height;
    int map_width;
    SparseMatrix<Game_object> TileMap;
public:
    draw_map(game_map& field);
    int drawing(sf::RenderWindow& win);
};

#endif  // PROJECT_INCLUDE_GUI_H_
