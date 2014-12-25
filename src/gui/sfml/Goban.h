#pragma once
#include "AGui.h"
#include "Options.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>

class Goban: public AGui
{
   public:
      Goban(const Map& m, sf::RenderWindow& mainWindow);
      virtual ~Goban();
      
      // specific goban
      void  setOptions(std::vector<Options*> const& options);
      void setPlaying(Stone::E_COLOR c);
      
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
      
      Stone::E_COLOR _curs_color;
      
      sf::RenderWindow& _mainWindow;
      sf::Texture _goban_tile_tx;
      sf::Texture _stone_tx;
      sf::Texture _hand_tx;
      sf::Texture _stone_black_tx;
      sf::Texture _stone_white_tx;
      sf::Texture _background_tile_tx;
      
      sf::Sprite _goban_sp;
      sf::Sprite _curs_sp;
      sf::Sprite _background_sp;
      
      int _OFFSET_Y;
      int _OFFSET_X;
      sf::Vector2f _SQUARE_SIZE;

      //Infos à l'arrache
      sf::Font            _font;
      GText*      _capturedWhite;
      GText*      _capturedBlack;
      std::vector<Options*>    _options;

      bool handleKeys(const sf::Event& current, EventManager& events);
      void resize();
};
