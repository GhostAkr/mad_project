#ifndef PROJECT_INCLUDE_GAME_H_
#define PROJECT_INCLUDE_GAME_H_

#include <iostream>
#include <string> 
#include <fstream>
#include <vector>

#include "../src/SparseMatrix.cpp"

using std::vector;
using std::string;

enum Game_object
{
    PLAYER=1,
    ENEMY
};

class character_type {
protected:
    size_t xcoord, ycoord;
    vector<string> avalible_cards;
    vector<string> chosen_actions;
    int hp;
public:
    int get_hp();
    int set_hp(int new_hp);
    size_t get_xcoord();
    size_t get_ycoord();
    int set_coords(size_t new_xcoord, size_t new_ycoord);
};

class player : public character_type {

};

class npc : public character_type {

};

class character {
private:
    character_type* person;
public:
    character();
};

class game_map {
private:
    size_t n_of_lines;
    size_t n_of_cols;
    SparseMatrix<Game_object> field;
public:
    game_map(string map_path);
};

class battle {
public:
    int fighting(vector<string> chosen_actions);
    int move(character& person, size_t new_xcoord, size_t new_ycoord);
    // int play_card(); [LATER]
};

class card {
private:
    size_t xcoord_start, ycoord_start;
    string action;
    vector<string> action_area;
};

#endif  // PROJECT_INCLUDE_GAME_H_
