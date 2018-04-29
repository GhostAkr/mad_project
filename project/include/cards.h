#ifndef PROJECT_INCLUDE_CARDS_H_
#define PROJECT_INCLUDE_CARDS_H_

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using std::string;
using std::vector;
using std::pair;

enum CardID {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
    VOID = 1111,
    FIREBOLT = 10
};

class card {
protected:
    size_t spell_x, spell_y;
    size_t xcoord_start, ycoord_start;
    string shirt_image_path;
    string spell_image_path;
    vector<pair<int, int>> action_area;
    CardID tag;
    int dmg;
    string name;
    sf::Texture spellTexture;
    int side;
    float tickDummy;
    sf::RenderTarget* targetDummy;
    bool boolDummy;
    vector<pair<int, int>> direction_area;
public:
    vector<pair<int, int>> get_direction_area();
    size_t get_spell_x();
    size_t get_spell_y();
    virtual ~card() {}
    static card* create_card(CardID name);
    static card* create_card(CardID name, size_t x_start, size_t y_start, int direction);
    virtual string get_shirt_image_path() = 0;
    vector<pair<int, int>> get_action_area();
    string get_name();
    string get_spell_image_path();
    int get_dmg();
    virtual void updateSpell(float tick, bool* isMoveSpell) = 0;
    virtual int drawCurrent(sf::RenderTarget& target) = 0;
    //virtual int set_action_area(int direction) = 0;
};

class firebolt : public card {
public:
    //int set_action_area(int direction);
    void updateSpell(float tick, bool* isMoveSpell);
    int drawCurrent(sf::RenderTarget& target);
    string get_shirt_image_path();
    firebolt();
    firebolt(size_t x_start, size_t y_start, int direction);
    ~firebolt() {}
};

#endif  // PROJECT_INCLUDE_CARDS_H_
