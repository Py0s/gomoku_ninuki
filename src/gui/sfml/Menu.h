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
      virtual bool drawAll();
      
      virtual bool cursorUp();
      virtual bool cursorDown();
      virtual bool cursorLeft();
      virtual bool cursorRight();
      virtual bool cursorMouse(int pos_x, int pos_y);
      
      virtual bool newWindow(const Rectangle& rect, const std::string& msg);
      
    private:
        sf::RenderWindow& _mainWindow;
      
      bool handleKeys(const sf::Event& current, EventManager& events);
};