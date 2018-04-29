#ifndef PROJECT_INCLUDE_GAME_H_
#define PROJECT_INCLUDE_GAME_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <sstream>
#include "../src/SparseMatrix.cpp"
#include "cards.h"

using std::vector;
using std::string;

enum creature_type {
    DARKMAGE,
    BARDESS
};

class character {
protected:
    int xcoord, ycoord;
    vector<CardID> deck;
    int hp;
    character* characterDummy;
public:
    vector<CardID> avalible_cards;
    vector<CardID> chosen_cards;
    vector<CardID> chosen_actions;
    vector<int> directions;
    creature_type cr_type;
    static character* create_character(Game_object character_type, creature_type type);
    int get_hp();
    int set_hp(int new_hp);
    int get_xcoord();
    int get_ycoord();
    int set_coords(size_t new_xcoord, size_t new_ycoord);
    vector<CardID> get_avalible_cards();
    virtual int create_avalible_cards() = 0;
    virtual ~character() {}
    virtual Game_object get_type() = 0;
    virtual int play_dark_mage(character* player) = 0;
};

class player : public character{
public:
    Game_object get_type();
    int create_avalible_cards();
    player(string map_path_player, creature_type type);
    ~player() {}
    //AI
    int play_dark_mage(character* player);
};

class npc : public character {
public:
    Game_object get_type();
    int create_avalible_cards();
    npc(string map_path_npc, creature_type type);
    ~npc() {}
    // AI
    int play_dark_mage(character* player);

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
    //battle();
    int fighting(character* person1, character* person2, game_map& map);
    int move(character* person, game_map& map, size_t new_xcoord, size_t new_ycoord);
    int play_card(CardID tag, int x, int y, character* player1, character* npc1);
};

#endif  // PROJECT_INCLUDE_GAME_H_
