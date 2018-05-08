#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "gui.h"

//GUI METHODS

int gui::get_xpreivew() {
    return preview_coords.back().first;
}

int gui::get_ypreview() {
    return preview_coords.back().second;
}

int gui::run() {
    window.setVerticalSyncEnabled(true);
    sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
    sf::Clock theclock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (window.isOpen()) {
        processEvents();
        timeSinceLastUpdate += theclock.restart();
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render(field_back);
    }
    return 0;
}

void gui::set_start_vals() {
    cout << "Start vals" << endl;
    bgTexture.loadFromFile("images/background.jpg");
    bgSprite.setTexture(bgTexture);
    person1 = character::create_character(PLAYER, DARKMAGE);
    person2 = character::create_character(ENEMY, DARKMAGE);
    person1->create_avalible_cards();
    person2->create_avalible_cards();
    creature1 = creature::create_creature(person1->cr_type, person1->get_xcoord(), person1->get_ycoord());
    creature2 = creature::create_creature(person2->cr_type, person2->get_xcoord(), person2->get_ycoord());
    isShopBtn = true;
    isShop = false;
    isApplyBtn = false;
    isShopCardsBtn = false;
    isDeckBtn = true;
    isDeck = false;
    isMainMenu = true;
    isActionWindow = false;
    isPlayBtn = true;
    PlayingCard1 = NULL;
    PlayingCard2 = NULL;
    scrollUp = false;
    scrollDown = false;
    isBegBtn = false;
    isMenuBtn = false;
    isScrollBtn = false;
    isOptions = false;
    isChoosingOptions = false;
    isPlay = false;
    isMoveAnim1 = false;
    isMoveAnim2 = false;
    isBattle = false;
    isDrawSpell1 = false;
    isMoveSpell1 = false;
    isDrawSpell2 = false;
    isMoveSpell2 = false;
    isNPCPlay = false;
    isCancelBtn = false;
    isDrawDirection = false;
    isChooseDirection = false;
    isPreview = false;
    cardsCounter = 0;
    cardsChoosed = 0;
    moveChoosed = 0;
    step = 0;
    stepDirection1 = 0;
    stepDirection2 = 0;
    preview_coords.push_back(pair<int, int> (person1->get_xcoord(), person1->get_ycoord()));
}

void gui::new_turn_vals() {
    person1->chosen_cards.clear();
    person1->chosen_actions.clear();
    person1->directions.clear();
    person2->chosen_cards.clear();
    person2->chosen_actions.clear();
    person2->directions.clear();
    preview_coords.push_back(pair<int, int> (person1->get_xcoord(), person1->get_ycoord()));
    creature1->startPoints.clear();
    cardsStartPoints.clear();
    PlayingCard1 = NULL;
    PlayingCard2 = NULL;
    scrollUp = false;
    scrollDown = false;
    isBegBtn = true;
    isMenuBtn = true;
    isScrollBtn = false;
    isOptions = false;
    isChoosingOptions = false;
    isPlay = false;
    isMoveAnim1 = false;
    isMoveAnim2 = false;
    isBattle = false;
    isDrawSpell1 = false;
    isMoveSpell1 = false;
    isDrawSpell2 = false;
    isMoveSpell2 = false;
    isNPCPlay = false;
    isCancelBtn = false;
    isDrawDirection = false;
    isChooseDirection = false;
    isPreview = false;
    cardsCounter = 0;
    cardsChoosed = 0;
    moveChoosed = 0;
    step = 0;
    stepDirection1 = 0;
    stepDirection2 = 0;
}

gui::~gui() {

}

gui::gui(game_map& field)
:window(sf::VideoMode(1024, 768), "MAD"),
field_back(field)
{
    set_start_vals();
}

