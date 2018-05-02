#include <iostream>
#include "cards.h"

using std::cout;
using std::endl;

//CARD METHODS

card* card::create_card(CardID name) {
    card* ret;
    switch(name) {
        case FIREBOLT:
            ret = new firebolt();
            break;
        default:
            cout << "Wrong CardID" << endl;
            break;
    }
    return ret;
}

card* card::create_card(CardID name, size_t x_start, size_t y_start) {
    card* ret;
    switch(name) {
        case FIREBOLT:
            ret = new firebolt(x_start, y_start);
            break;
        default:
            cout << "Wrong CardID" << endl;
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

int card::get_cost() {
    return cost;
}

vector<pair<int, int>> card::get_direction_area() {
    return direction_area;
}

void card::drawActionArea(sf::RenderTarget& target, SparseMatrix<Game_object> field, int x, int y) {
    cout << "drawActionArea" << endl;
    choiceTexture.loadFromFile("images/direction.jpg");
    sf::Sprite choiceSprite(choiceTexture);
    for (size_t i = 0; i < direction_area.size(); i++) {
        if (field.get(x + direction_area[i].first + 1, y + direction_area[i].second + 1) == 0) {
            choiceSprite.setPosition((x + direction_area[i].first) * 50, (y + direction_area[i].second) * 50);
        }
        target.draw(choiceSprite);
    }
}

//FIREBOLT METHODS

firebolt::firebolt(size_t x_start, size_t y_start) {
    spell_x = x_start * 50;
    spell_y = y_start * 50;
    xcoord_start = x_start;
    ycoord_start = y_start;
    shirt_image_path = "images/cards/shirts/firebolt.png";
    spell_image_path = "images/cards/spells/firebolt.png";
    previewTexture.loadFromFile("images/cards/spells/firebolt_preview.png");
    spellTexture.loadFromFile(spell_image_path);
    name = "FIREBOLT";
    tag = FIREBOLT;
    dmg = 3;
    cost = 100;
    // Direction area
    direction_area.push_back(pair<int, int> (0, -1));
    direction_area.push_back(pair<int, int> (1, 0));
    direction_area.push_back(pair<int, int> (0, 1));
    direction_area.push_back(pair<int, int> (-1, 0));
}

firebolt::firebolt() {
    shirt_image_path = "images/cards/shirts/firebolt.png";
    tag = FIREBOLT;
    cost = 100;
    name = "FIREBOLT";
}

void firebolt::previewSpell(sf::RenderTarget& target, int xcoord, int ycoord) {
    sf::Sprite previewSprite(previewTexture);
    for (size_t i = 0; i < action_area.size(); i++) {
        previewSprite.setPosition((xcoord + action_area[i].first) * 50, (ycoord + action_area[i].second) * 50);
        target.draw(previewSprite);
    }
}

int firebolt::handleDirection(sf::Window& source, SparseMatrix<Game_object> field, int x, int y) {
    while (true) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {}  //Onle one tap
            if (sf::IntRect(x * 50, (y - 1) * 50, 50, 50).contains(sf::Mouse::getPosition(source)) &&
            field.get(x + 1, (y - 1) + 1) == 0) {  // UP
                return 0;
            }
            if (sf::IntRect((x + 1) * 50, y * 50, 50, 50).contains(sf::Mouse::getPosition(source)) &&
            field.get((x + 1) + 1, y + 1) == 0) {  // RIGHT
                return 1;
            }
            if (sf::IntRect(x * 50, (y + 1) * 50, 50, 50).contains(sf::Mouse::getPosition(source)) &&
            field.get(x + 1, (y + 1) + 1) == 0) {  // DOWN
                return 2;
            }
            if (sf::IntRect((x - 1) * 50, y * 50, 50, 50).contains(sf::Mouse::getPosition(source)) &&
            field.get((x - 1) + 1, y + 1) == 0) {  // LEFT
                return 3;
            }
        }
    }
}

string firebolt::get_shirt_image_path() {
    return shirt_image_path;
}

void firebolt::updateSpell(float tick, bool* isMoveSpell, int side) {
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
    target.draw(spellSprite);
    return 0;
}

void firebolt::set_action_area(int direction) {
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
