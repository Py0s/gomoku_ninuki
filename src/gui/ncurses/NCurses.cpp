#include "NCurses.h"
#include "Exceptions.h"
#include <string>

NCurses::NCurses(int map_size_y, int map_size_x)
: AGui(map_size_y, map_size_x) {
  if (initscr() == NULL)
    throw Exceptions("Could not initialise screen");

  if (raw() == ERR
      || noecho() == ERR
      || keypad(stdscr, true) == ERR
      || curs_set(0) == ERR)
      {
        endwin();
        throw Exceptions("Could not set terminal properties");
      }
  ESCDELAY = 25;
  timeout(0);
}

NCurses::~NCurses() {
  endwin();
}

// Getters
bool NCurses::getInput(EventManager& events) {
  int	c;
  int	tmp;

  c = ERR;
  while ((tmp = getch()) != ERR)
    c = tmp;
  switch (c)
    {
      case (KEY_UP):
          events.setKey(EventManager::E_KEYS::UP);
          break;
      case (KEY_DOWN):
          events.setKey(EventManager::E_KEYS::DOWN);
          break;
      case (KEY_LEFT):
          events.setKey(EventManager::E_KEYS::LEFT);
          break;
      case (KEY_RIGHT):
          events.setKey(EventManager::E_KEYS::RIGHT);
          break;
      case ('\n'):
          // TODO: Replace \n with something better
          events.setKey(EventManager::E_KEYS::ACCEPT);
          break;
      case ('q'):
      case (KEY_ESC):
          events.setKey(EventManager::E_KEYS::QUIT);
          break;
      default:
          break;
    }
  return true;
}

// Members
bool NCurses::refresh() {
  ::refresh();
  return true;
}

bool NCurses::drawFrame(char c, const Rectangle& rect) {
    mvprintw(rect.y(), rect.x(), &c);
    return true;
}

bool NCurses::drawMap(const char* map) {
   char c[3];

  c[1] = ' ';
  c[2] = '\0';
  for (int y = 0; y < this->_map_size_y; ++y)
    for (int x = 0; x < this->_map_size_x; ++x) {
        c[0] = map[(y * this->_map_size_x) + x];
        if (x == this->_curs.X && y == this->_curs.Y)
        {
            attron(A_REVERSE);
            mvprintw(y, x * 2, c);
            attroff(A_REVERSE);
            mvprintw(y, (x * 2) + 1, &c[1]);
        }
        else
            mvprintw(y, x * 2, c);
      }
  return true;
}

bool NCurses::cursorUp(const Map& m) {
    AGui::cursorUp(m);
    this->drawMap(m.displayMap());
    return true;
}

bool NCurses::cursorDown(const Map& m) {
    AGui::cursorDown(m);
    this->drawMap(m.displayMap());
    return true;
}

bool NCurses::cursorLeft(const Map& m) {
    AGui::cursorLeft(m);
    this->drawMap(m.displayMap());
    return true;
}

bool NCurses::cursorRight(const Map& m) {
    AGui::cursorRight(m);
    this->drawMap(m.displayMap());
    return true;
}

bool NCurses::cursorMouse(int pos_x, int pos_y) {
    return false;
}

bool NCurses::newWindow(const Rectangle& rect, const std::string& msg)
{
    int line_size = msg.size();
    int max_y = rect.y() + rect.sizeY();
    int max_x = rect.x() + rect.sizeX();

    for (int y = rect.y(); y < max_y; ++y) {
        for (int x = rect.x(); x < max_x; ++x) {
            if (y == rect.y() || y == max_y - 1
                    || x == rect.x() || x == max_x - 1)
                mvprintw(y, x, "#\0");
            else
                mvprintw(y, x, " \0");
        }
    }
    mvprintw(rect.y() + (rect.sizeY() / 2), rect.x() + (rect.sizeX() / 2) - (line_size / 2),msg.c_str());
    return true;
}

// Statics
void NCurses::DebugPrint(const std::string& msg)
{
    int y, x, sub;
    getmaxyx(stdscr, y, x);
    sub = (msg.size() / x) + 1;
    mvprintw(y - sub, 0, msg.c_str());
}