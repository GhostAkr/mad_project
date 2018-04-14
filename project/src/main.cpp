#include <iostream>
#include "game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using std::cout;
using std::endl;

int main() {

    {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");// обязательно для рендера



      while (window.isOpen())
      {
          sf::Event event;
          while (window.pollEvent(event))
          {
              if (event.type == sf::Event::Closed)
                  window.close();
          }

          window.clear();
          //window.draw();
          window.display();
      }
      return 0;

  }

}
