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
  	cout << new_xcoord << " " << new_ycoord << endl;
  	field.set(obj,new_ycoord + 1,new_xcoord + 1);
}

Game_object game_map::get(size_t xcoord,size_t ycoord) {
  Game_object cell_status = field.get(ycoord + 1,xcoord + 1);
  return cell_status;
}

character_type *character::get() {
  return person;
}

Game_object character::get_type()
{
  return type;
}

player::player(string map_path_player) {
ifstream infile(map_path_player);
if (!infile) {
    cout << "ERROR!!!" << endl;
}
infile >> xcoord >> ycoord;

}

npc::npc(string map_path_npc) {
ifstream infile(map_path_npc);
if (!infile) {
    cout << "ERROR!!!" << endl;
}
infile >> xcoord >> ycoord;
}

character::character (Game_object obj, string map_path_player_or_npc) {
  switch(obj) {
    case PLAYER:
      person = new player(map_path_player_or_npc);
      break;

    case ENEMY:
      person = new npc (map_path_player_or_npc);
      break;
  }
  type = obj;
}

character::~character() {
    delete person;
}

battle::battle(){};
int battle::move(character& person, game_map& map, size_t new_xcoord, size_t new_ycoord) {
  if ((new_xcoord < map.get_n_of_cols()-1) and (new_ycoord < map.get_n_of_lines()-1) and (new_xcoord > 0) and (new_ycoord > 0)) {
    size_t x = person.get()->get_xcoord();
    size_t y = person.get()->get_ycoord();
    Game_object obj_new = map.get(new_xcoord,new_ycoord);
    if (obj_new == 0) {
        if ((abs((int)x - (int)new_xcoord) + abs((int)y - (int)new_ycoord)) == 1) {
          person.get()->set_coords(new_xcoord, new_ycoord);
          map.set(Game_object(0), x, y);
          map.set(person.get_type(), new_xcoord, new_ycoord);
        }
    }
  }
  return 0;
}

SparseMatrix<Game_object> game_map::get_field() {
    return field;
}
