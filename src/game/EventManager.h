#pragma once

class EventManager {
  public:
    typedef enum e_keys
    {
        NONE = 0,
        QUIT,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ACCEPT,
        BLACK,
        WHITE,
        MAX
    } E_KEYS;

  EventManager();
  ~EventManager();
  
  // Setters
  void setKey(E_KEYS key, bool activate = true);

  // Getters  
  bool getKey(E_KEYS key) const;
  bool getDisposeKey(E_KEYS key); // set keys to false after reading
  E_KEYS getLastKey();
  E_KEYS getDisposeLastKey();

  // Members
  void disposeKey(E_KEYS key);
  void disposeLastKey();

private:
  bool _keys[E_KEYS::MAX];
  E_KEYS _lastKey;

};