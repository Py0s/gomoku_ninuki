#pragma once

#include "EventManager.h"
#include "Cursor.h"
#include "Rectangle.h"
#include "Map.h"
#include "Cursor.h"
#include "Stone.h"
#include <string>

class AGui {
  public:
    AGui(int map_size_y, int map_size_x);
    virtual ~AGui();

    // Getters
    virtual bool getInput(EventManager& events) = 0;
    virtual const Cursor& getCursor() const;
    
    // Members
    virtual bool refresh() = 0;
    virtual bool drawFrame(char c, const Rectangle& rect) = 0; // Could change with sfml introd
    virtual bool drawMap(const Stone::E_COLOR* map) = 0;
    
    virtual bool cursorUp(const Map& m);
    virtual bool cursorDown(const Map& m);
    virtual bool cursorLeft(const Map& m);
    virtual bool cursorRight(const Map& m);
    virtual bool cursorMouse(int pos_x, int pos_y) = 0; // Prototype could change with sfml
    
    // Naïve implementation of simple menu msgs such as Winner and Loser status
    virtual bool newWindow(const Rectangle& rect, const std::string& msg) = 0;
    
  protected:
    int _map_size_y;
    int _map_size_x;
    Cursor _curs;
    
};

