#ifndef ORANGUTAN_UTIL_KEYBOARD_H
#define ORANGUTAN_UTIL_KEYBOARD_H

#include <memory>
#include <vector>

namespace orangutan {

enum KeyState { kReleased, kPressed, kUnknow };

class Keyboard {
 public:
  static Keyboard& instance();

  Keyboard(Keyboard& keyboard) = delete;
  Keyboard(Keyboard&& keyboard) = delete;
  void operator=(const Keyboard& keyboard) = delete;
  void operator=(const Keyboard&& keyboard) = delete;

  [[nodiscard]] const std::vector<KeyState>& getKeyboard() const;

  void setState(int key, KeyState state);
  [[nodiscard]] KeyState getState(int key) const;

 private:
  static Keyboard _instance;
  std::vector<KeyState> _keyboard;

  Keyboard();
  ~Keyboard();
};

}  // namespace orangutan

#endif  // ORANGUTAN_UTIL_KEYBOARD_H
