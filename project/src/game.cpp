#include <iostream>
#include <string>
#include "game.h"

int character_type::get_hp() {
    return hp;
}

int character_type::set_hp(int new_hp) {
    hp = new_hp;
    return 0;
}

size_t character_type::get_xcoord() {
    return xcoord;
}

size_t character_type::get_ycoord() {
    return ycoord;
}

int character_type::set_coords(size_t new_xcoord, size_t new_ycoord) {
    xcoord = new_xcoord;
    ycoord = new_ycoord; 
    return 0; 
}