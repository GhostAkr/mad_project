#include <iostream>
#include "cards.h"

using std::cout;
using std::endl;

//CARDS METHODS

card* card::create_card(CardID name) {
    card* ret;
    switch(name) {
        case FIREBOLT:
            ret = new firebolt();
            break;
        case UP:
            ret = new up();
            break;
        case RIGHT:
            ret = new right();
            break;
        case DOWN:
            ret = new down();
            break;
        case LEFT:
            ret = new left();
            break;
        default:
            break;
    }
    return ret;
}

card* card::create_card(CardID name, size_t x_start, size_t y_start, int direction) {
    card* ret;
    switch(name) {
        case FIREBOLT:
            ret = new firebolt(x_start, y_start, direction);
            break;
        default:
            break;
    }
    return ret;
}

string card::get_spell_image_path() {
    return spell_image_path;
}

vector<pair<int, int>> card::get_action_area () {
    return action_area;
}

int card::get_dmg() {
    return dmg;
}

string card::get_name() {
    return name;
}

size_t card::get_spell_x() {
    return spell_x;
}

size_t card::get_spell_y() {
    return spell_y;
}

//FIREBOLT METHODS

firebolt::firebolt(size_t x_start, size_t y_start, int direction) {
    spell_x = x_start * 50;
    spell_y = y_start * 50;
    xcoord_start = x_start;
    ycoord_start = y_start;
    shirt_image_path = "images/cards/shirts/firebolt.png";
    spell_image_path = "images/cards/spells/firebolt.png";
    spellTexture.loadFromFile(spell_image_path);
    name = "FIREBOLT";
    tag = FIREBOLT;
    dmg = 3;
    side = direction;
    switch (direction) {
        case 0:  // UP
            for (size_t i = 1; i <= ycoord_start; i++) {
                action_area.push_back(pair<int, int> (0, -i));
            }
            break;
        case 1:  // RIGHT
            for (size_t i = 1; i <= 12 - xcoord_start; i++) {
                action_area.push_back(pair<int, int> (i, 0));
            }
            break;
        case 2:  // DOWN
            for (size_t i = 1; i <= 12 - ycoord_start; i++) {
                action_area.push_back(pair<int, int> (0, i));
            }
            break;
        case 3:  // LEFT
            for (size_t i = 1; i <= xcoord_start; i++) {
                action_area.push_back(pair<int, int> (-i, 0));
            }
            break;
    }
}

firebolt::firebolt() {
    shirt_image_path = "images/cards/shirts/firebolt.png";
    tag = FIREBOLT;
    name = "FIREBOLT";
}

string firebolt::get_shirt_image_path() {
    return shirt_image_path;
}

void firebolt::updateSpell(float tick, bool* isMoveSpell) {
    switch (side) {
        case 0:
            if (spell_y < 50) {
                *isMoveSpell = false;
            }
            spell_y -= 1 * tick;
            break;
        case 1:
            if (spell_x > 600) {
                *isMoveSpell = false;
            }
            spell_x += 1 * tick;
            break;
        case 2:
            if (spell_y > 600) {
                *isMoveSpell = false;
            }
            spell_y += 1 * tick;
            break;
        case 3:
            if (spell_x < 50) {
                *isMoveSpell = false;
            }
            spell_x -= 1 * tick;
            break;
    }
}

int firebolt::drawCurrent(sf::RenderTarget& target) {
    sf::Sprite spellSprite(spellTexture);
    spellSprite.setPosition(spell_x, spell_y);
    //spellSprite.setPosition(500, 500);
    target.draw(spellSprite);
    //while (true) {}
    return 0;
}

//UP METHODS

up::up() {
    tag = UP;
    name = "UP";
}


void up::updateSpell(float tick, bool* isMoveSpell) {
    boolDummy = *isMoveSpell;
    tickDummy = tick;
}

int up::drawCurrent(sf::RenderTarget& target) {
    targetDummy = &target;
    return 0;
}


string up::get_shirt_image_path() {
    return "";
}

//RIGHT METHODS

right::right() {
    tag = RIGHT;
    name = "RIGHT";
}

void right::updateSpell(float tick, bool* isMoveSpell) {
    boolDummy = *isMoveSpell;
    tickDummy = tick;
}

int right::drawCurrent(sf::RenderTarget& target) {
    targetDummy = &target;
    return 0;
}

string right::get_shirt_image_path() {
    return "";
}

//DOWN METHODS

down::down() {
    tag = DOWN;
    name = "DOWN";
}

void down::updateSpell(float tick, bool* isMoveSpell) {
    boolDummy = *isMoveSpell;
    tickDummy = tick;
}

int down::drawCurrent(sf::RenderTarget& target) {
    targetDummy = &target;
    return 0;
}

string down::get_shirt_image_path() {
    return "";
}

//LEFT MRTHODS

left::left() {
    tag = LEFT;
    name = "LEFT";
}

void left::updateSpell(float tick, bool* isMoveSpell) {
    boolDummy = *isMoveSpell;
    tickDummy = tick;
}

int left::drawCurrent(sf::RenderTarget& target) {
    targetDummy = &target;
    return 0;
}

string left::get_shirt_image_path() {
    return "";
}
