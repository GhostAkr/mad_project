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
    size_t amount;
    infile >> n_of_lines >> n_of_cols>>amount;
    field = SparseMatrix<Game_object>(n_of_lines, n_of_cols);
    size_t temp;
    size_t temp_x;
    size_t temp_y;

    // while(infile >> temp_x >> temp_y >> temp) {
    //     field.set(Game_object(temp), temp_x + 1, temp_y + 1);
    // }
    for (size_t i = 0; i < amount; ++i) {
      infile >> temp_x >> temp_y >> temp;
      field.set(Game_object(temp), temp_x + 1, temp_y + 1);   
    }

    infile.close();
    cout << field << endl;
}

size_t game_map::get_n_of_lines() {
    return n_of_lines;
}

size_t game_map::get_n_of_cols() {
    return n_of_cols;
}

void game_map::set(Game_object obj, size_t new_xcoord, size_t new_ycoord) {
  field.set(obj,new_xcoord,new_ycoord);
}

Game_object game_map::get(size_t xcoord,size_t ycoord) {
  Game_object cell_status = field.get(xcoord,ycoord);
  return cell_status;
}


character::character (Game_object obj) {
  switch(obj) {
    case PLAYER:
      person = new player();
      break;
  
    case ENEMY:
      person = new npc ();
      break;
  }
  type = obj;

}
character_type *character::get() {
  return person;
}

Game_object character::get_type()
{
  return type;
}
battle::battle(){};
int battle::move(character& person, game_map& map, size_t new_xcoord, size_t new_ycoord) {
  if ((new_xcoord == map.get_n_of_cols()-1) and (new_ycoord == map.get_n_of_lines()-1)) {
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
