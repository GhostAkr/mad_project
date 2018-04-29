#ifndef PROJECT_INCLUDE_GUI_H_
#define PROJECT_INCLUDE_GUI_H_

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "game.h"
using std::vector;
using std::string;

class entity {

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
    int x_pos, y_pos;
public:
    scroll();
    int drawCurrent(sf::RenderTarget& target);
    int set_coords(int x_delta, int y_delta);
    int set_avalible_cards(vector <CardID> new_cards);
    size_t get_y_pos();
};

class actions : public entity {
private:
    vector<sf::Texture> cardTexture;
    vector<CardID> chosen_cards;
public:
    actions(vector<CardID> new_cards);
    int drawCurrent(sf::RenderTarget& target, character* person1);
};

class creature : public entity {
protected:
    sf::Texture creatureTexture;
    sf::Sprite creatureSprite;
    creature_type type;
    int delta_x, delta_y;  // For updateCurrent
public:
    int x_pos, y_pos;
    static creature* create_creature(creature_type new_type, size_t xcoord, size_t ycoord);
    virtual int drawCurrent(sf::RenderTarget& target) = 0;
    int updateCurrent(character* person, float tick);  //Returns 1 to stop animation, 0 - other case
};

class dark_mage_draw : public creature {
public:
    dark_mage_draw(size_t x_coord, size_t y_coord);
    int drawCurrent(sf::RenderTarget& target);
    //void updateCurrent(int direction);
};

class bardess_draw : public creature {
public:
    bardess_draw(size_t x_coord, size_t y_coord);
    int drawCurrent(sf::RenderTarget& target);
    //void updateCurrent(int direction);
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
    int render(game_map& field_back);
    sf::RenderWindow window;
    sf::Texture bgTexture;  // Background
    sf::Sprite bgSprite;
    bool scrollUp;
    bool scrollDown;
    bool isBegBtn;
    bool isScrollBtn;
    bool isOptions;
    bool isChoosingOptions;
    bool isMoveAnim1;
    bool isMoveAnim2;
    bool isPlay;
    bool isBattle;
    bool isDrawSpell1;
    bool isMoveSpell1;
    bool isDrawSpell2;
    bool isMoveSpell2;
    bool isNPCPlay;
    bool isNPC;
    size_t cardsCounter;
    size_t cardsChoosed;
    size_t moveChoosed;
    size_t step;
    size_t stepDirection1;
    size_t stepDirection2;
    sf::Clock theclock;
    float tick;
    //sf::Time tick;
    scroll Scroll;
    card* Card;
    character* person1;
    character* person2;
    creature* creature1;
    creature* creature2;
    vector<CardID> cardNums;
    //string stat;
public:
    gui(character* pers1, character* pers2);
    int run(game_map& field_back);
    int set_cardNums (character* person, int num);
    void play(battle& fight, game_map& field_back);
    int handleDirection();
};

#endif  // PROJECT_INCLUDE_GUI_H_
