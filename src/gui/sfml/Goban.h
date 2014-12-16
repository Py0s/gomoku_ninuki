#pragma once
#include "AGui.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>

class Goban: public AGui
{
   public:
      Goban(const Map& m, sf::RenderWindow& mainWindow);
      virtual ~Goban();
      
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
      const Map& _m;
      
      sf::RenderWindow& _mainWindow;
      sf::Texture _goban_tile_tx;
      sf::Texture _stone_tx;
      sf::Texture _hand_tx;

      sf::Sprite _goban_sp;
      sf::Sprite _curs_sp;
      
      static const int OFFSET_Y = 38;
      static const int OFFSET_X = 38;
      
      bool handleKeys(const sf::Event& current, EventManager& events);
};
