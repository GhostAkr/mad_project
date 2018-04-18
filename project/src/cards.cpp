#include <iostream>
#include "cards.h"

firebolt::firebolt(character& pers) {
    xcoord_start = pers.get_xcoord();
    ycoord_start = pers.get_ycoord();
    shirt_image_path = "images/cards/shirts/firebolt.png";
    spell_image_path = "images/cards/spells/firebolt.png";
    tag = FIREBOLT;
    dmg = 3;
    for (size_t i = 0; i < ycoord; i++) {
        action_area.push_back(pair<int, int> (xcoord_start, ycoord_start + i));
    }
}

card* card::create_card(CardID name) {
    card* ret;
    switch(name) {
        case FIREBOLT:
            firebolt srs();
            ret = &srs;
            break;
    }
    return ret;
}
