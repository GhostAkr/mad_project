#include <SFML/Graphics.hpp>
#include <iostream>
//#include "game.h"
#include "gui.h"

using namespace sf;
using std::cout;
using std::endl;

int main(/*int argc, const char** argv*/) {
    game_map field_back("data/map");
    //NEED IMPROVEMENT
    character* person1 = character::create_character(PLAYER);
    character* person2 = character::create_character(ENEMY);
    //NEED IMPROVEMENT
    person1->create_avalible_cards();
    person2->create_avalible_cards();
    gui game(person1 , person2);
    game.run(field_back);
    delete person1;
    delete person2;
	return 0;
}