void gui::preview(vector<CardID> chosen_actions) {
    for (size_t i = 0; i < chosen_actions.size(); i++) {
        switch (chosen_actions[i]) {
            case UP:
                creature1->drawPreview(window);
                break;
            case RIGHT:
                creature1->drawPreview(window);
                break;
            case DOWN:
                creature1->drawPreview(window);
                break;
            case LEFT:
                creature1->drawPreview(window);
                break;
            default:
                for (size_t j = 0; j < cardsStartPoints.size(); j++) {
                    card* CurCard = card::create_card(chosen_actions[i], cardsStartPoints[j].first, cardsStartPoints[j].second);
                    CurCard->set_action_area(person1->directions[j]);
                    CurCard->previewSpell(window, cardsStartPoints[j].first, cardsStartPoints[j].second);
                    delete CurCard;
                }
                break;
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
    if (isChooseDirection) {
        card* CurCard = card::create_card(person1->chosen_cards[cardsChoosed - 1], preview_coords.back().first, preview_coords.back().second);
        person1->directions.push_back(CurCard->handleDirection(window, field_back.get_field(), preview_coords.back().first, preview_coords.back().second));
        cardsStartPoints.push_back(pair<int, int> (preview_coords.back().first, preview_coords.back().second));
        if ((cardsChoosed + moveChoosed) == 6) {
            isPreview = false;
            isPlay = true;
        }
        isChooseDirection = false;
        isDrawDirection = false;
        delete CurCard;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {}  // Getting only one tap
        if (isShopCardsBtn) {
            for (size_t i = 0; i < shopSprites.size(); i++) {
                if (sf::IntRect(shopSprites[i].getPosition().x, shopSprites[i].getPosition().y, 80, 180).contains(sf::Mouse::getPosition(window))) {
                    card* CurCard = card::create_card(shopCards[i]);
                    if (person1->money >= CurCard->get_cost()) {
                        person1->deck.push_back(shopCards[i]);
                        person1->money -= CurCard->get_cost();
                    }
                    delete CurCard;
                }
            }
        }
        if (sf::IntRect(412, 438, 200, 32).contains(sf::Mouse::getPosition(window)) && isDeckBtn) {
            isDeck = true;
            isShopBtn = false;
            isMainMenu = false;
            isApplyBtn = true;
            isShopCardsBtn = true;
            isPlayBtn = false;
            isDeckBtn = false;

        }
        if (sf::IntRect(20, 730, 200, 32).contains(sf::Mouse::getPosition(window)) && isApplyBtn) {
            isShop = false;
            isMainMenu = true;
            isApplyBtn = false;
            isShopBtn = true;
            isShopCardsBtn = false;
            isPlayBtn = true;
            isDeck = false;
            isDeckBtn = true;
        }
        if (sf::IntRect(412, 386, 200, 32).contains(sf::Mouse::getPosition(window)) && isShopBtn) {
            isShopBtn = false;
            isShop = true;
            isMainMenu = false;
            isApplyBtn = true;
            isShopCardsBtn = true;
            isPlayBtn = false;
            isDeckBtn = false;
        }
        if (sf::IntRect(480, 670, 200, 32).contains(sf::Mouse::getPosition(window)) && isMenuBtn) {
            set_start_vals();
            isActionWindow = false;
            isMainMenu = true;
        }
        if (sf::IntRect(250, 670, 200, 32).contains(sf::Mouse::getPosition(window)) && isCancelBtn) {
            cout << "Cancel" << endl;
            switch (person1->chosen_actions.back()) {
                case UP:
                    creature1->startPoints.pop_back();
                    person1->chosen_actions.pop_back();
                    preview_coords.pop_back();
                    moveChoosed--;
                    break;
                case RIGHT:
                    creature1->startPoints.pop_back();
                    person1->chosen_actions.pop_back();
                    preview_coords.pop_back();
                    moveChoosed--;
                    break;
                case DOWN:
                    creature1->startPoints.pop_back();
                    person1->chosen_actions.pop_back();
                    preview_coords.pop_back();
                    moveChoosed--;
                    break;
                case LEFT:
                    creature1->startPoints.pop_back();
                    person1->chosen_actions.pop_back();
                    preview_coords.pop_back();
                    moveChoosed--;
                    break;
                default:
                    cardsStartPoints.pop_back();
                    person1->chosen_actions.pop_back();
                    person1->directions.pop_back();
                    //preview_coords.pop_back();
                    cardsChoosed--;
                    break;
            }
            if (person1->chosen_actions.size() == 0) {
                isCancelBtn = false;
            }
        }
        if (sf::IntRect(412, 334, 200, 32).contains(sf::Mouse::getPosition(window)) && isPlayBtn) {
            cout << "Let's Play!" << endl;
            set_start_vals();
            isActionWindow = true;
            isMainMenu = false;
            isBegBtn = true;
            isMenuBtn = true;
            isDeckBtn = false;
        }
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
            isPreview = true;
            isDrawDirection = true;
            isCancelBtn = true;
            person1->chosen_actions.push_back(person1->chosen_cards[0]);
            cardsChoosed++;
            if ((cardsChoosed + moveChoosed) == 6) {
                cout << "End of choice" << endl;
                isChoosingOptions = false;
                isOptions = false;
                isBattle = true;
                isNPCPlay = true;
            }
        }
        if (sf::IntRect(670, 210, 80, 180).contains(sf::Mouse::getPosition(window)) && isChoosingOptions && cardsChoosed < 3) {
            cout << "Choosed card 2" << endl;
            isPreview = true;
            isDrawDirection = true;
            isCancelBtn = true;
            person1->chosen_actions.push_back(person1->chosen_cards[1]);
            cardsChoosed++;
            if ((cardsChoosed + moveChoosed) == 6) {
                isChoosingOptions = false;
                isOptions = false;
                isBattle = true;
                isNPCPlay = true;
            }
        }
        if (sf::IntRect(670, 400, 80, 180).contains(sf::Mouse::getPosition(window)) && isChoosingOptions && cardsChoosed < 3) {
            cout << "Choosed card 3" << endl;
            isPreview = true;
            isDrawDirection = true;
            isCancelBtn = true;
            person1->chosen_actions.push_back(person1->chosen_cards[2]);
            cardsChoosed++;
            cout << cardsChoosed << endl;
            if ((cardsChoosed + moveChoosed) == 6) {
                isChoosingOptions = false;
                isOptions = false;
                isBattle = true;
                isNPCPlay = true;
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && isChoosingOptions && moveChoosed < 3) {
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {}  // Only one tap
        cout << "Choosed move up" << endl;
        int new_x = preview_coords.back().first;
        int new_y = preview_coords.back().second - 1;
        preview_coords.push_back(pair<int, int> (new_x, new_y));
        cout << "X = " << preview_coords.back().first << endl;
        cout << "Y = " << preview_coords.back().second << endl;
        creature1->startPoints.push_back(pair<int, int> (preview_coords.back().first, preview_coords.back().second));
        isPreview = true;
        isCancelBtn = true;
        person1->chosen_actions.push_back(UP);
        moveChoosed++;
        if ((cardsChoosed + moveChoosed) == 6) {
            isPreview = false;
            isChoosingOptions = false;
            isOptions = false;
            isPlay = true;
            isBattle = true;
            isNPCPlay = true;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && isChoosingOptions && moveChoosed < 3) {
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {}  // Only one tap
        cout << "Choosed move right" << endl;
        int new_x = preview_coords.back().first + 1;
        int new_y = preview_coords.back().second;
        preview_coords.push_back(pair<int, int> (new_x, new_y));
        creature1->startPoints.push_back(pair<int, int> (preview_coords.back().first, preview_coords.back().second));
        isPreview = true;
        isCancelBtn = true;
        person1->chosen_actions.push_back(RIGHT);
        moveChoosed++;
        if ((cardsChoosed + moveChoosed) == 6) {
            isPreview = false;
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
        int new_x = preview_coords.back().first;
        int new_y = preview_coords.back().second + 1;
        preview_coords.push_back(pair<int, int> (new_x, new_y));
        creature1->startPoints.push_back(pair<int, int> (preview_coords.back().first, preview_coords.back().second));
        isPreview = true;
        isCancelBtn = true;
        person1->chosen_actions.push_back(DOWN);
        moveChoosed++;
        if ((cardsChoosed + moveChoosed) == 6) {
            isPreview = false;
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
        int new_x = preview_coords.back().first - 1;
        int new_y = preview_coords.back().second;
        preview_coords.push_back(pair<int, int> (new_x, new_y));
        creature1->startPoints.push_back(pair<int, int> (preview_coords.back().first, preview_coords.back().second));
        isPreview = true;
        isCancelBtn = true;
        person1->chosen_actions.push_back(LEFT);
        moveChoosed++;
        if ((cardsChoosed + moveChoosed) == 6) {
            isPreview = false;
            isChoosingOptions = false;
            isOptions = false;
            isPlay = true;
            isBattle = true;
            isNPCPlay = true;
        }
    }
    return 0;
}

int gui::update(sf::Time tick) {
    sf::Vector2f movementScrollUp(0.f, 0.f);
    float ScrollSpeed = 0.0005;
    if (scrollUp) {
        movementScrollUp.y -= ScrollSpeed;
        Scroll.set_coords(0, movementScrollUp.y * tick.asMicroseconds());
        if (Scroll.get_y_pos() < 50) {
            scrollUp = false;
            isScrollBtn = true;
        }
    }
    sf::Vector2f movementScrollDown(0.f, 0.f);
    if (scrollDown) {
        movementScrollDown.y += ScrollSpeed;
        Scroll.set_coords(0, movementScrollDown.y * tick.asMicroseconds());
        if (Scroll.get_y_pos() > 768) {
            scrollDown = false;
            isOptions = true;
        }
    }
    float moveSpeed = 0.00005;
    if (isMoveAnim1) {
        if (creature1->updateCurrent(person1, moveSpeed * tick.asMicroseconds()) == 1) {  // Stop animation
            isMoveAnim1 = false;
        }
    }
    if (isMoveAnim2) {
        if (creature2->updateCurrent(person2, moveSpeed * tick.asMicroseconds()) == 1) {  // Stop animation
            isMoveAnim2 = false;
        }
    }
    float spellSpeed = 0.0002;
    if (isMoveSpell1) {
        PlayingCard1->updateSpell(spellSpeed * tick.asMicroseconds(), &isMoveSpell1, person1->directions[stepDirection1 - 1]);
        if (!isMoveSpell1) {
            isDrawSpell1 = false;
        }
    }
    if (isMoveSpell2) {
        PlayingCard2->updateSpell(spellSpeed * tick.asMicroseconds(), &isMoveSpell2, person2->directions[stepDirection2 - 1]);
        if (!isMoveSpell2) {
            isDrawSpell2 = false;
        }
    }
    return 0;
}

void gui::play(battle& fight) {
    if (step < 6 && !isMoveAnim1 && !isMoveAnim2 && !isMoveSpell1 && !isMoveSpell2) {
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
                break;
        }
        if (person1->chosen_actions[step] != UP && person1->chosen_actions[step] != RIGHT && person1->chosen_actions[step] != DOWN && person1->chosen_actions[step] != LEFT) {
            if (PlayingCard1 != NULL) {
                delete PlayingCard1;
            }
            PlayingCard1 = card::create_card(person1->chosen_actions[step], person1->get_xcoord(), person1->get_ycoord());
            PlayingCard1->set_action_area(person1->directions[stepDirection1]);
            fight.play_card(person1->chosen_actions[step], person1->get_xcoord(), person1->get_ycoord(), person1, person2, person1->directions[stepDirection1]);
            isDrawSpell1 = true;
            isMoveSpell1 = true;
            stepDirection1++;
        }
        if (person2->chosen_actions[step] != UP && person2->chosen_actions[step] != RIGHT && person2->chosen_actions[step] != DOWN && person2->chosen_actions[step] != LEFT) {
            if (PlayingCard2 != NULL) {
                delete PlayingCard2;
            }
            PlayingCard2 = card::create_card(person2->chosen_actions[step], person2->get_xcoord(), person2->get_ycoord());
            PlayingCard2->set_action_area(person2->directions[stepDirection2]);
            fight.play_card(person2->chosen_actions[step], person2->get_xcoord(), person2->get_ycoord(), person1, person2, person2->directions[stepDirection2]);
            isDrawSpell2 = true;
            isMoveSpell2 = true;
            stepDirection2++;
        }
        step++;
    }
}

int gui::render(game_map& field_back) {
    window.clear();
    window.draw(bgSprite);
    if (isDeck) {
        show_deck Deck(person1);
        apply_button applyBTN;
        applyBTN.drawCurrent(window);
        Deck.drawCurrent(window);
    }
    if (isShop) {
        shop Shop(person1->get_money());
        apply_button applyBTN;
        applyBTN.drawCurrent(window);
        Shop.drawCurrent(window);
        shopSprites = Shop.shopSprites;
        shopCards = Shop.shopCards;
    }
    if (isMainMenu) {
        play_button playBTN;
        shop_button shopBTN;
        show_deck_button deckBTN;
        deckBTN.drawCurrent(window);
        shopBTN.drawCurrent(window);
        playBTN.drawCurrent(window);
    }
    if (isActionWindow) {
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
        cancel_button cancelBTN;
        menu_button menuBTN;
        menuBTN.drawCurrent(window);
        cancelBTN.drawCurrent(window);
        startBTN.drawCurrent(window);
        Scroll.set_avalible_cards(person1->get_avalible_cards());
        Scroll.drawCurrent(window);
        if (isOptions) {
            actions Actions(person1->chosen_cards);
            Actions.drawCurrent(window, person1);
            isChoosingOptions = true;
        }
        if (isNPCPlay) {
            person2->play_dark_mage(person1);
            isNPCPlay = false;
        }
        if (isPreview) {
            preview(person1->chosen_actions);
        }
        if (isDrawDirection) {
            cout << "Preview Coord Size = " << preview_coords.size() << endl;
            card* CurCard = card::create_card(person1->chosen_actions[cardsChoosed + moveChoosed - 1], preview_coords.back().first, preview_coords.back().second);
            CurCard->drawActionArea(window, field_back.get_field(), preview_coords.back().first, preview_coords.back().second);
            isChooseDirection = true;
            delete CurCard;
        }
        battle fight;
        if (isPlay) {
            this->play(fight);
        }
        if (isDrawSpell1 && !isMoveAnim1 && !isMoveAnim2) {
            PlayingCard1->drawCurrent(window);
        }
        if (isDrawSpell2 && !isMoveAnim1 && !isMoveAnim2) {
            PlayingCard2->drawCurrent(window);
        }
        if (step == 6 && !isMoveAnim1 && !isMoveAnim2) {
            new_turn_vals();
        }
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
    wallTexture.loadFromFile("images/wall.jpg");
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

play_button::play_button() {
    buttonTexture.loadFromFile("images/buttons/play_button.png");
    buttonSprite.setTexture(buttonTexture);
    x_pos = 412;
    y_pos = 334;
}

void play_button::drawCurrent(sf::RenderTarget& target) {
    buttonSprite.setPosition(x_pos, y_pos);
    target.draw(buttonSprite);
}

cancel_button::cancel_button() {
    buttonTexture.loadFromFile("images/buttons/cancel_button.png");
    buttonSprite.setTexture(buttonTexture);
    x_pos = 250;
    y_pos = 670;
}

void cancel_button::drawCurrent(sf::RenderTarget& target) {
    buttonSprite.setPosition(x_pos, y_pos);
    target.draw(buttonSprite);
}

menu_button::menu_button() {
    buttonTexture.loadFromFile("images/buttons/menu_button.png");
    buttonSprite.setTexture(buttonTexture);
    x_pos = 480;
    y_pos = 670;
}

void menu_button::drawCurrent(sf::RenderTarget& target) {
    buttonSprite.setPosition(x_pos, y_pos);
    target.draw(buttonSprite);
}

shop_button::shop_button() {
    buttonTexture.loadFromFile("images/buttons/shop_button.png");
    buttonSprite.setTexture(buttonTexture);
    x_pos = 412;
    y_pos = 386;
}

void shop_button::drawCurrent(sf::RenderTarget& target) {
    buttonSprite.setPosition(x_pos, y_pos);
    target.draw(buttonSprite);
}

apply_button::apply_button() {
    buttonTexture.loadFromFile("images/buttons/apply_button.png");
    buttonSprite.setTexture(buttonTexture);
    x_pos = 20;
    y_pos = 730;
}

void apply_button::drawCurrent(sf::RenderTarget& target) {
    buttonSprite.setPosition(x_pos, y_pos);
    target.draw(buttonSprite);
}

show_deck_button::show_deck_button() {
    buttonTexture.loadFromFile("images/buttons/show_deck_button.png");
    buttonSprite.setTexture(buttonTexture);
    x_pos = 412;
    y_pos = 438;
}

void show_deck_button::drawCurrent(sf::RenderTarget& target) {
    buttonSprite.setPosition(x_pos, y_pos);
    target.draw(buttonSprite);
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
        card* CurCard = card::create_card(avalible_cards[i]);
        sf::Texture texture;
        texture.loadFromFile(CurCard->get_shirt_image_path());
        cardTexture.push_back(texture);
        delete CurCard;
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

// ACTIONS METHODS

actions::actions(vector<CardID> new_cards) {
    chosen_cards = new_cards;
    for (size_t i = 0; i < 3; i++) {
        if (chosen_cards[i] != VOID) {
            card* CurCard = card::create_card(chosen_cards[i]);
            sf::Texture texture;
            texture.loadFromFile(CurCard->get_shirt_image_path());
            cardTexture.push_back(texture);
            delete CurCard;
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
                card* CurCard = card::create_card(person1->chosen_actions[i]);
                string new_action = CurCard->get_name();
                choiceString += (new_action + "\n");
                delete CurCard;
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

// SHOP METHODS

shop::shop(int money) {
    shop_file_path = "data/shop";
    player_money = money;
}

void shop::drawCurrent(sf::RenderTarget& target) {
    int row = 0, col = 0;
    stringstream coins;
    string coinsSTR;
    coins << player_money;
    coins >> coinsSTR;
    string info = "Your money: " + coinsSTR;
    sf::Font font;
    font.loadFromFile("data/font.ttf");
    sf::Text infoText(info, font, 20);
    infoText.setColor(sf::Color::Black);
    infoText.setPosition(0, 0);
    target.draw(infoText);
    ifstream infile(shop_file_path);
    if (!infile) {
        cout << "Shop error" << endl;
    }
    int tag;
    while (infile >> tag) {
        card* CurCard = card::create_card(CardID(tag));
        shopCards.push_back(CardID(tag));
        sf::Texture texture;
        texture.loadFromFile(CurCard->get_shirt_image_path());
        shopTextures.push_back(texture);
        sf::Sprite sprite(shopTextures.back());
        sprite.setPosition(col * 104 + 5, row * 180 + 45);
        shopSprites.push_back(sprite);
        target.draw(shopSprites.back());
        stringstream cost;
        string costSTR;
        cost << CurCard->get_cost();
        cost >> costSTR;
        string price = costSTR;
        sf::Font font;
        font.loadFromFile("data/font.ttf");
        sf::Text infoText(price, font, 20);
        infoText.setColor(sf::Color::Black);
        infoText.setPosition(col * 104 + 5, row * 180 + 230);
        target.draw(infoText);
        col++;
        if (col % 10 == 0) {
            col = 0;
            row++;
        }
        delete CurCard;
    }
}

// DECK METHODS

show_deck::show_deck(character* pers) {
    person = pers;
}

void show_deck::drawCurrent(sf::RenderTarget& target) {
    int row = 0, col = 0;
    vector<CardID> deck(person->deck);
    for (size_t i = 0; i < deck.size(); i++) {
        card* CurCard = card::create_card(deck[i]);
        sf::Texture texture;
        texture.loadFromFile(CurCard->get_shirt_image_path());
        cardsTextures.push_back(texture);
        sf::Sprite sprite(cardsTextures.back());
        sprite.setPosition(col * 104 + 5, row * 200 + 45);
        target.draw(sprite);
        col++;
        if (col % 10 == 0) {
            col = 0;
            row++;
        }
        delete CurCard;
    }
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
    if (abs(x_pos - dst_x) < eps && abs(y_pos - dst_y) < eps) {  //Stop animation conditions
        return 1;
    }
    if (abs(dst_x - x_pos) != 0) {
        x_pos += (dst_x - x_pos) / abs(dst_x - x_pos) * tick;
    }
    if (abs(dst_y - y_pos) != 0) {
        y_pos += (dst_y - y_pos) / abs(dst_y - y_pos) * tick;
    }
    return 0;
}

// DARK MAGE METHODS

dark_mage_draw::dark_mage_draw(size_t x_coord, size_t y_coord) {
    previewTexture.loadFromFile("images/creatures/mage_preview.png");
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

void dark_mage_draw::drawPreview(sf::RenderTarget& target) {
    sf::Sprite previewSprite(previewTexture);
    for (size_t i = 0; i < startPoints.size(); i++) {
        previewSprite.setPosition(startPoints[i].first * 50, startPoints[i].second * 50);
        target.draw(previewSprite);
    }
}

// BARDESS METHODS

bardess_draw::bardess_draw(size_t x_coord, size_t y_coord) {
    previewTexture.loadFromFile("images/creatures/timmy_preview.png");
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

void bardess_draw::drawPreview(sf::RenderTarget& target) {
    sf::Sprite previewSprite(previewTexture);
    for (size_t i = 0; i < startPoints.size(); i++) {
        previewSprite.setPosition(startPoints[i].first * 50, startPoints[i].second * 50);
        target.draw(previewSprite);
    }
}
