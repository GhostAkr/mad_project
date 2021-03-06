#ifndef PROJECT_INCLUDE_GUI_H_
#define PROJECT_INCLUDE_GUI_H_

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "game.h"
using std::vector;
using std::string;

class entity {

};

class show_deck : public entity {
private:
    character* person;
    vector<sf::Texture> cardsTextures;
public:
    show_deck(character* pers);
    void drawCurrent(sf::RenderTarget& target);
};

class shop : public entity {
private:
    string shop_file_path;
    int player_money;
    vector<sf::Texture> shopTextures;
public:
    vector<sf::Sprite> shopSprites;
    vector<CardID> shopCards;
    shop(int money);
    void drawCurrent(sf::RenderTarget& target);
};

class battle_map : public entity {
private:
    sf::Texture wallTexture;
    sf::Texture cellTexture;
    size_t map_height;
    size_t map_width;
    SparseMatrix <Game_object> field;
    vector <vector <sf::Sprite>> mapSprite;
public:
    battle_map(SparseMatrix <Game_object> src_field);
    int set_mapSprite();
    size_t get_map_height();
    size_t get_map_width();
    sf::Sprite get_mapTile(size_t row, size_t col);
    int drawCurrent(sf::RenderTarget& target);
};

class scroll : public entity {
private:
    sf::Texture scrollTexture;
    sf::Sprite scrollSprite;
    vector <sf::Texture> cardTexture;
    vector <CardID> avalible_cards;
    int x_pos, y_pos;
public:
    scroll();
    int drawCurrent(sf::RenderTarget& target);
    int set_coords(int x_delta, int y_delta);
    int set_avalible_cards(vector <CardID> new_cards);
    size_t get_y_pos();
};

class actions : public entity {
private:
    vector<sf::Texture> cardTexture;
    vector<CardID> chosen_cards;
public:
    actions(vector<CardID> new_cards);
    int drawCurrent(sf::RenderTarget& target, character* person1);
};

class creature : public entity {
protected:
    sf::Texture creatureTexture;
    sf::Texture previewTexture;
    sf::Sprite creatureSprite;
    creature_type type;
    int delta_x, delta_y;  // For updateCurrent
public:
    vector<pair<int, int>> startPoints;  // Start points for each step
    float x_pos, y_pos;
    static creature* create_creature(creature_type new_type, size_t xcoord, size_t ycoord);
    virtual int drawCurrent(sf::RenderTarget& target) = 0;
    virtual void drawPreview(sf::RenderTarget& target) = 0;
    int updateCurrent(character* person, float tick);  // Returns 1 to stop animation, 0 - other case
};

class dark_mage_draw : public creature {
public:
    void drawPreview(sf::RenderTarget& target);
    dark_mage_draw(size_t x_coord, size_t y_coord);
    int drawCurrent(sf::RenderTarget& target);
};

class bardess_draw : public creature {
public:
    void drawPreview(sf::RenderTarget& target);
    bardess_draw(size_t x_coord, size_t y_coord);
    int drawCurrent(sf::RenderTarget& target);
};

class button : public entity {
protected:
    sf::Texture buttonTexture;
    sf::Sprite buttonSprite;
public:
    int btnWidth;
    int btnHeight;
    int x_pos, y_pos;
};

class start_turn_button : public button {
public:
    start_turn_button();
    int drawCurrent(sf::RenderTarget& target);
};

class play_button : public button {
public:
    play_button();
    void drawCurrent(sf::RenderTarget& target);
};

class cancel_button : public button {
public:
    cancel_button();
    void drawCurrent(sf::RenderTarget& target);
};

class menu_button : public button {
public:
    menu_button();
    void drawCurrent(sf::RenderTarget& target);
};

class shop_button : public button {
public:
    shop_button();
    void drawCurrent(sf::RenderTarget& target);
};

class apply_button : public button {
public:
    apply_button();
    void drawCurrent(sf::RenderTarget& target);
};

class show_deck_button : public button {
public:
    show_deck_button();
    void drawCurrent(sf::RenderTarget& target);
};

class gui {
private:
    int dxScale, dyScale;
    int processEvents();
    int update(sf::Time tick);
    int render(game_map& field_back);
    sf::RenderWindow window;
    sf::Texture bgTexture;  // Background
    sf::Sprite bgSprite;
    sf::View view;
    // Window specs
    int windowWidth;
    int windowHeight;
    // Windows flags
    bool isMainMenu;
    bool isActionWindow;
    bool isShop;
    bool isDeck;
    // Animation flags
    bool scrollUp;
    bool scrollDown;
    bool isMoveAnim1;
    bool isMoveAnim2;
    bool isMoveSpell1;
    bool isMoveSpell2;
    // Buttons flags
    bool isPlayBtn;
    bool isBegBtn;
    bool isScrollBtn;
    bool isCancelBtn;
    bool isMenuBtn;
    bool isShopBtn;
    bool isApplyBtn;
    bool isShopCardsBtn;
    bool isDeckBtn;
    //Drawing flags
    bool isDrawSpell1;
    bool isDrawSpell2;
    // Other elements flags
    bool isOptions;
    bool isChoosingOptions;
    bool isPlay;
    bool isBattle;
    bool isNPCPlay;
    bool isDrawDirection;
    bool isPreview;
    bool isChooseDirection;
    int cardsCounter;
    int cardsChoosed;
    size_t moveChoosed;
    size_t step;
    size_t stepDirection1;
    size_t stepDirection2;
    scroll Scroll;
    card* PlayingCard1;
    card* PlayingCard2;
    character* person1;
    character* person2;
    creature* creature1;
    creature* creature2;
    game_map field_back;
    vector<CardID> cardNums;
    vector<pair<int, int>> preview_coords;
    vector<pair<int, int>> cardsStartPoints;
    vector<sf::Sprite> shopSprites;
    vector<CardID> shopCards;
public:
    void handleButtons();
    void handleKeyboard(sf::Event keyEvent);
    // Handling methods for each key
    void handleMoveUp(sf::Event keyEvent);
    void handleMoveRight(sf::Event keyEvent);
    void handleMoveDown(sf::Event keyEvent);
    void handleMoveLeft(sf::Event keyEvent);
    // Handling methods for each button
    void handlePlayBTN(play_button& playBTN);
    void handleShopBTN(shop_button& shopBTN);
    void handleShowDeckBTN(show_deck_button& deckBTN);
    void handleApplyBTN(apply_button& applyBTN);
    void handleShopCards();
    void handleStartBTN(start_turn_button& startBTN);
    void handleCancelBTN(cancel_button& cancelBTN);
    void handleMenuBTN(menu_button& menuBTN);
    void handleScrollCards();
    void handleActionCards();
    void handleDirection();
    // Other methods
    void set_start_vals();
    void new_turn_vals();
    int get_xpreivew();
    int get_ypreview();
    gui(game_map& field);
    ~gui();
    int run();
    int set_cardNums (character* person, int num);
    void play(battle& fight);
    void preview(vector<CardID> chosen_actions);
    void resize(sf::Event event);
};

#endif  // PROJECT_INCLUDE_GUI_H_
