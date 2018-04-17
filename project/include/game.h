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
public:
    player(string map_path_player);

};

class npc : public character_type {
public:
    npc(string map_path_npc);

};

class character {
private:
    character_type* person;
    Game_object type;
public:
    character(Game_object obj,string map_path_player_or_npc);
    character_type*get();
    Game_object get_type();
};

class game_map {
private:
    size_t n_of_lines;
    size_t n_of_cols;
    SparseMatrix<Game_object> field;

public:
    game_map(string map_path);
    size_t get_n_of_lines();
    size_t get_n_of_cols();
    void set(Game_object obj, size_t new_xcoord, size_t new_ycoord);
    Game_object get(size_t xcoord,size_t ycoord);
    void cout_field();
};

class battle {
public:
    battle();
    int fighting(vector<string> chosen_actions);
    int move(character& person, game_map& map, size_t new_xcoord, size_t new_ycoord);
    // int play_card(); [LATER]
};

class card {
private:
    size_t xcoord_start, ycoord_start;
    string action;
    vector<string> action_area;
};

#endif  // PROJECT_INCLUDE_GAME_H_
