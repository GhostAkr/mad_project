#include <iostream>
#include "cards.h"

//CARDS METHODS

card* card::create_card(CardID name) {
    card* ret;
    switch(name) {
        case FIREBOLT:
            ret = new firebolt();
            break;
        default:
            break;
    }
    return ret;
}

card* card::create_card(CardID name, size_t x_start, size_t y_start) {
    card* ret;
    switch(name) {
        case FIREBOLT:
            ret = new firebolt(x_start, y_start);
            break;
    }
    return ret;
}

//FIREBOLT METHODS

firebolt::firebolt(size_t x_start, size_t y_start) {
    xcoord_start = x_start;
    ycoord_start = y_start;
    shirt_image_path = "images/cards/shirts/firebolt.png";
    spell_image_path = "images/cards/spells/firebolt.png";
    tag = FIREBOLT;
    dmg = 3;
    for (size_t i = 0; i < ycoord_start; i++) {
        action_area.push_back(pair<int, int> (xcoord_start, ycoord_start + i));
    }
}

firebolt::firebolt() {
    shirt_image_path = "images/cards/shirts/firebolt.png";
    tag = FIREBOLT;
}

string firebolt::get_shirt_image_path() {
    return shirt_image_path;
}

string card::get_spell_image_path() {
    return spell_image_path;
}
