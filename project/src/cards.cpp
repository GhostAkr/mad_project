#include <iostream>
#include "cards.h"

//CARDS METHODS

card* card::create_card(CardID name) {
    card* ret;
    switch(name) {
        case FIREBOLT:
            ret = new firebolt();
            break;
        case UP:
            ret = new up();
            break;
        case RIGHT:
            ret = new right();
            break;
        case DOWN:
            ret = new down();
            break;
        case LEFT:
            ret = new left();
            break;
        default:
            break;
    }
    return ret;
}

card* card::create_card(CardID name, size_t x_start, size_t y_start, int direction) {
    card* ret;
    switch(name) {
        case FIREBOLT:
            ret = new firebolt(x_start, y_start, direction);
            break;
        default:
            break;
    }
    return ret;
}

string card::get_spell_image_path() {
    return spell_image_path;
}

vector<pair<int, int>> card::get_action_area () {
    return action_area;
}

int card::get_dmg() {
    return dmg;
}

string card::get_name() {
    return name;
}

//FIREBOLT METHODS

firebolt::firebolt(size_t x_start, size_t y_start, int direction) {
    xcoord_start = x_start;
    ycoord_start = y_start;
    shirt_image_path = "images/cards/shirts/firebolt.png";
    spell_image_path = "images/cards/spells/firebolt.png";
    name = "FIREBOLT";
    tag = FIREBOLT;
    dmg = 3;
    switch (direction) {
        case 0:  // UP
            for (size_t i = 1; i <= ycoord_start; i++) {
                action_area.push_back(pair<int, int> (0, -i));
            }
            break;
        case 1:  // RIGHT
            for (size_t i = 1; i <= 12 - xcoord_start; i++) {
                action_area.push_back(pair<int, int> (i, 0));
            }
            break;
        case 2:  // DOWN
            for (size_t i = 1; i <= 12 - ycoord_start; i++) {
                action_area.push_back(pair<int, int> (0, i));
            }
            break;
        case 3:  // LEFT
            for (size_t i = 1; i <= xcoord_start; i++) {
                action_area.push_back(pair<int, int> (-i, 0));
            }
            break;
    }
}

firebolt::firebolt() {
    shirt_image_path = "images/cards/shirts/firebolt.png";
    tag = FIREBOLT;
    name = "FIREBOLT";
}

string firebolt::get_shirt_image_path() {
    return shirt_image_path;
}

//UP METHODS

up::up() {
    tag = UP;
    name = "UP";
}

string up::get_shirt_image_path() {
    return "";
}

//RIGHT METHODS

right::right() {
    tag = RIGHT;
    name = "RIGHT";
}

string right::get_shirt_image_path() {
    return "";
}

//DOWN METHODS

down::down() {
    tag = DOWN;
    name = "DOWN";
}

string down::get_shirt_image_path() {
    return "";
}

//LEFT MRTHODS

left::left() {
    tag = LEFT;
    name = "LEFT";
}

string left::get_shirt_image_path() {
    return "";
}
