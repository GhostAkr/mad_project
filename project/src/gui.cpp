#include <iostream>
#include <SFML/Graphics.hpp>
#include "gui.h"

//GUI METHODS
int gui::run(game_map& field_back) {
    while (window.isOpen()) {
        processEvents();
        update();
        render(field_back);
    }
    return 0;
}

gui::gui(character* pers1, character* pers2)
:window(sf::VideoMode(1024, 768), "MAD")
{
    bgTexture.loadFromFile("images/background.jpg");
    bgSprite.setTexture(bgTexture);
    scrollUp = false;
    scrollDown = false;
    isBegBtn = true;
    isScrollBtn = false;
    isOptions = false;
    isChoosingOptions = false;
    cardsCounter = 0;
    cardsChoosed = 0;
    moveChoosed = 0;
    person1 = pers1;
    person2 = pers2;
}

int gui::handleDirection() {
    while (true) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            while (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {}  //Onle one tap
            return 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            while (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {}  //Onle one tap
            return 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            while (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {}  //Onle one tap
            return 2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            while (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {}  //Onle one tap
            return 3;
        }
    }
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
        if (sf::IntRect(20, 670, 200, 32).contains(sf::Mouse::getPosition(window)) && isBegBtn) {
            cout << "Scroll Up" << endl;
            scrollUp = true;
            isBegBtn = false;
        }
        if (sf::IntRect(120, Scroll.get_y_pos() + 165, 80, 180).contains(sf::Mouse::getPosition(window)) && isScrollBtn) {
            cout << "1 Card" << endl;
            person1->chosen_cards.push_back(person1->avalible_cards[0]);
            cardsCounter++;
            if (cardsCounter == 3) {
                cout << "Scroll down" << endl;
                isScrollBtn = false;
                scrollDown = true;
                cardsCounter = 0;
            }
        }
        if (sf::IntRect(240, Scroll.get_y_pos() + 165, 80, 180).contains(sf::Mouse::getPosition(window)) && isScrollBtn) {
            cout << "2 Card" << endl;
            person1->chosen_cards.push_back(person1->avalible_cards[1]);
            cardsCounter++;
            if (cardsCounter == 3) {
                cout << "Scroll down" << endl;
                isScrollBtn = false;
                scrollDown = true;
                cardsCounter = 0;
            }
        }
        if (sf::IntRect(360, Scroll.get_y_pos() + 165, 80, 180).contains(sf::Mouse::getPosition(window)) && isScrollBtn) {
            cout << "3 Card" << endl;
            person1->chosen_cards.push_back(person1->avalible_cards[2]);
            cardsCounter++;
            if (cardsCounter == 3) {
                cout << "Scroll down" << endl;
                isScrollBtn = false;
                scrollDown = true;
                cardsCounter = 0;
            }
        }
        if (sf::IntRect(480, Scroll.get_y_pos() + 165, 80, 180).contains(sf::Mouse::getPosition(window)) && isScrollBtn) {
            cout << "4 Card" << endl;
            person1->chosen_cards.push_back(person1->avalible_cards[3]);
            cardsCounter++;
            if (cardsCounter == 3) {
                cout << "Scroll down" << endl;
                isScrollBtn = false;
                scrollDown = true;
                cardsCounter = 0;
            }
        }
        if (sf::IntRect(600, Scroll.get_y_pos() + 165, 80, 180).contains(sf::Mouse::getPosition(window)) && isScrollBtn) {
            cout << "5 Card" << endl;
            person1->chosen_cards.push_back(person1->avalible_cards[4]);
            cardsCounter++;
            if (cardsCounter == 3) {
                cout << "Scroll down" << endl;
                isScrollBtn = false;
                scrollDown = true;
                cardsCounter = 0;
            }
        }
        if (sf::IntRect(670, 20, 80, 180).contains(sf::Mouse::getPosition(window)) && isChoosingOptions && cardsChoosed < 3) {
            cout << "Choosed card 1" << endl;
            person1->directions.push_back(handleDirection());
            cout << "Direction: " << person1->directions[person1->directions.size() - 1] << endl;
            person1->chosen_actions.push_back(person1->chosen_cards[0]);
            cardsChoosed++;
            if ((cardsChoosed + moveChoosed) == 6) {
                cout << "End of choice" << endl;
                cardsChoosed = 0;
                moveChoosed = 0;
                isChoosingOptions = false;
                isOptions = false;
            }
        }
        if (sf::IntRect(670, 210, 80, 180).contains(sf::Mouse::getPosition(window)) && isChoosingOptions && cardsChoosed < 3) {
            cout << "Choosed card 2" << endl;
            person1->directions.push_back(handleDirection());
            cout << "Direction: " << person1->directions[person1->directions.size() - 1] << endl;
            person1->chosen_actions.push_back(person1->chosen_cards[1]);
            cardsChoosed++;
            if ((cardsChoosed + moveChoosed) == 6) {
                cardsChoosed = 0;
                moveChoosed = 0;
                isChoosingOptions = false;
                isOptions = false;
            }
        }
        if (sf::IntRect(670, 400, 80, 180).contains(sf::Mouse::getPosition(window)) && isChoosingOptions && cardsChoosed < 3) {
            cout << "Choosed card 3" << endl;
            person1->directions.push_back(handleDirection());
            cout << "Direction: " << person1->directions[person1->directions.size() - 1] << endl;
            person1->chosen_actions.push_back(person1->chosen_cards[2]);
            cardsChoosed++;
            if ((cardsChoosed + moveChoosed) == 6) {
                cardsChoosed = 0;
                moveChoosed = 0;
                isChoosingOptions = false;
                isOptions = false;
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && isChoosingOptions && moveChoosed < 3) {
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {}  // Only one tap
        cout << "Choosed move up" << endl;
        person1->chosen_actions.push_back(UP);
        moveChoosed++;
        if ((cardsChoosed + moveChoosed) == 6) {
            cardsChoosed = 0;
            moveChoosed = 0;
            isChoosingOptions = false;
            isOptions = false;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && isChoosingOptions && moveChoosed < 3) {
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {}  // Only one tap
        cout << "Choosed move right" << endl;
        person1->chosen_actions.push_back(RIGHT);
        moveChoosed++;
        if ((cardsChoosed + moveChoosed) == 6) {
            cardsChoosed = 0;
            moveChoosed = 0;
            isChoosingOptions = false;
            isOptions = false;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && isChoosingOptions && moveChoosed < 3) {
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {}  // Only one tap
        cout << "Choosed move down" << endl;
        person1->chosen_actions.push_back(DOWN);
        moveChoosed++;
        if ((cardsChoosed + moveChoosed) == 6) {
            cardsChoosed = 0;
            moveChoosed = 0;
            isChoosingOptions = false;
            isOptions = false;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && isChoosingOptions && moveChoosed < 3) {
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {}  // Only one tap
        cout << "Choosed move left" << endl;
        person1->chosen_actions.push_back(LEFT);
        moveChoosed++;
        if ((cardsChoosed + moveChoosed) == 6) {
            cardsChoosed = 0;
            moveChoosed = 0;
            isChoosingOptions = false;
            isOptions = false;
        }
    }
    return 0;
}

int gui::update() {
    if (scrollUp) {
        Scroll.set_coords(0, -5 * tick);
        if (Scroll.get_y_pos() < 50) {
            scrollUp = false;
            isScrollBtn = true;
        }
    }
    if (scrollDown) {
        Scroll.set_coords(0, 5 * tick);
        if (Scroll.get_y_pos() > 768) {
            scrollDown = false;
            isOptions = true;
        }
    }
    return 0;
}

int gui::render(game_map& field_back) {
    tick = theclock.getElapsedTime().asMicroseconds();
    theclock.restart();
    tick /= 5000;
    window.clear();
    window.draw(bgSprite);
    battle_map field_front(field_back.get_field());
    field_front.drawCurrent(window);
    dark_mage_draw person1_draw(person1->get_xcoord(), person1->get_ycoord());
    bardess_draw person2_draw(person2->get_xcoord(), person2->get_ycoord());
    person1_draw.drawCurrent(window);
    person2_draw.drawCurrent(window);
    start_turn_button startBTN;
    startBTN.drawCurrent(window);
    Scroll.set_avalible_cards(person1->get_avalible_cards());
    Scroll.drawCurrent(window);
    if (isOptions) {
        actions Actions(person1->chosen_cards);
        Actions.drawCurrent(window, person1);
        isChoosingOptions = true;
    }
    window.display();
    return 0;
}

int gui::set_cardNums (character* person, int num) {
    vector<CardID> cards = person->get_avalible_cards();
    cardNums.push_back(cards[num]);
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
}

int scroll::set_coords(size_t x_delta, size_t y_delta) {
    x_pos += x_delta;
    y_pos += y_delta;
    return 0;
}

int scroll::drawCurrent(sf::RenderTarget& target) {
    scrollSprite.setPosition(x_pos, y_pos);
    target.draw(scrollSprite);
    for (size_t i = 0; i < 5; i++) {
        card* Card = card::create_card(avalible_cards[i]);
        sf::Texture texture;
        texture.loadFromFile(Card->get_shirt_image_path());
        cardTexture.push_back(texture);
    }
    for (size_t i = 0; i < 5; i++) {
        sf::Sprite sprite(cardTexture[i]);
        sprite.setPosition((x_pos + 120) * (i + 1), y_pos + 165);
        target.draw(sprite);
    }
    return 0;
}

size_t scroll::get_y_pos() {
    return y_pos;
}

int scroll::set_avalible_cards(vector <CardID> new_cards) {
    avalible_cards = new_cards;
    return 0;
}

//ACTIONS METHODS

actions::actions(vector<CardID> new_cards) {
    chosen_cards = new_cards;
    for (size_t i = 0; i < 3; i++) {
        if (chosen_cards[i] != VOID) {
            card* Card = card::create_card(chosen_cards[i]);
            sf::Texture texture;
            texture.loadFromFile(Card->get_shirt_image_path());
            cardTexture.push_back(texture);
        }
    }
}

int actions::drawCurrent(sf::RenderTarget& target, character* person1) {
    string choiceString = "";
    for (size_t i = 0; i < person1->chosen_actions.size(); i++) {
        card* Card = card::create_card(person1->chosen_actions[i]);
        string new_action = Card->get_name();
        choiceString += (new_action + "\n");
    }
    sf::Font font;
    font.loadFromFile("data/font.ttf");
    sf::Text choiceText(choiceString, font, 20);
    choiceText.setColor(sf::Color::Black);
    choiceText.setPosition(870, 20);
    sf::Sprite card1Sprite(cardTexture[0]);
    sf::Sprite card2Sprite(cardTexture[1]);
    sf::Sprite card3Sprite(cardTexture[2]);
    card1Sprite.setPosition(670, 20);
    card2Sprite.setPosition(670, 210);
    card3Sprite.setPosition(670, 400);
    target.draw(choiceText);
    target.draw(card1Sprite);
    target.draw(card2Sprite);
    target.draw(card3Sprite);
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
