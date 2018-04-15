#include "../include/game.h"

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

game_map::game_map(string map_path) : field(1) {
    ifstream infile(map_path);
    if (!infile) {
        cout << "ERROR!!!" << endl;
    }
    infile >> n_of_lines >> n_of_cols;
    field = SparseMatrix<Game_object>(n_of_lines, n_of_cols);
    size_t temp;
    size_t temp_x;
    size_t temp_y;
    while(infile >> temp_x >> temp_y >> temp) {
        field.set(Game_object(temp), temp_x + 1, temp_y + 1);
    }
    infile.close();
}

size_t game_map::get_n_of_lines() {
    return n_of_lines;
}

size_t game_map::get_n_of_cols() {
    return n_of_cols;
}

SparseMatrix<Game_object> game_map::get_field() {
    return field;
}
