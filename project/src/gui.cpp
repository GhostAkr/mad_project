#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "gui.h"

//GUI METHODS
int gui::run(game_map& field_back) {
    while (window.isOpen()) {
        tick = theclock.getElapsedTime().asMicroseconds();
        theclock.restart();
        tick /= 5000;
        processEvents();
        update();
        render(field_back);
        sf::sleep(sf::microseconds(1));
    }
    return 0;
}

gui::gui(character* pers1, character* pers2)
:window(sf::VideoMode(1024, 768), "MAD")
{
    //window.setFramerateLimit(60);
    creature1 = creature::create_creature(pers1->cr_type, pers1->get_xcoord(), pers1->get_ycoord());
    creature2 = creature::create_creature(pers2->cr_type, pers2->get_xcoord(), pers2->get_ycoord());
    bgTexture.loadFromFile("images/background.jpg");
    bgSprite.setTexture(bgTexture);
    //passedTime = 0;
    Card = NULL;
    scrollUp = false;
    scrollDown = false;
    isBegBtn = true;
    isScrollBtn = false;
    isOptions = false;
    isChoosingOptions = false;
    isPlay = false;
    isMoveAnim1 = false;
    isMoveAnim2 = false;
    isBattle = false;
    isDrawSpell1 = false;
    isMoveSpell1 = false;
    isNPCPlay = false;
    isNPC = false;
    cardsCounter = 0;
    cardsChoosed = 0;
    moveChoosed = 0;
    step = 0;
    stepDirection1 = 0;
    stepDirection2 = 0;
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
                isPlay = true;
                isBattle = true;
                isNPCPlay = true;
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
                isPlay = true;
                isBattle = true;
                isNPCPlay = true;
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
                isPlay = true;
                isBattle = true;
                isNPCPlay = true;
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
            isPlay = true;
            isBattle = true;
            isNPCPlay = true;
        }
        cout << "Test" << endl;
        cout << person1->chosen_actions.size() << endl;
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
            isPlay = true;
            isBattle = true;
            isNPCPlay = true;
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
            isPlay = true;
            isBattle = true;
            isNPCPlay = true;
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
            isPlay = true;
            isBattle = true;
            isNPCPlay = true;
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
    if (isMoveAnim1) {
        if (creature1->updateCurrent(person1, tick) == 1) {  // Stop animation
            isMoveAnim1 = false;
        }
    }
    if (isMoveAnim2) {
        if (creature2->updateCurrent(person2, tick) == 1) {  // Stop animation
            isMoveAnim2 = false;
        }
    }
    if (isMoveSpell1) {
        Card->updateSpell(tick, &isMoveSpell1);
        if (!isMoveSpell1) {
            isDrawSpell1 = false;
        }
    }
    return 0;
}

void gui::play(battle& fight, game_map& field_back) {
    if (step < 6 && !isMoveAnim1 && !isMoveAnim2) {
        //cout << "Play action" << endl;
        switch (person1->chosen_actions[step]) {
            case UP:
                fight.move(person1, field_back, person1->get_xcoord(), person1->get_ycoord() - 1);
                isMoveAnim1 = true;
                break;
            case RIGHT:
                fight.move(person1, field_back, person1->get_xcoord() + 1, person1->get_ycoord());
                isMoveAnim1 = true;
                break;
            case DOWN:
                fight.move(person1, field_back, person1->get_xcoord(), person1->get_ycoord() + 1);
                isMoveAnim1 = true;
                break;
            case LEFT:
                fight.move(person1, field_back, person1->get_xcoord() - 1, person1->get_ycoord());
                isMoveAnim1 = true;
                break;
            default:
                /*
                Card = card::create_card(person1->chosen_actions[step1], person1->get_xcoord(), person1->get_ycoord(), person1->directions[stepDirection1]);
                fight.play_card(person1->chosen_actions[step1], person1->get_xcoord(), person1->get_ycoord(), person1->directions[stepDirection1], person1, person2);
                isDrawSpell1 = true;
                isMoveSpell1 = true;
                isNPC = true;
                step1++;
                stepDirection1++;
                */
                //cout << "Player hit" << endl;
                break;
        }
        switch (person2->chosen_actions[step]) {
            case UP:
                fight.move(person2, field_back, person2->get_xcoord(), person2->get_ycoord() - 1);
                isMoveAnim2 = true;
                break;
            case RIGHT:
                fight.move(person2, field_back, person2->get_xcoord() + 1, person2->get_ycoord());
                isMoveAnim2 = true;
                break;
            case DOWN:
                fight.move(person2, field_back, person2->get_xcoord(), person2->get_ycoord() + 1);
                isMoveAnim2 = true;
                break;
            case LEFT:
                fight.move(person2, field_back, person2->get_xcoord() - 1, person2->get_ycoord());
                isMoveAnim2 = true;
                break;
            default:
            /*
                Card = card::create_card(person2->chosen_actions[step2], person2->get_xcoord(), person2->get_ycoord(), person2->directions[stepDirection2]);
                fight.play_card(person2->chosen_actions[step2], person2->get_xcoord(), person2->get_ycoord(), person2->directions[stepDirection2], person1, person2);
                isDrawSpell1 = true;
                isMoveSpell1 = true;
                isNPC = false;
                step2++;
                stepDirection2++;
                */
                //cout << "NPC hit" << endl;
                break;
        }
        step++;
    }
}

