#ifndef PROJECT_INCLUDE_GUI_H_
#define PROJECT_INCLUDE_GUI_H_

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "cards.h"

using std::vector;
using std::string;
using namespace sf;

enum Action_Button {
    VOID,
    BEGBTN,
    ENDBTN
};

class buttons {
private:
    int xcoord, ycoord;  // Координаты кнопки
    string image_path;
public:
    buttons(int xc, int yc, string path);  // Конструктор принимает размер и координаты кнопки [Done]
    int draw_button(sf::RenderWindow& window);  // Рисует кнопку на window [Done]
};

class planning {
private:
    Texture card1Texture, card2Texture, card3Texture, card4Texture, card5Texture;
    Sprite card1Sprite, card2Sprite, card3Sprite, card4Sprite, card5Sprite;
    Texture scrollTexture;
    Sprite scrollSprite;
    vector<int> chosen_actions;  // 6 выбранных действий
    vector<int> chosen_cards;  // 3 выбранные способности
public:
    planning(/*vector<CardID> avalible_cards*/);
    vector<int> get_chosen_actions();
    int draw_scroll(sf::RenderWindow& window, size_t ycoord);  // Анимация выезжающего свитка
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
    action_window(sf::RenderWindow& window, game_map& field);  // Рисует поле и кнопки
    /*Кнопки рисовать через класс buttons*/
    /*Карту рисовать через класс draw_map*/
    /*Позднее сюда можно добавить методы рисования дополнительных элементов*/
    Action_Button get_button(sf::RenderWindow& window);  // Считывает нажатие на кнопку
    /*В зависимости от нажатой кнопки вызывает создает необходимый объект
    и вызывает соответствующий метод*/
};

#endif  // PROJECT_INCLUDE_GUI_H_
