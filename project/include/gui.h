#ifndef PROJECT_INCLUDE_GUI_H_
#define PROJECT_INCLUDE_GUI_H_

#include <iostream>
#include <vector>

using std::vector;

class planning {
private:
    vector<size_t> chosen_actions;  // Надо заполнить
public:
    vector<size_t> get_chosen_actions();
};

#endif  // PROJECT_INCLUDE_GUI_H_
