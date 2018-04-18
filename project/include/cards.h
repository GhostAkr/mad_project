#ifndef PROJECT_INCLUDE_CARDS_H_
#define PROJECT_INCLUDE_CARDS_H_

enum CardID {
    FIREBOLT = 10
}

class card {
private:
    size_t xcoord_start, ycoord_start;
    string shirt_image_path;
    string spell_image_path;
    vector<pair<int, int>> action_area;
    CardID tag;
    int dmg;
public:
    //card(character& pers);
    card* create_card(CardID tag);
};

class firebolt : public card {
    firebolt(character& pers);
};

#endif  // PROJECT_INCLUDE_CARDS_H_
