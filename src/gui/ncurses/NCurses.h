#pragma once

#include "AGui.h"
#include "EventManager.h"
#include "Rectangle.h"
#include "Cursor.h"
#include "Map.h"
#include <ncurses.h>

// For ncurses
#define KEY_ESC 27

class NCurses: public AGui {
public:
  NCurses(int map_size_y, int map_size_x);
  ~NCurses();

  // Getters
  virtual bool getInput(EventManager& events);
  
  // Members
  virtual bool refresh();
  virtual bool drawFrame(char c, const Rectangle& rect);
  virtual bool drawMap(const char* map);
  
  virtual bool cursorUp(const Map& m);
  virtual bool cursorDown(const Map& m);
  virtual bool cursorLeft(const Map& m);
  virtual bool cursorRight(const Map& m);
  virtual bool cursorMouse(int pos_x, int pos_y);
  
  virtual bool newWindow(const Rectangle& rect, const std::string& msg);

  static void DebugPrint(const std::string& msg);
};
