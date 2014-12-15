#pragma once
#include "AGui.h"
#include "Options.h"
#include "Config.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>

class Menu: public AGui
{
   public:
      Menu(sf::RenderWindow& mainWindow, std::string const& title = "Welcome");
      virtual ~Menu();
      
      // specific menu
      Config const& config();
      bool chooseOptionValue();
      void setTitle(std::string const& title);
      
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
        sf::RenderWindow&   _mainWindow;
        sf::Font            _font;
        GText*              _title;
        std::vector<Options*>    _options;
        unsigned int        _selected;
        Config        _config;
    
        void    setSelected(unsigned int i);
        void    selectUp();
        void    selectDown();
        void    selectLeft();
        void    selectRight();
        void    validate();

        Options*     selectedOption() const;
        void    saveConfig();
          
      bool handleKeys(const sf::Event& current, EventManager& events);
};