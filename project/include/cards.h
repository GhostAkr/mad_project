#ifndef PROJECT_INCLUDE_CARDS_H_
#define PROJECT_INCLUDE_CARDS_H_

#include <iostream>
#include <string>
#include <vector>

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
    card* create_card(CardID name);  // For drawing
    card* create_card(CardID name, size_t x_start, size_t y_start);
    string get_shirt_image_path();
    string get_spell_image_path();
};

class firebolt : public card {
public:
    firebolt();  // For drawing
    firebolt(size_t x_start, size_t y_start);
};

#endif  // PROJECT_INCLUDE_CARDS_H_
