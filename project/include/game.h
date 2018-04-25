#ifndef PROJECT_INCLUDE_GAME_H_
#define PROJECT_INCLUDE_GAME_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include "../src/SparseMatrix.cpp"
#include "cards.h"

using std::vector;
using std::string;

enum Game_object
{
    PLAYER=1,
    ENEMY,
    WALL
};

class character {
protected:
    size_t xcoord, ycoord;
    vector<CardID> deck;
    int hp;
public:
    vector<CardID> avalible_cards;
    vector<CardID> chosen_cards;
    vector<CardID> chosen_actions;
    vector<int> directions;
    static character* create_character(Game_object character_type);
    int get_hp();
    int set_hp(int new_hp);
    size_t get_xcoord();
    size_t get_ycoord();
    int set_coords(size_t new_xcoord, size_t new_ycoord);
    vector<CardID> get_avalible_cards();
    virtual int create_avalible_cards() = 0;
    virtual ~character() {}
    virtual Game_object get_type() = 0;
};

class player : public character{
public:
    Game_object get_type();
    int create_avalible_cards();
    player(string map_path_player);
    ~player() {}
};

class npc : public character {
public:
    Game_object get_type();
    int create_avalible_cards();
    npc(string map_path_npc);
    ~npc() {}
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
    SparseMatrix<Game_object> get_field();
};

class battle {
public:
    battle();
    int fighting(vector<string> chosen_actions);
    int move(character* person, game_map& map, size_t new_xcoord, size_t new_ycoord);
    int play_card(CardID tag, size_t x, size_t y, int direction, player& player1, npc& npc1);
};

#endif  // PROJECT_INCLUDE_GAME_H_
