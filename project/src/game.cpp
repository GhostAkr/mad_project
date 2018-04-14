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

    size_t rows_to_read;

    infile >> n_of_lines >> n_of_cols >> rows_to_read;

    field = SparseMatrix<Game_object>(n_of_lines, n_of_cols);

    size_t temp;
    size_t temp_x; 
    size_t temp_y;
    for (size_t i = 0; i < rows_to_read; ++i) {
        infile >> temp_x;
        infile >> temp_y;
        infile >> temp;
        field.set(Game_object(temp), temp_x + 1,temp_y + 1);  
    }
    
    infile.close();
}