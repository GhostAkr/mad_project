#include "game.h"

// CHARACTER METHODS

int character::get_hp() {
    return hp;
}

int character::set_hp(int new_hp) {
    hp = new_hp;
    return 0;
}

size_t character::get_xcoord() {
    return xcoord;
}

size_t character::get_ycoord() {
    return ycoord;
}

int character::set_coords(size_t new_xcoord, size_t new_ycoord) {
    xcoord = new_xcoord;
    ycoord = new_ycoord;
    return 0;
}

character* character::create_character(Game_object character_type) {
    character* ret;
    switch (character_type) {
        case PLAYER:
            ret = new player("data/player");
            break;
        case ENEMY:
            ret = new npc("data/npc");
            break;
        default:
            break;
    };
    return ret;
}

vector<CardID> character::get_avalible_cards() {
    return avalible_cards;
}

// GAME_MAP METHODS

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
        field.set(Game_object(temp), temp_y + 1, temp_x + 1);
    }
    infile.close();
}

void game_map::cout_field() {
	cout << field << endl;
	cout << endl;
}

size_t game_map::get_n_of_lines() {
    return n_of_lines;
}

size_t game_map::get_n_of_cols() {
    return n_of_cols;
}

void game_map::set(Game_object obj, size_t new_xcoord, size_t new_ycoord) {
  	field.set(obj,new_ycoord + 1,new_xcoord + 1);
}

Game_object game_map::get(size_t xcoord,size_t ycoord) {
  Game_object cell_status = field.get(ycoord + 1,xcoord + 1);
  return cell_status;
}

SparseMatrix<Game_object> game_map::get_field() {
    return field;
}

// PLAYER METHODS

player::player(string map_path_player) {
    ifstream infile(map_path_player);
    if (!infile) {
        cout << "Player creation error!" << endl;
    }
    infile >> xcoord >> ycoord;
    int tag;
    while (true) {
        infile >> tag;
        if (tag == 1111) {
            break;
        }
        deck.push_back(CardID(tag));
    }
    infile.close();
}

int player::create_avalible_cards() {
    srand(time(0));
    for (size_t i = 0; i < 5; i++) {
        size_t card_num = rand() % deck.size() + 1;
        avalible_cards.push_back(deck[card_num - 1]);
    }
    return 0;
}

Game_object player::get_type() {
    return PLAYER;
}

// NPC METHODS

npc::npc(string map_path_npc) {
    ifstream infile(map_path_npc);
    if (!infile) {
        cout << "NPC creation error!" << endl;
    }
    infile >> xcoord >> ycoord;
    int tag;
    while (true) {
        infile >> tag;
        if (tag == 1111) {
            break;
        }
        deck.push_back(CardID(tag));
    }
    infile.close();
}

int npc::create_avalible_cards() {
    srand(time(0));
    for (size_t i = 0; i < 5; i++) {
        size_t card_num = rand() % deck.size() + 1;
        avalible_cards.push_back(deck[card_num - 1]);
    }
    return 0;
}

Game_object npc::get_type() {
    return ENEMY;
}

// BATTLE METHODS

int battle::move(character* person, game_map& map, size_t new_xcoord, size_t new_ycoord) {
  if ((new_xcoord < map.get_n_of_cols()-1) and (new_ycoord < map.get_n_of_lines()-1) and (new_xcoord > 0) and (new_ycoord > 0)) {
    size_t x = person->get_xcoord();
    size_t y = person->get_ycoord();
    Game_object obj_new = map.get(new_xcoord,new_ycoord);
    if (obj_new == 0) {
        if ((abs((int)x - (int)new_xcoord) + abs((int)y - (int)new_ycoord)) == 1) {
          map.set(Game_object(0), x, y);
          map.set(person->get_type(), new_xcoord, new_ycoord);
        }
    }
  }
  return 0;
}
