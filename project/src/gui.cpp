#include <iostream>
#include <SFML/Graphics.hpp>
#include "gui.h"

//GUI METHODS

int gui::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
    return 0;
}

gui::gui()
:window(sf::VideoMode(1024, 768), "MAD")
{
    bgTexture.loadFromFile("images/background.jpg");
    bgSprite.setTexture(bgTexture);
    scrollUp = false;
}

int gui::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {}  // Getting only one tap
        if (sf::IntRect(20, 670, 200, 32).contains(sf::Mouse::getPosition(window))) {
            cout << "Scroll Up" << endl;
            scrollUp = true;
        }
    }
    return 0;
}

int gui::update() {
    if (scrollUp) {
        Scroll.set_coords(0, -2 * tick);
        if (Scroll.get_y_pos() < 50) {
            scrollUp = false;
        }
    }
    return 0;
}

int gui::render() {
    tick = theclock.getElapsedTime().asMicroseconds();
    theclock.restart();
    tick /= 1000;
    window.clear();
    window.draw(bgSprite);
    game_map field_back("data/map");
    battle_map field_front(field_back.get_field());
    field_front.drawCurrent(window);
    // NEED IMPROVEMENT
    player Player("data/player");
    dark_mage_draw person1(Player.get_xcoord(), Player.get_ycoord());
    npc NPC("data/npc");
    bardess_draw person2(NPC.get_xcoord(), NPC.get_ycoord());
    // NEED IMPROVEMENT
    person1.drawCurrent(window);
    person2.drawCurrent(window);
    start_turn_button startBTN;
    startBTN.drawCurrent(window);
    Scroll.drawCurrent(window);
    window.display();
    return 0;
}

// MAP METHODS

battle_map::battle_map(SparseMatrix <Game_object> src_field) {
    map_height = 13;
    map_width = 13;
    field = src_field;
    wallTexture.loadFromFile("images/wall.png");
    cellTexture.loadFromFile("images/empty_cell.png");
    this->set_mapSprite();
}

int battle_map::set_mapSprite() {
    sf::Sprite sprite;
    for (size_t i = 1; i <= map_height; i++) {
        vector <sf::Sprite> temp;
        for (size_t j = 1; j <= map_width; j++) {
            switch (field.get(i, j)) {
                case WALL:
                    sprite.setTexture(wallTexture);
                    break;
                default:
                    sprite.setTexture(cellTexture);
                    break;
            }
            temp.push_back(sprite);
        }
        mapSprite.push_back(temp);
    }
    return 0;
}

size_t battle_map::get_map_height() {
    return map_height;
}

size_t battle_map::get_map_width() {
    return map_width;
}

sf::Sprite battle_map::get_mapTile(size_t row, size_t col) {
    sf::Sprite sprite = mapSprite[row][col];
    return sprite;
}

int battle_map::drawCurrent(sf::RenderTarget& target) {
    for (size_t i = 0; i < map_height; i++) {
        for (size_t j = 0; j < map_width; j++) {
            mapSprite[i][j].setPosition(i * 50, j * 50);
            target.draw(mapSprite[i][j]);
        }
    }
    return 0;
}

// BUTTON METHODS

start_turn_button::start_turn_button() {
    buttonTexture.loadFromFile("images/buttons/begin_button.png");
    buttonSprite.setTexture(buttonTexture);
    x_pos = 20;
    y_pos = 670;
}

int start_turn_button::drawCurrent(sf::RenderTarget& target) {
    buttonSprite.setPosition(x_pos, y_pos);
    target.draw(buttonSprite);
    return 0;
}

// SCROLL METHODS

scroll::scroll() {
    scrollTexture.loadFromFile("images/scroll.png");
    scrollSprite.setTexture(scrollTexture);
    x_pos = 0;
    y_pos = 1030;
    /*
    for (size_t i = 0; i < 5; i++) {
        card* Card = card::create_card(avalible_cards[i]);
        sf::Texture texture;
        texture.loadFromFile(Card->get_shirt_image_path());
        cardTexture.push_back(texture);
    }
    */
}

int scroll::set_coords(size_t x_delta, size_t y_delta) {
    x_pos += x_delta;
    y_pos += y_delta;
    return 0;
}

