#ifndef PROJECT_INCLUDE_GUI_H_
#define PROJECT_INCLUDE_GUI_H_

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "game.h"

using std::vector;
using std::string;

class buttons {
private:
    int xcoord, ycoord;  // Координаты кнопки
    int xsize, ysize;  // Размеры кнопки
public:
    buttons(int xc, int yc, int xs, int ys);  // Конструктор принимает размер и координаты кнопки
    int draw_button(sf::RenderWindow& window);  // Рисует кнопку на window
};


class planning {
private:
    vector<int> chosen_actions;  // 6 выбранных действий
    vector<int> chosen_cards;  // 3 выбранные способности
public:
    vector<int> get_chosen_actions();
    int draw_scroll(sf::RenderWindow& window);  // Анимация выезжающего свитка
    int get_button(sf::RenderWindow& window);  // Считывает нажатие на кнопку на свитке
    /*Заполняется chosen_cards*/
    int remove_scroll(sf::RenderWindow& window);  // Анимация уезжающего свитка
    int choosing(sf::RenderWindow& window);  // Выбор последовательности действий
    /*Заполняется chosen_actions*/
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

class action_window {
public:
    action_window(sf::RenderWindow& window, draw_map& field);  // Рисует поле и кнопки
    /*Кнопки рисовать через класс buttons*/
    /*Карту рисовать через класс draw_map*/
    /*Позднее сюда можно добавить методы рисования дополнительных элементов*/
    int get_button(sf::RenderWindow& window);  // Считывает нажатие на кнопку
    /*В зависимости от нажатой кнопки вызывает создает необходимый объект
    и вызывает соответствующий метод*/
};

#endif  // PROJECT_INCLUDE_GUI_H_