int gui::render(game_map& field_back) {
    window.clear();
    window.draw(bgSprite);
    battle_map field_front(field_back.get_field());
    field_front.drawCurrent(window);
    //NEED IMPROVEMENT (Stats info)
    stringstream hp1, hp2;
    string hp1Str;
    string hp2Str;
    hp1 << person1->get_hp();
    hp2 << person2->get_hp();
    hp1 >> hp1Str;
    hp2 >> hp2Str;
    string stat = "Your HP: " + hp1Str + "\nEnemy HP: " + hp2Str;
    sf::Font font;
    font.loadFromFile("data/font.ttf");
    sf::Text choiceText(stat, font, 20);
    choiceText.setColor(sf::Color::Black);
    choiceText.setPosition(840, 650);
    window.draw(choiceText);
    //NEED IMPROVEMENT
    creature1->drawCurrent(window);
    creature2->drawCurrent(window);
    start_turn_button startBTN;
    startBTN.drawCurrent(window);
    Scroll.set_avalible_cards(person1->get_avalible_cards());
    Scroll.drawCurrent(window);
    if (isOptions) {
        actions Actions(person1->chosen_cards);
        Actions.drawCurrent(window, person1);
        isChoosingOptions = true;
    }
    //cout << "End" << endl;
    if (isNPCPlay) {
        person2->play_dark_mage(person1);
        isNPCPlay = false;
    }
    battle fight;
    if (isPlay) {
        this->play(fight, field_back);
        //if (!isMoveAnim1 && !isMoveAnim2 && step1 < 6 && !isDrawSpell1 && !isDrawSpell2 && !isNPC) {

            //cout << "Player hp: " << person1->get_hp() << "; NPC hp: " << person2->get_hp() << endl;
        //}
        //if (!isMoveAnim1 && !isMoveAnim2 && step2 < 6 && !isDrawSpell1 && !isDrawSpell2 && isNPC) {

            //cout << "Player hp: " << person1->get_hp() << "; NPC hp: " << person2->get_hp() << endl;
        //}
    }
    if (isDrawSpell1 && !isMoveAnim1 && !isMoveAnim2) {
        Card->drawCurrent(window);
    }
    if (step == 6 && !isMoveAnim1 && !isMoveAnim2) {
        cout << "Exit" << endl;
        isBegBtn = true;
        person1->chosen_cards.clear();
        person1->chosen_actions.clear();
        person1->directions.clear();
        person2->chosen_cards.clear();
        person2->chosen_actions.clear();
        person2->directions.clear();
        Card = NULL;
        scrollUp = false;
        scrollDown = false;
        isBegBtn = true;
        isScrollBtn = false;
        isOptions = false;
        isChoosingOptions = false;
        isPlay = false;
        isMoveAnim1 = false;
        isMoveAnim2 = false;
        isBattle = false;
        isDrawSpell1 = false;
        isMoveSpell1 = false;
        isNPCPlay = false;
        isNPC = false;
        cardsCounter = 0;
        cardsChoosed = 0;
        moveChoosed = 0;
        step = 0;
        stepDirection1 = 0;
        stepDirection2 = 0;
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

int scroll::set_coords(int x_delta, int y_delta) {
    x_pos += x_delta;
    y_pos += y_delta;
    x_pos = abs(x_pos);
    y_pos = abs(y_pos);
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
        switch (person1->chosen_actions[i]) {
            case UP:
                choiceString += "UP\n";
                break;
            case RIGHT:
                choiceString += "RIGHT\n";
                break;
            case DOWN:
                choiceString += "DOWN\n";
                break;
            case LEFT:
                choiceString += "LEFT\n";
                break;
            default:
                card* Card = card::create_card(person1->chosen_actions[i]);
                string new_action = Card->get_name();
                choiceString += (new_action + "\n");
                break;
        }
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

// CREATURE METHODS

creature* creature::create_creature(creature_type new_type, size_t xcoord, size_t ycoord) {
    creature* ret;
    switch (new_type) {
        case DARKMAGE:
            ret = new dark_mage_draw(xcoord, ycoord);
            break;
        case BARDESS:
            ret = new bardess_draw(xcoord, ycoord);
            break;
        default:
            break;
    }
    return ret;
}

int creature::updateCurrent(character* person, float tick) {
    int dst_x = person->get_xcoord() * 50;
    int dst_y = person->get_ycoord() * 50;
    int eps = 5;  //Stop animation in this area
    float speed = 2.5;
    if (abs(x_pos - dst_x) < eps && abs(y_pos - dst_y) < eps) {  //Stop animation conditions
        return 1;
    }
    if (abs(dst_x - x_pos) != 0) {
        x_pos += (dst_x - x_pos) / abs(dst_x - x_pos) / speed * tick;
    }
    if (abs(dst_y - y_pos) != 0) {
        y_pos += (dst_y - y_pos) / abs(dst_y - y_pos) / speed * tick;
    }
    return 0;
}

// DARK MAGE METHODS

dark_mage_draw::dark_mage_draw(size_t x_coord, size_t y_coord) {
    creatureTexture.loadFromFile("images/creatures/mage.png");
    creatureSprite.setTexture(creatureTexture);
    x_pos = x_coord * 50;
    y_pos = y_coord * 50;
}

int dark_mage_draw::drawCurrent(sf::RenderTarget& target) {
    creatureSprite.setPosition(x_pos, y_pos);
    target.draw(creatureSprite);
    return 0;
}

// BARDESS METHODS

bardess_draw::bardess_draw(size_t x_coord, size_t y_coord) {
    creatureTexture.loadFromFile("images/creatures/timmy.png");
    creatureSprite.setTexture(creatureTexture);
    x_pos = x_coord * 50;
    y_pos = y_coord * 50;
}

int bardess_draw::drawCurrent(sf::RenderTarget& target) {
    creatureSprite.setPosition(x_pos, y_pos);
    target.draw(creatureSprite);
    return 0;
}
