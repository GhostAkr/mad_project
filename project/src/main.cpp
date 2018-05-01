#include <SFML/Graphics.hpp>
#include <iostream>
#include "gui.h"

using std::cout;
using std::endl;

int main(/*int argc, const char** argv*/) {
    game_map field_back("data/map");
    //NEED IMPROVEMENT
    character* person1 = character::create_character(PLAYER, DARKMAGE);
    character* person2 = character::create_character(ENEMY, DARKMAGE);
    //NEED IMPROVEMENT
    person1->create_avalible_cards();
    person2->create_avalible_cards();
    gui game(person1 , person2, field_back);
    game.run();
    delete person1;
    delete person2;
	return 0;
}
