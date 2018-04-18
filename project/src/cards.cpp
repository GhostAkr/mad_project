#include <iostream>
#include "cards.h"
#include "game.h"

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

card* card::create_card(CardID name, size_t x_start, size_t y_start) {
    card* ret;
    switch(name) {
        case FIREBOLT:
            firebolt srs(x_start, y_start);
            ret = &srs;
            break;
    }
    return ret;
}

card* create_card(CardID name) {
    card* ret;
    switch(name) {
        case FIREBOLT:
            ret = new firebolt;
            //firebolt srs;
            //ret = &srs;
            break;
    }
    return ret;
}

firebolt::firebolt() {
    xcoord_start = 0;
    ycoord_start = 0;
    shirt_image_path = "images/cards/shirts/firebolt.png";
    spell_image_path = "images/cards/spells/firebolt.png";
    tag = FIREBOLT;
    dmg = 3;
    for (size_t i = 0; i < ycoord_start; i++) {
        action_area.push_back(pair<int, int> (xcoord_start, ycoord_start + i));
    }
}

string card::get_shirt_image_path() {
    return shirt_image_path;
}

string card::get_spell_image_path() {
    return spell_image_path;
}
