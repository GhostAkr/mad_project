#ifndef PROJECT_INCLUDE_GUI_H_
#define PROJECT_INCLUDE_GUI_H_

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "game.h"
//#include "../src/cards.cpp"

using std::vector;
using std::string;

class entity {
public:
    //virtual int drawCurrent(sf::RenderTarget& target, sf::RenderStates states) = 0;
};

class battle_map : public entity {
private:
    sf::Texture wallTexture;
    sf::Texture cellTexture;
    size_t map_height;
    size_t map_width;
    SparseMatrix <Game_object> field;
    vector <vector <sf::Sprite>> mapSprite;
public:
    battle_map(SparseMatrix <Game_object> src_field);
    int set_mapSprite();
    size_t get_map_height();
    size_t get_map_width();
    sf::Sprite get_mapTile(size_t row, size_t col);
    int drawCurrent(sf::RenderTarget& target);
};

class scroll : public entity {
private:
    sf::Texture scrollTexture;
    sf::Sprite scrollSprite;
    vector <sf::Texture> cardTexture;
    vector <CardID> avalible_cards;
    size_t x_pos, y_pos;
    //vector <int> cards;
public:
    scroll();
    int drawCurrent(sf::RenderTarget& target);
    int set_coords(size_t x_delta, size_t y_delta);
    int set_avalible_cards(vector <CardID> new_cards);
    size_t get_y_pos();
};

class creature : public entity {
protected:
    sf::Texture creatureTexture;
    sf::Sprite creatureSprite;
    size_t x_pos, y_pos;
};

class dark_mage_draw : public creature {
public:
    dark_mage_draw(size_t x_coord, size_t y_coord);
    int drawCurrent(sf::RenderTarget& target);
};

class bardess_draw : public creature {
public:
    bardess_draw(size_t x_coord, size_t y_coord);
    int drawCurrent(sf::RenderTarget& target);
};

class button : public entity {
protected:
    sf::Texture buttonTexture;
    sf::Sprite buttonSprite;
    size_t x_pos, y_pos;
};

class start_turn_button : public button {
public:
    start_turn_button();
    int drawCurrent(sf::RenderTarget& target);
};

class gui {
private:
    int processEvents();
    int update();
    int render();
    sf::RenderWindow window;
    sf::Texture bgTexture;  // Background
    sf::Sprite bgSprite;
    bool scrollUp;
    sf::Clock theclock;
    float tick;
    scroll Scroll;
public:
    gui();
    int run();
    //int handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
};

/*
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
    vector<int> chosen_actions;  // 6 выбранных действий
    vector<int> chosen_cards;  // 3 выбранные способности
public:
    vector<int> get_chosen_actions();
    int draw_scroll(sf::RenderWindow& window, size_t ycoord);  // Анимация выезжающего свитка
    int get_button(sf::RenderWindow& window);  // Считывает нажатие на кнопку на свитке
    int remove_scroll(sf::RenderWindow& window);  // Анимация уезжающего свитка
    int choosing(sf::RenderWindow& window);  // Выбор последовательности действий
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
    Action_Button get_button(sf::RenderWindow& window);  // Считывает нажатие на кнопку
};
*/

#endif  // PROJECT_INCLUDE_GUI_H_
