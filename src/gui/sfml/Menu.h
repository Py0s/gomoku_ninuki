#pragma once
#include "AGui.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>

class Menu: public AGui
{
   public:
      Menu(sf::RenderWindow& mainWindow);
      virtual ~Menu();
      
      // Getters
      virtual bool getInput(EventManager& events);
       
      // Members
      virtual bool refresh();
      virtual bool drawFrame(char c, const Rectangle& rect);
      virtual bool drawMap(const Stone::E_COLOR* map);
      
      virtual bool cursorUp(const Map& m);
      virtual bool cursorDown(const Map& m);
      virtual bool cursorLeft(const Map& m);
      virtual bool cursorRight(const Map& m);
      virtual bool cursorMouse(int pos_x, int pos_y);
      
      virtual bool newWindow(const Rectangle& rect, const std::string& msg);
      
    private:
        sf::RenderWindow& _mainWindow;
      
      bool handleKeys(const sf::Event& current, EventManager& events);
};