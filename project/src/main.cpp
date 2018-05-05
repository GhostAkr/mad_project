#include <SFML/Graphics.hpp>
#include <iostream>
#include "gui.h"

using std::cout;
using std::endl;

int main(/*int argc, const char** argv*/) {
    game_map field_back("data/map");
    gui game(field_back);
    game.run();
	return 0;
}
