#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <vector>

enum State {
    KEYUP = 0, KEYNUP, KEYDOWN, KEYNDOWN, KEYUNKNOW
};

class Keyboard
{
public:
  static Keyboard&                      instance();

  const std::vector<State>&             getKeyboard() const;

  void                                  setState(int key, State state);
  State                                 getState(int key) const;

private:
  Keyboard&                             operator=(const Keyboard&){return instance();}
                                        Keyboard(const Keyboard&){}

  static Keyboard                       _instance;
  std::vector<State>                    _keyboard;

                                        Keyboard();
                                        ~Keyboard(){};
};

#endif // KEYBOARD_H