int scroll::drawCurrent(sf::RenderTarget& target) {
    scrollSprite.setPosition(x_pos, y_pos);
    target.draw(scrollSprite);
    /*
    for (size_t i = 0; i < 5; i++) {
        sf::Sprite sprite(cardTexture[i]);
        sprite.setPosition((x_pos + 100) * i, y_pos + 100);
        target.draw(sprite);
    }
    */
    return 0;
}

size_t scroll::get_y_pos() {
    return y_pos;
}

int scroll::set_avalible_cards(vector <CardID> new_cards) {
    avalible_cards = new_cards;
    return 0;
}

// DARK MAGE METHODS

dark_mage_draw::dark_mage_draw(size_t x_coord, size_t y_coord) {
    creatureTexture.loadFromFile("images/creatures/mage.png");
    creatureSprite.setTexture(creatureTexture);
    x_pos = x_coord;
    y_pos = y_coord;
}

int dark_mage_draw::drawCurrent(sf::RenderTarget& target) {
    creatureSprite.setPosition(x_pos * 50, y_pos * 50);
    target.draw(creatureSprite);
    return 0;
}

// BARDESS METHODS

bardess_draw::bardess_draw(size_t x_coord, size_t y_coord) {
    creatureTexture.loadFromFile("images/creatures/timmy.png");
    creatureSprite.setTexture(creatureTexture);
    x_pos = x_coord;
    y_pos = y_coord;
}

int bardess_draw::drawCurrent(sf::RenderTarget& target) {
    creatureSprite.setPosition(x_pos * 50, y_pos * 50);
    target.draw(creatureSprite);
    return 0;
}

/*
vector<int> planning::get_chosen_actions() {
    return chosen_actions;
}

draw_map::draw_map(game_map& map_object) {
    map_height = map_object.get_n_of_lines();
    map_width = map_object.get_n_of_cols();
    TileMap = map_object.get_field();

}

int draw_map::drawing(sf::RenderWindow& win) {
    sf::Image map_image;
	map_image.loadFromFile("images/empty_cell.png");
	sf::Texture map_texture;
	map_texture.loadFromImage(map_image);
	sf::Sprite s_map;
	s_map.setTexture(map_texture);
    for (int i = 0; i < map_height; i++) {
        for (int j = 0; j < map_width; j++) {
            s_map.setTextureRect(sf::IntRect(0, 0, 50, 50));
            s_map.setPosition(j * 50, i * 50);
            win.draw(s_map);
        }
    }
    return 0;
}

buttons::buttons(int xc, int yc, string path) {
    xcoord = xc;
    ycoord = yc;
    image_path = path;
}

int buttons::draw_button(sf::RenderWindow& window) {
    Texture buttonTexture;
    buttonTexture.loadFromFile(image_path);
    Sprite buttonSprite(buttonTexture);
    buttonSprite.setPosition(xcoord, ycoord);
    window.draw(buttonSprite);
    return 0;
}
action_window::action_window(sf::RenderWindow& window, game_map& field) {
    draw_map field_draw(field);
    field_draw.drawing(window);
    buttons beginButton(10, 530, "images/buttons/begin_button.png");
    beginButton.draw_button(window);
    buttons endButton(230, 530, "images/buttons/end_button.png");
    endButton.draw_button(window);
}

Action_Button action_window::get_button(sf::RenderWindow& window) {
    if (Mouse::isButtonPressed(Mouse::Left)) {
        while (true) {
            if (!Mouse::isButtonPressed(Mouse::Left)) {
                break;
            }
        }
        if (IntRect(10, 530, 200, 32).contains(Mouse::getPosition(window))) {
            return BEGBTN;
        }
        if (IntRect(230, 530, 200, 32).contains(Mouse::getPosition(window))) {
            return ENDBTN;
        }
    }
    return VOID;
}

int planning::draw_scroll(sf::RenderWindow& window, size_t ycoord) {
    Texture scrollTexture;
    scrollTexture.loadFromFile("images/scroll.png");
    Sprite scrollSprite(scrollTexture);
    scrollSprite.setPosition(0, ycoord);
    window.draw(scrollSprite);
    return 0;
}
*/
