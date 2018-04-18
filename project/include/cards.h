#ifndef PROJECT_INCLUDE_CARDS_H_
#define PROJECT_INCLUDE_CARDS_H_

#include <iostream>
#include <string>
#include <vector>
//#include "game.h"

using std::string;
using std::vector;
using std::pair;


enum CardID {
    FIREBOLT = 10
};

class card {
protected:
    size_t xcoord_start, ycoord_start;
    string shirt_image_path;
    string spell_image_path;
    vector<pair<int, int>> action_area;
    CardID tag;
    int dmg;
public:
    //card(character& pers);
    card* create_card(CardID tag, size_t x_start, size_t y_start);
};

class firebolt : public card {
public:
    firebolt(size_t x_start, size_t y_start);
};

#endif  // PROJECT_INCLUDE_CARDS_H_
