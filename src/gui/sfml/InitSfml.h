#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class InitSfml {
  public:
    InitSfml();
    virtual ~InitSfml();

    sf::RenderWindow& getWindow();
    bool thisIsShit(int toto) {
        return toto;
    };
    
  private:
    sf::RenderWindow _mainWindow;

};
