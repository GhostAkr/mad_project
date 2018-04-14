#ifndef PROJECT_INCLUDE_GAME_H_
#define PROJECT_INCLUDE_GAME_H_

#include <vector>

using std::vector;
using std::string;

class character_type {
protected:
    size_t xcoord, ycoord;
    vector<string> avalible_cards;
    vector<string> chosen_actions;
    int hp;
public:
    int get_hp();
    int set_hp(int new_hp);
    int get_coords();
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
    vector<vector<string>> field;
public:
    game_map();
};

class battle {
public:
    int fighting(vector<string> chosen_actions);
    int move(character& person);
    // int play_card(); [LATER]
};

class card {
private:
    size_t xcoord_start, ycoord_start;
    string action;
    vector<string> action_area;
};

#endif  // PROJECT_INCLUDE_GAME_H_
